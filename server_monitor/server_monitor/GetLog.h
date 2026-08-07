#pragma once
#include <thread>

class GetLog
{
public:
	GetLog();
	~GetLog();

	bool SetStatusModule(bool value);
	bool GetStatusModule();
	void StartLogMonitoring();
	void StopLogMonitoring();

private:
	bool statusModule = false;
	void GetAllLogs();
	void CheckString(const string log);
	std::thread logThread;
};

