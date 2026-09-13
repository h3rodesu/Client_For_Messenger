#define NOMINMAX
#include "MediaClient.h"
#include "httplib.h"
#include <commdlg.h>
#include<vector>
#include<fstream>
#include<iostream>
#pragma comment (lib, "Comdlg32.lib")

std::string Media::OpenFileDialog(HWND hwnd) {
	OPENFILENAMEA opfn = { 0 };//структура для проводника
	char FilePath[260] = { 0 };//путь к файлу
	opfn.lStructSize = sizeof(opfn);
	opfn.hwndOwner = hwnd;
	opfn.lpstrFile = FilePath;
	opfn.nMaxFile = sizeof(FilePath);
	opfn.lpstrFilter = "Изображение (*.jpg;*.jpeg;*.png)\0*.jpg;*.jpeg;*.png\0";
	opfn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	opfn.nFilterIndex = 1;
	if (GetOpenFileNameA(&opfn) == true) {
		return std::string(FilePath);
}
	else {
		return "";
	}
}
void Media::sendImg(const std::string& path, SOCKET UserSocket) {
	if (path.empty()) {
		return;
	}
	std::ifstream file(path, std::ios::binary | std::ios::ate);
	if (!file.is_open()) {
		return;
	}
	std::streamsize sizeFile = file.tellg();//т.к. курсор в конце
	file.seekg(0, std::ios::beg);
	std::vector<char>myBuf(sizeFile);
	if (!file.read(myBuf.data(), sizeFile)) {
		return;
	}
	file.close();//если успех
	httplib::Client cli("127.0.0.1", 8081);
	auto res = cli.Post("/upload", myBuf.data(), myBuf.size(), "image/jpeg");
	if (res && res->status == 200) {
		std::string servFilePath = res->body;
		std::string fullimgstr = "MSG|IMG|" + servFilePath + "\n";
		send(UserSocket, fullimgstr.c_str(), (int)fullimgstr.size(), 0);
	}
	else {
		return;
	}
}