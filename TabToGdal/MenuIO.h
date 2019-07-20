#pragma once
#include <string>
#include <vector>
enum Aligment
{aCenter,
aLeft
};

enum Actions
{
	Header, ToMainMenu, SelectDistrict, SelectPreviousDistdicts, DoAll, Clear, Convertation, DistrictAction, Exit, Zone1, Zone2, Zone3,Next

};


struct MenuHandle
{
	std::string sItemName;
	Actions eAction;
	std::string DistrictFolderName = "";
	MenuHandle(std::string s, Actions eA) :sItemName(s), eAction(eA) {};
	MenuHandle(std::string s, Actions eA, std::string dfn) :sItemName(s), eAction(eA), DistrictFolderName(dfn){};
	void setItemName(const std::string &name) { 
		sItemName = name; }
	
};
class MenuIO
{

public:
	MenuIO();
	~MenuIO();
	static void printSymbol(const int &length, const std::string &symbol, const int countTabs);
	static void printMenuString(const Aligment, const int &length, const std::string &text, const std::string &symbolBorder, const int countTabs);
	static void printMenuItem(const int &length, const int &keyName, const std::string &itemName, const int countTabs);
	const static MenuHandle* MenuInput(const std::vector<MenuHandle> &MnHandle);
	static void setHandleInform(std::vector<MenuHandle>&, const std::string&);
	
};

