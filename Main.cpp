#include <iostream>
#include <string>
#include <thread>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <winuser.h>
#include <windowsx.h>
#include "Enemy.h"
#include "GameController.h"
using namespace std;
GameController* gc = NULL;
void creat_thread();
void thread_function() // 游戏线程
{
	gc->startGame();
	int s = 1;
	while (1)
	{
		cout << "\nBattle " << s << " begins" << endl;
		//cout.flush();
		int r = gc->executePlayerAction();
		cout << "Battle " << s++ << " ends" << endl;
		if (r == 1)
		{
			creat_thread();
			break;
		}
		else if (r == 4) {
			s = 1;
		}
	}
}
void creat_thread()
{
	thread t(thread_function);
	t.detach();
}
int main()
{
	GameController g;
	gc = &g;
	creat_thread();
	while (1) // 用于计时
	{
		Sleep(1000);
		g.nowTime++;
	}
	return 0;
}