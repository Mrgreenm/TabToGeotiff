//Menu
#pragma once
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include "boost\filesystem.hpp" 

#include <string>
#include <vector>
#include "MenuIO.h"
#include <string>

const int MENU_LENGTH = 50;
const int headerTabCount = 0;
const int DISTRICTS_IN_MENU = 7; //1-8


class Menu
{
private:
	
	bool bDoAll = false;
	int DistrictPointer = 0;

public:
	bool ShowMenu = true;
	
	const std::vector<MenuHandle> hMainMenu = { {"Âûáåðèòå äåéñòâèå", Header},
												{"Âñå ðàéîíû", DoAll},
												{"Âûáðàòü ðàéîí", SelectDistrict},
												{"Âûõîä", Exit}
	};
	std::vector<MenuHandle> hSelectZone = { {"Âûáåðèòå çîíó", Header},
												{"Çîíà 1", Zone1},
												{"Çîíà 2", Zone2},
												{"Çîíà 3", Zone3},
												{"Íàçàä", ToMainMenu}
	};
	


	const std::string* ProgramVersion;
	Menu();
	~Menu();
	void printHeader();
	void printMenu(const std::vector<MenuHandle> &menuHandle);

	void printDistricts(bool doNext);
	

	void printDistrictAction(const std::string &distrName);
	void doDistrictAction(const Actions &a,const std::string &distrName);
	void doAllDistrictAction(const Actions &a);
	int startMenu(const std::string &programVersion);
	int menuDoAction(const Actions &a, const std::string distrName = "");
	int iniData();
	void AddNextDistdictsItems(std::vector<MenuHandle> &HandlesArray);
	void PreviousDistdictsItems(std::vector<MenuHandle> &HandlesArray);
};

