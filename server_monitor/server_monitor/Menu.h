#pragma once
#include"GetDisk.h"
#include"GetLog.h"
#include<thread>

class Menu
{
public:
	void StartModule();
	void StartDiskMonitor();
	void StopDiskMonitor();
	void GetDiskStatus();

private:
	int itemMenu;
	GetDisk diskMonitor;
	//GegLog logMonitor;

	//thread diskThread;
	//thread logThread;
};

