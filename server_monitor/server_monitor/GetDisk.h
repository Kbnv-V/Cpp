#include<iostream>
#include<thread>

class GetDisk
{
public:
	GetDisk();
	~GetDisk();

	bool SetStatusModule(bool value);
	bool GetStatusModule();
	void StartDiskMonitoring();
	void StopDiskMonitoring();

private:
	bool statusModule = false;
	void GetFreeSpace();
	void Pause();
	std::thread diskThread;
};

