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
void thread_function() // ��Ϸ�߳�
{
	gc->startGame();
	int s = 1;
	while (1)
	{
		cout << "\n��" << s << "��ս��ʼ" << endl;
		//cout.flush();
		int r = gc->executePlayerAction();
		cout << "��" << s++ << "��ս����" << endl;
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
	while (1) // ���ڼ�ʱ
	{
		Sleep(1000);
		g.nowTime++;
	}
	return 0;
}