
#include "pch.h"
#include <iostream>
#include "Menu.h"
#include <string>

const std :: string PROGRAM_VERSION = "0.2.2";

int main()
{
	system("cls");

	setlocale(LC_ALL, "Russian");

	auto newMenu = std::make_unique<Menu> ();

	//Menu* newMenu = new Menu;

	if (newMenu->startMenu(PROGRAM_VERSION) == 0)
	{
		
		//std::cout << "Всего хорошего !!!"<<std::endl;
		system("pause");
	}
	else
	{
	
		std::cout << "Возникла ошибка";
		system("pause");

	}
	
	
}
