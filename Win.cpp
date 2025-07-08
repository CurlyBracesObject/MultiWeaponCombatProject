#include <windows.h>
#include <winuser.h>
#include <windowsx.h>
#include <iostream>
#include <string>
#include <thread>
#include <stdlib.h>
#include <conio.h>
#include "Enemy.h"
#include "GameController.h"
#include <map>
using namespace std;

const char CLASS_NAME[] = "Sample Window Class";
int prop = -1;
WNDCLASS wc = {};
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 1000:
		{
			prop = 0;
			DestroyWindow(hwnd);
			UnregisterClass(wc.lpszClassName, wc.hInstance);
			return 0;
		}
		//break;
		case 1001:
		{
			prop = 1;
			DestroyWindow(hwnd);
			UnregisterClass(wc.lpszClassName, wc.hInstance);
			return 0;
		}
		//break;
		case 1002:
		{
			prop = 2;
			DestroyWindow(hwnd);
			UnregisterClass(wc.lpszClassName, wc.hInstance);
			return 0;
		}
		//break;
		case 2000:
		{
			DestroyWindow(hwnd);
			UnregisterClass(wc.lpszClassName, wc.hInstance);
			return 0;
		}
		//break;
		//return 0;
		}
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

//创建窗口
void createWindow(std::map<std::string, int>& bag) {

	wc.lpfnWndProc = WindowProcedure;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = CLASS_NAME;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClass(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	HWND hwnd = CreateWindowEx(0, CLASS_NAME, TEXT("Bag"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 120, NULL, NULL, GetModuleHandle(NULL), NULL);
	if (hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return;
	}
	CreateWindow("BUTTON", "cancel", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 190, 50, 120, 30, hwnd, (HMENU)2000, GetModuleHandle(NULL), NULL);
	// 根据背包的内容创建按钮
	auto it = bag.begin();
	int x = 10;
	for (; it != bag.end(); it++) {
		std::string text = it->first + "x" + to_string(it->second);
		if (it->first.compare("EnergyShield") == 0) {
			CreateWindow("BUTTON", text.c_str(), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, x, 10, 120, 30, hwnd, (HMENU)1000, GetModuleHandle(NULL), NULL);
		}
		else if (it->first.compare("potion") == 0) {
			CreateWindow("BUTTON", text.c_str(), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, x, 10, 120, 30, hwnd, (HMENU)1001, GetModuleHandle(NULL), NULL);
		}
		else if (it->first.compare("Medical") == 0) {
			CreateWindow("BUTTON", text.c_str(), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, x, 10, 120, 30, hwnd, (HMENU)1002, GetModuleHandle(NULL), NULL);
		}
		x += 120;
	}
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


