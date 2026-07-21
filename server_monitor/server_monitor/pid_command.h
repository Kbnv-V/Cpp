#pragma once
//#include "Menu.h"

class Menu;
extern Menu* pMenu = nullptr;

//функция для записи pid 
void WritePid();

//функция для удаления pid файла
void DeletePid();

//чтение pid в файле
int ReadPid();

//обработчики сигналов
void SignalHandler(int signal);