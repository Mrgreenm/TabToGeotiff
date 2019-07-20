#include "pch.h"
#include <iostream>
#include "Menu.h"
#include "FileSystemIO.h"
#include <windows.h>




const std::vector<boost::filesystem::directory_entry>* dirList;
std::string Zone1PROJ, Zone2PROJ, Zone3PROJ, projTo;

Menu::Menu()
{
}


Menu::~Menu()
{
}

void Menu::printHeader()
{
	
	MenuIO::printSymbol(MENU_LENGTH, "*", headerTabCount);
	std::cout << std::endl;
	MenuIO::printMenuString(aCenter, MENU_LENGTH, "- TAB TO GEOTIF - ", "**", headerTabCount);
	std::cout << std::endl;
	MenuIO::printMenuString(aCenter, MENU_LENGTH, "Version :"+ *ProgramVersion, "**", headerTabCount);
	std::cout << std::endl;
	MenuIO::printMenuString(aCenter, MENU_LENGTH, "Created by Andrey Moshchenko, 2019", "**", headerTabCount);
	std::cout << std::endl;
	MenuIO::printSymbol(MENU_LENGTH, "*", headerTabCount);
	std::cout << std::endl << std::endl << std::endl;
}






void Menu::printMenu(const std::vector<MenuHandle> &menuHandle)
{
	system("cls");
	printHeader();
	//ShellExecute(NULL, L"open", L"./GDAL/gdal_translate.exe", NULL, NULL, SW_SHOWDEFAULT);
	//system("start ./GDAL/gdal_translate.exe");

	
	
	int key = 1;
	for (int index = 0; index < menuHandle.size() - 1; index++)
	{
		
		if (menuHandle.at(index).eAction == Header) 
		{
			MenuIO::printSymbol(MENU_LENGTH, "#", headerTabCount);
			std::cout << std::endl;
			MenuIO::printMenuString(aCenter, MENU_LENGTH, menuHandle.at(index).sItemName, "##", headerTabCount);
			std::cout << std::endl;
			MenuIO::printSymbol(MENU_LENGTH, "#", headerTabCount);
			std::cout << std::endl;
		}
		else 
		{
			MenuIO::printMenuItem(MENU_LENGTH, key, menuHandle.at(index).sItemName, 0);
			key++;			
		}

	}
	MenuIO::printMenuItem(MENU_LENGTH, 0, menuHandle.back().sItemName, 0);
	std::cout << std::endl;

	const MenuHandle* currentHandle = MenuIO::MenuInput(menuHandle);

	if (!currentHandle)
	{
		printMenu(menuHandle);
	}
	else
	{
		if (currentHandle->eAction == DistrictAction)
		{
			//std::cout << currentHandle->DistrictFolderName;
			menuDoAction(DistrictAction, currentHandle->DistrictFolderName);
		}
		else
		{
			menuDoAction(currentHandle->eAction, currentHandle->DistrictFolderName);
		}
		
	}
	
}

void Menu::printDistricts(bool doNext)
{
	

	std::vector<MenuHandle> localHandlesArray;
	localHandlesArray.push_back({ "Выберите район", Header });
	if (doNext) 
	{
		AddNextDistdictsItems(localHandlesArray);
	}else
	{
		PreviousDistdictsItems(localHandlesArray);
	}

	bool bisShowNext = (DistrictPointer <dirList->size());
	bool bisShowPrevious = DistrictPointer - (DISTRICTS_IN_MENU) > 0;
	if (bisShowPrevious)localHandlesArray.push_back({ "Назад", SelectPreviousDistdicts });
	if (bisShowNext) localHandlesArray.push_back({ "Ещё", SelectDistrict });

	localHandlesArray.push_back({ "Главное меню", ToMainMenu });
	
	printMenu(localHandlesArray);
}



void Menu::printDistrictAction(const std::string &distrName)
{
	MenuIO::setHandleInform(hSelectZone, distrName);
    printMenu(hSelectZone);
}

void Menu::doDistrictAction(const Actions & a, const std::string & distrName)
{
	

	system("cls");

	std::string projFrom = "";
	switch (a)
	{
	
	case Zone1: projFrom = Zone1PROJ;
		break;
	case Zone2:projFrom = Zone2PROJ;
		break;
	case Zone3:projFrom = Zone3PROJ;
		break;
	default:
		break;
	}
	    //ini path variables
		bfs::path currentPath = bfs::current_path().append(distrName);
		bfs::path tempPath = currentPath;
		bfs::path GeoTiffFolderPath = currentPath;
		GeoTiffFolderPath.append("Geotiffs");
				
		//delete folders
		tempPath.append("temp");
		bfs::remove_all("./temp");
		bfs::remove_all(tempPath.string());
		bfs::remove_all(GeoTiffFolderPath.string());
		
		//create folders
		bfs::create_directory(tempPath);
		bfs::create_directory(GeoTiffFolderPath);
		
		//std::vector<std::string>* tifFilesList = FileSystemIO::GetFileList(currentPath);
		std::unique_ptr<std::vector<std::string>> tifFilesList (FileSystemIO::GetFileList(currentPath));


		for(auto currentTifFileName:*tifFilesList)
		{
			bfs::path workFilePath = currentPath;
			workFilePath.append(currentTifFileName);

			bfs::path tempFilePath = tempPath;
			tempFilePath.append(currentTifFileName);

			bfs::path GeoTiffFilePath = GeoTiffFolderPath;
			GeoTiffFilePath.append(currentTifFileName);

			std::vector<std::string> inCoordinates;
		
			
			

			std::string currentTabFileName = FileSystemIO::GetFileByName(currentPath, currentTifFileName.substr(0, currentTifFileName.find(".")));
			if (currentTabFileName != "0")
			{
				std::string commandstring = "";
				
				std::vector<std::string> coords = FileSystemIO::GetCoords(currentPath,currentTabFileName);

				//GDAL_TRANSLATE
				commandstring = bfs::current_path().string()+"\\GDAL\\gdal_translate.exe -of GTiff ";
				for (auto s : coords)
				{
					std::string coord_s = s.substr(0, s.find("*"));
					std::string coord_MSK = s.substr(s.find("*")+1, s.back());
					inCoordinates.push_back(coord_MSK);
					commandstring = commandstring + " -gcp " + coord_s ;
				}
				commandstring = commandstring + " " + "\"" + workFilePath.string() + "\" " + "\"" + tempFilePath.string() + "\" ";
				system(commandstring.c_str());

				
				//GDALWARP
				commandstring = bfs::current_path().string() + "\\GDAL\\gdalwarp.exe ";
				commandstring = commandstring + "-t_srs \"" + projTo + "\" ";
				commandstring = commandstring + "-s_srs \"" + projFrom + "\" ";
				commandstring = commandstring + "-r near -order 1 -co COMPRESS=DEFLATE ";
				commandstring = commandstring + " " + "\"" + tempFilePath.string() + "\" " + "\"" + GeoTiffFilePath.string() + "\" ";
				system(commandstring.c_str());
				
			}

			
			
		}

		system("pause");
		bfs::remove_all(tempPath.string());
		
	
}

void Menu::doAllDistrictAction(const Actions & a)
{
	std::string dirName;
	for (auto dirName : *dirList)
	{
		doDistrictAction(a, dirName.path().filename().string());
	}



}


int Menu::startMenu(const std::string &programVersion)
{
	
	ProgramVersion = &programVersion;
	if (iniData())
	{


	}

	while (ShowMenu)
	{
		printMenu(hMainMenu);
		
	}

	return 0;

}

int Menu::menuDoAction(const Actions & a, std::string distrName)
{
	
	switch (a)
	{
	case ToMainMenu:
		DistrictPointer = 0;
		printMenu(hMainMenu);
		
		break;
	case SelectDistrict:
		printDistricts(true);
		break;
	case SelectPreviousDistdicts:
		printDistricts(false);
		break;
	case DoAll:
		bDoAll = true;
		printMenu(hSelectZone);
		break;
	case DistrictAction:
		printDistrictAction(distrName);
		break;
	case Zone1:
		if (bDoAll)	doAllDistrictAction(a);
		else doDistrictAction(Zone1, distrName);
		break;
	case Zone2:
		if (bDoAll)	doAllDistrictAction(a);
		else doDistrictAction(Zone2, distrName);
		break;
	case Zone3:
		if (bDoAll)	doAllDistrictAction(a);
		else doDistrictAction(Zone3, distrName);
		break;

	case Exit:
		ShowMenu = false;
		break;
	default:
		break;
	}
	bDoAll = false;
	return 0;
}

int Menu::iniData()
{

	dirList = FileSystemIO::GetFolderList();
	std::vector<std::string> variables = FileSystemIO::ReadSettings();
	Zone1PROJ = variables.at(0);
	Zone2PROJ = variables.at(1);
	Zone3PROJ = variables.at(2);
	projTo = variables.at(3);

	return 1;
}

void Menu::AddNextDistdictsItems(std::vector<MenuHandle> &HandlesArray)
{
	int localBeginPointer = DistrictPointer;
	for (int i = localBeginPointer; DistrictPointer  < localBeginPointer + DISTRICTS_IN_MENU; i++)
	{
		DistrictPointer++;
		if (i < dirList->size())
		{
			std::string localString = dirList->at(i).path().filename().string();
			HandlesArray.push_back({ localString,DistrictAction,localString });
		}
		else
		{
			break;
		}
	}
	if (DistrictPointer > dirList->size()) DistrictPointer = dirList->size();
	
}

void Menu::PreviousDistdictsItems(std::vector<MenuHandle> &HandlesArray)
{
	int localBeginPointer = DistrictPointer-2* DISTRICTS_IN_MENU;
	if (localBeginPointer < 0) localBeginPointer = 0;
	DistrictPointer = localBeginPointer;
	
	for (int i = localBeginPointer; DistrictPointer < localBeginPointer + DISTRICTS_IN_MENU; i++)
	{
		DistrictPointer++;
		if (i < dirList->size())
		{
			std::string localString = dirList->at(i).path().filename().string();
			HandlesArray.push_back({ localString,DistrictAction,localString });
		}
		else
		{
			break;
		}
	}
	if (DistrictPointer < 0) DistrictPointer = 0;
	
}
