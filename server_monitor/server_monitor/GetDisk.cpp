#pragma once
#include "GetDisk.h"
#include "iostream"
#include "filesystem"
#include "chrono"
#include<thread>
#include<ctime>
#include <fstream>

using namespace std;
using namespace chrono;

GetDisk::GetDisk()
{
	setlocale(LC_ALL, "ru-RU.UTF-8");
}

GetDisk::~GetDisk()
{
	StopDiskMonitoring();
}

bool GetDisk::SetStatusModule(bool value)
{
	statusModule = value;

	return true;
}

bool GetDisk::GetStatusModule()
{
	return statusModule;
}

void GetDisk::Pause()
{
	cout << "Pause" << endl;
	this_thread::sleep_for(milliseconds(3000)); // Пауза для тестирования

	/*
	auto nowTime = system_clock::now(); //получаем текущее время
	nowTime = nowTime + chrono::hours(3); // КОСТЫЛЬ!!! system_clock::now отдает время меньше на 3 часа, чем на компе
	
	//cout << "Текущее время [nowTime] - " << nowTime << endl;

	//тут формируем время, с которым потом будет сравнивать текущее
	auto today = floor<days>(nowTime); //округляем до указанных единиц
	auto todayStart = today + hours(10); 
	auto tomorrowStart = todayStart + hours(24);

	system_clock::time_point resTime;

	if (nowTime < todayStart)
	{
		resTime = todayStart;
	}
	else
	{
		resTime = tomorrowStart;
	}

	//cout << "До следующего запуска осталось " << duration_cast<hours>(resTime - nowTime).count() << " ч. " << duration_cast<minutes>(resTime - nowTime).count() % 60 << " мин." << "\n";

	this_thread::sleep_until(resTime);
	*/
}

void GetDisk::GetFreeSpace()
{
	ofstream test("test.txt");
	int i = 0;

	while (statusModule)
	{
		//ИЗМЕНИТЬ ПУТЬ
		auto info = filesystem::space("C:\\");

		double freeGb = info.free / 1073741824.00;

		stringstream strFreeGb;
		strFreeGb << freeGb;
		string stringFreeGb = strFreeGb.str();

		//string command = "php /home/bitrix/www/local/check_disk/send_mess.php " + stringFreeGb;

		// Вывод для тестирования
		cout << "Свободное место на диске C - " << freeGb << endl;

		if (test.is_open())
		{
			i++;
			test << "Лог №" << i << endl;
		}

		Pause();
	}
}

void GetDisk::StartDiskMonitoring()
{
	statusModule = true;

	diskThread = thread([this] {GetFreeSpace();}); //в параметр передаем this, а теле выполняем метод
	//diskThread.join();

	cout << "Служба мониторинга свободного места на диске успешно запущена!" << endl;
}

void GetDisk::StopDiskMonitoring()
{
	statusModule = false;

	if (diskThread.joinable())
	{
		diskThread.join();
	}

	cout << "Служба мониторинга свободного места на диске успешно остановлена!" << endl;
}

