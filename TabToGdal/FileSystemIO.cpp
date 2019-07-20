
#include "pch.h"
#include "FileSystemIO.h"

#include <filesystem>
#include <cstdlib>
#include <fstream>
#include <string>
#include "windows.h"



FileSystemIO::FileSystemIO()
{
}


FileSystemIO::~FileSystemIO()
{
}
 std::vector<bfs::directory_entry>* FileSystemIO::GetFolderList()
{
	std::vector<bfs::directory_entry>* FoldersVector = new std::vector<bfs::directory_entry>;
	bfs::path localPath = bfs::current_path();
	bfs::directory_iterator end_iter;
	for (bfs::directory_iterator dir_itr(localPath); dir_itr != end_iter; ++dir_itr)
	{
		try
		{
			if (bfs::is_directory(*dir_itr))
			{
								
				if (isMapFilesExists(dir_itr->path().filename())){ FoldersVector->push_back(*dir_itr); }
			}

		}
		catch (const std::exception & ex)
		{
			std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
		}
	}

	for (auto const &i : *FoldersVector)
	{

		std::cout << "***" << i << std::endl;

	}

	return FoldersVector;
}

 bool FileSystemIO::isMapFilesExists(const bfs::path p)
 {
	 bfs::directory_iterator end_iter;
	 bool tabExist = false, tifExist = false;
	 for (bfs::directory_iterator dir_itr(p); dir_itr != end_iter; ++dir_itr)
	 {

		 try
		 {
			 if (!bfs::is_directory(*dir_itr))
			 {
				 
				 if (dir_itr->path().extension() == ".tab"){ tabExist = true;}
				 else if (dir_itr->path().extension() == ".tif") { tifExist = true; }
			 }
			 if (tabExist && tifExist) { return true; }

		 }
		 catch (const std::exception & ex)
		 {
			 std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
		 }
	 }
	 return false;
 }

 std::string FileSystemIO::GetFirstWithExtention(const bfs::path &localPath, const std::string & Extention)
 {
	
	 bfs::directory_iterator end_iter;
	 for (bfs::directory_iterator dir_itr(localPath); dir_itr != end_iter; ++dir_itr)
	 {
		 try
		 {
			 if (!bfs::is_directory(*dir_itr))
			 {
				 if (dir_itr->path().extension() == Extention) 
				 {
					 return dir_itr->path().filename().string();
				 }
				 
			 }

		 }
		 catch (const std::exception & ex)
		 {
			 std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
		 }
	 }
	 
	 return std::string();
 }

 std::string FileSystemIO::GetFileByName(const bfs::path &localPath, const std::string & fileName)
 {

	 bfs::directory_iterator end_iter;
	 std::string localStr = fileName+".tab" ;
	 for (bfs::directory_iterator file_itr(localPath); file_itr != end_iter; ++file_itr)
	 {
		 try
		 {
			 if (!bfs::is_directory(*file_itr))
			 {
				// std::cout << file_itr->path().filename().string().find(localStr) << "  " << file_itr->path().filename().string() << "   " << localStr << "\n";
				 
				 		 
				 if (file_itr->path().filename().string().find(localStr) != std::string::npos)
				 {
					return file_itr->path().filename().string();
				 }

			 }

		 }
		 catch (const std::exception & ex)
		 {
			 std::cout << file_itr->path().filename() << " " << ex.what() << std::endl;
		 }
	 }

	 return "0";

 }

 std::vector<std::string>* FileSystemIO::GetFileList(bfs::path &localPath)
 {
	 std::vector<std::string>* localVector = new std::vector<std::string>;
	 bfs::directory_iterator end_iter;
	 for (bfs::directory_iterator dir_itr(localPath); dir_itr != end_iter; ++dir_itr)
	 {
		 try
		 {
			  if (!bfs::is_directory(*dir_itr))
			 {
				 if (dir_itr->path().extension() == ".tif")
				 {
					
					 localVector->push_back(dir_itr->path().filename().string());
					// std::cout << localVector->at(localVector->size()-1);
				 }

			 }

		 }
		 catch (const std::exception & ex)
		 {
			 std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
		 }
	 }
	// system("pause");
	 return localVector;

 }

 std::vector<std::string> FileSystemIO::GetCoords(const bfs::path localpath, const std::string & fileName)
 {
	   std::vector <std::string> LocalStrList;
	   bfs::path path = localpath;
	   path = path.append(fileName);
	   
	   
		 std::ifstream proxyTabFile(path.string());
		 if (proxyTabFile.is_open())
		 {
			 std::string str, X1Y1, X2Y2, X1, Y1, X2, Y2;

			 bool isHeader = true;
			 
			 while (getline(proxyTabFile, str))
			 {

				 std::string::size_type str_index;
				 std::string::size_type str2_index;

				 str_index = str.find("(");
				 str2_index = str.find(")");

				 if (str_index != -1)
				 {

					 X1Y1 = str.substr(str_index + 1, str2_index - str_index - 1);
					 str_index = str.find("(");
					 str2_index = str.find(")");
					 X1 = X1Y1.substr(0, X1Y1.find(","));
					 Y1 = X1Y1.substr(X1Y1.find(",") + 1, std::string::npos);
					 X1Y1 = X1 + " " + Y1;

					 str.erase(0, str2_index + 2);
					 str_index = str.find("(");
					 str2_index = str.find(")");
					 X2Y2 = str.substr(str_index + 1, str2_index - str_index - 1);
					 X2 = X2Y2.substr(0, X2Y2.find(","));
					 Y2 = X2Y2.substr(X2Y2.find(",") + 1, std::string::npos);
					 X2Y2 = X2 + " " + Y2;


					 LocalStrList.push_back(X2Y2 + " " + X1Y1+"*"+ X1 + " " + Y1);
					
				 }
			 }

			 proxyTabFile.close();
			 return LocalStrList;


		 }
		 else
		 {
			 return LocalStrList;
		 }


}

 void FileSystemIO::writeCoordsToFile(const std::vector<std::string>& CoordsVector, const std::string & fileName)
 {
	 bfs::create_directory("temp");
	 bfs::path p = bfs::current_path().append("temp");
	 p.append(fileName);
	 std::ofstream file;
	 file.open(p.string(), std::ofstream::ate);
	 if (file.is_open())
	 {
		 for (auto s:CoordsVector)
		 {
			 file << s << std::endl;
		 }
		 file.close();
	 }
 }

std::vector<std::string> FileSystemIO::ReadSettings()
 {
	bool bAllOk =true;
	std::vector<std::string> settingsVector;
	std::string Zone1PROJ = "+proj=tmerc +ellps=krass +towgs84=23.57,-140.95,-79.8,0,0.35,0.79,-0.22 +units=m +lon_0=79.46666666666 +lat_0=0 +k_0=1 +x_0=1300000 +y_0=-5312900.56";
	std::string Zone2PROJ = "+proj=tmerc +ellps=krass +towgs84=23.57,-140.95,-79.8,0,0.35,0.79,-0.22 +units=m +lon_0=82.46666666666 +lat_0=0 +k_0=1 +x_0=2300000 +y_0=-5312900.56";
	std::string Zone3PROJ = "+proj=tmerc +ellps=krass +towgs84=23.57,-140.95,-79.8,0,0.35,0.79,-0.22 +units=m +lon_0=85.46666666666 +lat_0=0 +k_0=1 +x_0=3300000 +y_0=-5312900.56";
	std::string projTo = "+proj=utm +zone=44 +datum=WGS84 +units=m +no_defs";

		if (!bfs::exists("config.ini"))
		{
			bAllOk = false;
		}


		std::fstream configFile("./config.ini");
		if (configFile.is_open() && bAllOk)
		{
			std::string line;
			while (std::getline(configFile, line))
			{
				int delimetr = line.find(":");
				if (delimetr >= 0) settingsVector.push_back(line.substr(delimetr, line.size() - 1));
				else bAllOk = false;
			}
		}else bAllOk = false;
		
		
		if (!bAllOk)//Default
		{
			settingsVector.push_back(Zone1PROJ);
			settingsVector.push_back(Zone2PROJ);
			settingsVector.push_back(Zone3PROJ);
			settingsVector.push_back(projTo);
			std::ofstream configFile("./config.ini");
			configFile << Zone1PROJ << std::endl;
			configFile << Zone2PROJ << std::endl;
			configFile << Zone3PROJ << std::endl;
			configFile << projTo << std::endl;
			configFile.close();
		
		}
		
		return settingsVector;

 }



 
