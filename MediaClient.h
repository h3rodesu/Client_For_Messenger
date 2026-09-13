#pragma once
#include<string>
#include<WinSock2.h>
class Media {
public:
	static std::string OpenFileDialog(HWND hwnd);//хэндл для привязки окна проводника
	static void sendImg(const std::string& smthPicture, SOCKET UserSocket);
private:
	Media() = default;
};