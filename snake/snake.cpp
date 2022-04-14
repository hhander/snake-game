// snake.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<stdio.h>
#include <iostream>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#include<easyx.h>

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

#define SNACK_NUM 500


enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};



struct Snake
{
	int size;
	int dir;
	int speed;
	POINT coor[SNACK_NUM];
}snake;

struct food
{

	int x;
	int y;
	int r;//食物大小
	DWORD color;
	bool flag;//食物是否被吃

}food;

void GameDraw()
{
	BeginBatchDraw();
	setbkcolor(RGB(28, 115, 119));
	cleardevice();
	setfillcolor(GREEN);
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	if (food.flag)
	{
		solidcircle(food.x, food.y, 5);
	}


	EndBatchDraw();
}


void GameInit()
{
	initgraph(640, 480/*,SHOWCONSOLE*/);
	/*srand((unsigned int)time(NULL));*/
	srand(GetTickCount());
	snake.size = 3;
	snake.speed = 10;
	snake.dir = RIGHT;
	for (int i = 0; i < snake.size; i++)
	{
		snake.coor[i].x = 40 - 10 * i;
		snake.coor[i].y = 10;
		/*	printf("%d%d", snake.coor[i].x, snake.coor[i].y);*/
	}
	//snake.coor[0].x = 40;
	//snake.coor[0].y = 10;
	//snake.coor[1].x = 30;
	//snake.coor[1].y = 10;
	//snake.coor[2].x = 20;
	//snake.coor[2].y = 10;


	//食物

	food.x = rand() % 640 + 1;
	food.y = rand() % 480 + 1;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = rand() % 10 + 5;
	food.flag = true;
}

void SnakeMove()
{
	for (int i = snake.size - 1; i > 0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
		switch (snake.dir)
		{
		case UP:
			snake.coor[0].y-=snake.speed;
			if (snake.coor[0].y+10 <= 0)
			{
				snake.coor[0].y = 480;
			}
			break;
		case DOWN:
			snake.coor[0].y+= snake.speed;
			if (snake.coor[0].y-10 >= 480)
			{
				snake.coor[0].y = 0;
			}
			break;
		case LEFT:
			snake.coor[0].x-= snake.speed;
			if (snake.coor[0].x+10 <= 0)
			{
				snake.coor[0].x = 640;
			}
			break;
		case RIGHT:
			snake.coor[0].x+= snake.speed;
			if (snake.coor[0].x-10 >= 640)
			{
				snake.coor[0].x = 0;
			}
			break;
		}

}
		

void KeyControl()
{
	if (_kbhit())//检测有无按键 有按键返回真
	{
		switch (_getch())
		{
		case 'w':
		case 'W':
		case 72:
			if (snake.dir != DOWN)
			{
				snake.dir = UP;
			}
			break;
		case 's':
		case 'S':
		case 80:
			if (snake.dir != UP)
			{
				snake.dir = DOWN;
			}
			break;
		case 'A':
		case 'a':
		case 75:
			if (snake.dir != RIGHT)
			{
				snake.dir = LEFT;
			}
			break;
		case 'd':
		case 'D':
		case 77:
			if (snake.dir != LEFT)
			{
				snake.dir = RIGHT;
			}
			break;
		case ' ':
		{
			while (1)
			{
				if (_getch() == ' ')
					break;
			}
		}
		}
	}
}

void EatFood()
{
	if (food.flag&&snake.coor[0].x >= food.x-food.r && snake.coor[0].x <= food.x+food.r
		&&snake.coor[0].y<=food.y+food.r&& snake.coor[0].y>=food.y - food.r)
	{
		food.flag = false;
		snake.size++;
	}
	if (!food.flag)
	{
		food.x = rand() % 640 + 1;
		food.y = rand() % 480 + 1;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = rand() % 10 + 5;
		food.flag = true;

	}

}





int main()
{
	GameInit();
	

	while (1)
	{
	
		SnakeMove();
		GameDraw();
		KeyControl();
		EatFood();
		Sleep(50);
		
	}


	return 0;
}