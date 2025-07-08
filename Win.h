#pragma once

#include <windows.h>
#include <winuser.h>
#include <windowsx.h>
#include <iostream>
#include <map>
extern int prop;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void createWindow(std::map<std::string, int>& bag);
