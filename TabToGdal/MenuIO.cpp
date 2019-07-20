#include "pch.h"
#include "MenuIO.h"
#include <iostream>
#include <string>



MenuIO::MenuIO()
{
}


MenuIO::~MenuIO()
{
}

void MenuIO::printSymbol(const int &length, const std::string &symbol, const int countTabs = 0)
{
		
	if (countTabs > 0) printSymbol(countTabs, "\t", 0);

	for (int i = 0; i<length ; i++)
	{	
		std::cout << symbol;
	}

}





void MenuIO::printMenuString(	const Aligment alig, 
								const int & length,
								const std::string & text, 
								const std::string & symbolBorder, 
								const int countTabs)
{
	
	std::string leftPadding = "   ";
	if (countTabs > 0) printSymbol(countTabs, "\t", 0);
	int borderLen = symbolBorder.length() * 2;
	int SpaceLen;
	switch (alig)
		
	{
	case aCenter:
		
	    SpaceLen = length - borderLen - text.length();
		//std::cout << length << "=" << borderLen << "+" << SpaceLen <<"+"<< text.length()<<"="<< int(borderLen)+int(SpaceLen)+int(text.length());
		if (length > 0)
		{
			std::cout << symbolBorder;
			printSymbol(SpaceLen / 2, " ", 0);
			std::cout << text;
			printSymbol(SpaceLen / 2, " ", 0);
			std::cout << symbolBorder;
		}
		break;



	case aLeft:
		
	     SpaceLen = length - borderLen - text.length()-leftPadding.length();
		//std::cout << length << "=" << borderLen << "+" << SpaceLen <<"+"<< text.length()<<"="<< int(borderLen)+int(SpaceLen)+int(text.length());
		 if (length > 0)
		 {
			 std::cout << symbolBorder << leftPadding;
			 std::cout << text;
			 printSymbol(SpaceLen, " ", 0);
			 std::cout << symbolBorder;
		 }
		break;
	default:
		break;
	}
	

	

}

void MenuIO::printMenuItem(const int &length , const int & keyName, const std::string & itemName, const int countTabs=0)
{
	std::string s = "[";
	s.append(std::to_string(keyName));
	s.append("]");
	s.append("   ");
	s.append(itemName);
	std::cout << std::endl;
	MenuIO::printMenuString(aLeft,length, s, "#", countTabs);


}

const MenuHandle* MenuIO::MenuInput (const std::vector<MenuHandle> &MnHandle)
{
	int c;
	
		c = -1;
		
		std::cin >> c;
		
		if (c == 0)
		{
			return &MnHandle.back();
		} 

		if ((c > 0) && (c <= 9))
		{



			return &MnHandle.at(c);

		} 
	

	return nullptr;
}

void MenuIO::setHandleInform(std::vector<MenuHandle> &vectorHandles, const std::string &districtName)
{
	
	for (auto &p : vectorHandles)
	{
		p.DistrictFolderName = districtName;
		if (p.eAction == Header)
		{
			p.sItemName = districtName;
			
		}

	}
}


