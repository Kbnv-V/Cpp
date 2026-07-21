#include "Menu.h"
#include"GetDisk.h"
#include"GetLog.h"
#include<iostream>
#include<cstdlib>
#include<thread>
using namespace std;

void Menu::StartModule()
{
	/*
	cout << "=====МЕНЮ=====" << "\n\n";
	cout << "1. Мониторинг свободного места на диске." << "\n";
	cout << "2. Мониторинг логов системы." << "\n";
	cout << "3. Статус служб." << "\n\n";
	cout << "Ввод: ";

	cin >> Menu::itemMenu;

	if (itemMenu < 1 || itemMenu > 3)
	{
		system("cls");
		cout << "Такой пункт меню отсутсвует!" << "\n";
		StartModule();
	}

	//меню мониторинга свободного места
	if (itemMenu == 1)
	{
		system("cls");
		cout << "1. Включить службу." << "\n";
		cout << "2. Выключить службу." << "\n";
		cout << "2. Вернутся в главное меню." << "\n\n";
		cout << "Ввод: ";

		cin >> itemMenu;

		if (itemMenu < 1 || itemMenu > 3)
		{
			cout << "Такой пункт меню отсутсвует!" << "\n";
			system("cls");
			StartModule();
		}

		//запуск службы мониторинга свободного места
		if (itemMenu == 1)
		{
			//проверяем значение свойства, которое отдает статус службы
			if (diskMonitor.GetStatusModule())
			{
				system("cls");
				cout << "Служба уже запущена!" << endl;
				StartModule();
			}
			else
			{
				system("cls");
				diskMonitor.StartDiskMonitoring();
				StartModule();
			}
		}

		//остановка службы мониторинга свободного места
		if (itemMenu == 2)
		{
			//проверяем значение свойства, которое отдает статус службы
			if (!diskMonitor.GetStatusModule())
			{
				system("cls");
				cout << "Служба уже остановлена!" << endl;
				StartModule();
			}
			else
			{
				system("cls");
				diskMonitor.StopDiskMonitoring();
				StartModule();
			}
		}

		//выход в главное меню
		if (itemMenu == 3)
		{
			StartModule();
		}
		
	}

	//запуск мониторинга логов
	if (itemMenu == 2)
	{
		
	}

	//получение статусов работы модулей
	if (itemMenu == 3)
	{

	}
}

//методы для обработки сигналов

void Menu::StartDiskMonitor()
{
	if (diskMonitor.GetStatusModule())
	{
		system("cls");
		cout << "Служба уже запущена!" << endl;
		StartModule();
	}
	else
	{
		diskMonitor.StartDiskMonitoring();
	}
}

void Menu::StopDiskMonitor()
{
	if (!diskMonitor.GetStatusModule())
	{
		system("cls");
		cout << "Служба уже остановлена!" << endl;
		StartModule();
	}
	else
	{
		diskMonitor.StopDiskMonitoring();
	}
}

void Menu::GetDiskStatus()
{
	if (diskMonitor.GetStatusModule())
	{
		cout << "Мониторинг диска: ON" << endl;
	}
	else
	{
		cout << "Мониторинг диска: OFF" << endl;
	}
}