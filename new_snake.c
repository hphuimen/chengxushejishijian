#include "snake.h"
Snake snake;
Food food, food1;
barrier b[5];
char now_dir = RIGHT;
char direction = RIGHT;

int menu()
{
	gotoxy(40, 12);
	printf("欢迎来到贪吃蛇小游戏");
	gotoxy(43, 14);
	printf("1. 开始游戏");
	gotoxy(43, 16);
	printf("2. 帮助");
	gotoxy(43, 18);
	printf("3. 关于");
	gotoxy(43, 22);
	printf("其他任意键退出游戏");
	gotoxy(43, 20);
	printf("4. 积分排行榜");
	hide();
	char ch;
	int result = 0;
	ch = _getch();
	switch (ch)
	{
	case '1':result = 1;break;
	case '2':result = 2;break;
	case '3':result = 3;break;
	case '4':result = 4;break;
	}
	system("cls");
	return result;
}

void gotoxy(int x, int y)
{
	HANDLE hout;
	COORD cor;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	cor.X = x;
	cor.Y = y;
	SetConsoleCursorPosition(hout, cor);
}

void hide()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cor_info = { 1, 0 };
	SetConsoleCursorInfo(hout, &cor_info);
}

void about()
{
	gotoxy(30, 12);
	printf("杭州电子科技大学--程序设计综合实践案例");
	gotoxy(43, 14);
	printf("贪吃蛇游戏");
	gotoxy(43, 16);
	printf("按任意键返回上级菜单");
	hide();
	char ch = _getch();
	system("cls");
}

void help()
{
	gotoxy(40, 12);
	printf("w上");
	gotoxy(40, 14);
	printf("s下");
	gotoxy(40, 16);
	printf("a左");
	gotoxy(40, 18);
	printf("d右");
	gotoxy(40, 20);
	printf("当蛇撞到自身或撞墙时游戏结束");
	gotoxy(45, 22);
	printf("按任意键返回上级菜单");
	hide();
	char ch = _getch();
	system("cls");
}

void leaderboard()
{
	FILE *fp;
	int n = 0;
	char ch1;
	if ((fp = fopen("grade.txt", "rb")) == NULL)
	{
		printf("file open error\n");
		exit(0);
	}
	while (fscanf(fp, "%d", &g[n])==1)
	{
		ch1 = fgetc(fp);
		while (ch1 != '\n')
		{
			ch1 = fgetc(fp);
		}
		n++;
	}
	for (int i = 0;i < n;i++)
	{
		f[i] = i + 1;
	}
	int t;
	for (int i = 0;i < n - 1;i++)
	{
		int k = i;
		for (int j = i + 1;j < n;j++)
		{
			if (g[j] > g[k]) k = j;
		}
		t = g[i], g[i] = g[k], g[k] = t;
		t = f[i], f[i] = f[k], f[k] = t;
	}
	for (int i = 0;i < n;i++)
	{
		gotoxy(10, (i + 1) * 2);
		printf("第%d次游戏   分数：%d   排名：%d", f[i], g[i], i + 1);
	}
	fclose(fp);
	hide();
	char ch = _getch();
	system("cls");
}
void initmap()
{
	hide();
	snake.snakenode[0].x = MAP_WIDTH / 2 - 1;
	snake.snakenode[0].y = MAP_HEIGHT / 2 - 1;
	gotoxy(snake.snakenode[0].x, snake.snakenode[0].y);
	printf("@");
	snake.length = 3;
	snake.speed = 250;
	now_dir = RIGHT;
	for (int i = 1;i < snake.length;i++)
	{
		snake.snakenode[i].y = snake.snakenode[i - 1].y;
		snake.snakenode[i].x = snake.snakenode[i - 1].x - 1;
		gotoxy(snake.snakenode[i].x, snake.snakenode[i].y);
		printf("o");
	}
	for (int i = 0;i <= MAP_WIDTH;i++)
	{
		gotoxy(i, 0);
		printf("-");
		gotoxy(i, MAP_HEIGHT - 1);
		printf("-");
	}
	for (int i = 1;i < MAP_HEIGHT - 1;i++)
	{
		gotoxy(0, i);
		printf("|");
		gotoxy(MAP_WIDTH - 1, i);
		printf("|");
	}
	initbarrier();
	printfood();
	printfood1();
	gotoxy(5, 50);
	printf("当前得分: 0");
}

void printfood()
{
	int flag = 1;
	while (flag)
	{
		flag = 0;
		food.x = rand() % (MAP_WIDTH - 2) + 1;
		food.y = rand() % (MAP_HEIGHT - 2) + 1;
		for (int k = 0;k <= snake.length - 1;k++)
		{
			if (snake.snakenode[k].x == food.x && snake.snakenode[k].y == food.y)
			{
				flag = 1;
				break;
			}
		}
		for (int i = 0;i < 5;i++)
		{
			if (b[i].x == food.x && b[i].y == food.y)
			{
				flag = 1;
				break;
			}
		}
		if (food1.x == food.x && food1.y == food.y)
		{
			flag = 1;
			break;
		}
	}
	gotoxy(food.x, food.y);
	printf("$");
}

void printfood1()
{
	int flag = 1;
	while (flag)
	{
		flag = 0;
		food1.x = rand() % (MAP_WIDTH - 2) + 1;
		food1.y = rand() % (MAP_HEIGHT - 2) + 1;
		for (int k = 0;k <= snake.length - 1;k++)
		{
			if (snake.snakenode[k].x == food1.x && snake.snakenode[k].y == food1.y)
			{
				flag = 1;
				break;
			}
		}
		for (int i = 0;i < 5;i++)
		{
			if (b[i].x == food1.x && b[i].y == food1.y)
			{
				flag = 1;
				break;
			}
		}
		if (food1.x == food.x && food1.y == food.y)
		{
			flag = 1;
			break;
		}
	}
	gotoxy(food1.x, food1.y);
	printf("2");
}

int movesnake()
{
	Snakenode temp;
	int flag = 0;
	temp = snake.snakenode[snake.length - 1];
	for (int i = snake.length - 1;i >= 1;i--)
	{
		snake.snakenode[i] = snake.snakenode[i - 1];
	}
	gotoxy(snake.snakenode[1].x, snake.snakenode[1].y);
	printf("o");
	if (_kbhit())
	{
		direction = _getch();
		switch (direction)
		{
		case UP:
			if (now_dir != DOWN)
				now_dir = direction;
			break;
		case DOWN:
			if (now_dir != UP)
				now_dir = direction;
			break;
		case LEFT:
			if (now_dir != RIGHT)
				now_dir = direction;
			break;
		case RIGHT:
			if (now_dir != LEFT)
				now_dir = direction;
			break;
		}
	}
	switch (now_dir)
	{
	case UP:snake.snakenode[0].y--;break;
	case DOWN:snake.snakenode[0].y++;break;
	case LEFT:snake.snakenode[0].x--;break;
	case RIGHT:snake.snakenode[0].x++;break;
	}
	gotoxy(snake.snakenode[0].x, snake.snakenode[0].y);
	printf("@");

	if (snake.snakenode[0].x == food.x && snake.snakenode[0].y == food.y)
	{
		snake.length++;
		flag = 1;
		snake.snakenode[snake.length - 1] = temp;
		printfood();
		gotoxy(50, 5);
		printf("当前得分: %d", snake.length - 3);
	}
	if (snake.snakenode[0].x == food1.x && snake.snakenode[0].y == food1.y)
	{
		snake.length++;
		flag = 1;
		snake.snakenode[snake.length - 1] = temp;
		snake.length++;
		if (snake.snakenode[snake.length - 3].x == temp.x && snake.snakenode[snake.length - 3].y - 1 == temp.y)
			snake.snakenode[snake.length - 1].x = temp.x, snake.snakenode[snake.length - 1].y = temp.y - 1;
		if (snake.snakenode[snake.length - 3].x == temp.x && snake.snakenode[snake.length - 3].y + 1 == temp.y)
			snake.snakenode[snake.length - 1].x = temp.x, snake.snakenode[snake.length - 1].y = temp.y + 1;
		if (snake.snakenode[snake.length - 3].x - 1 == temp.x && snake.snakenode[snake.length - 3].y == temp.y)
			snake.snakenode[snake.length - 1].x = temp.x - 1, snake.snakenode[snake.length - 1].y = temp.y;
		if (snake.snakenode[snake.length - 3].x + 1 == temp.x && snake.snakenode[snake.length - 3].y == temp.y)
			snake.snakenode[snake.length - 1].x = temp.x + 1, snake.snakenode[snake.length - 1].y = temp.y;
		if (!iscorrect())
		{
			input_grade();
			system("cls");
			gotoxy(45, 14);
			printf("最终得分: %d", snake.length - 3);
			gotoxy(45, 16);
			printf("你输了！");
			gotoxy(45, 18);
			printf("按任意键返回主菜单");
			char c = _getch();
			system("cls");
			return 0;
		}
		gotoxy(snake.snakenode[snake.length - 1].x, snake.snakenode[snake.length - 1].y);
		printf("o");
		printfood1();
		gotoxy(50, 5);
		printf("当前得分: %d", snake.length - 3);
	}
	if (!flag)
	{
		gotoxy(temp.x, temp.y);
		printf(" ");
	}

	int w = 0;
	for (int i = 1;i < snake.length;i++)
	{
		if (snake.snakenode[0].x == snake.snakenode[i].x && snake.snakenode[0].y == snake.snakenode[i].y)
		{
			w = i;
			break;
		}
	}
	if (w != 0)
	{
		for (int i = w + 1;i < snake.length;i++)
		{
			gotoxy(snake.snakenode[i].x, snake.snakenode[i].y);
			printf(" ");
		}
		snake.length = w;
		gotoxy(50, 5);
		printf("                      ");
		gotoxy(50, 5);
		printf("当前得分: %d", snake.length - 3);
	}


	if (!iscorrect())
	{
		input_grade();
		system("cls");
		gotoxy(45, 14);
		printf("最终得分: %d", snake.length - 3);
		gotoxy(45, 16);
		printf("你输了！");
		gotoxy(45, 18);
		printf("按任意键返回主菜单");
		char c = _getch();
		system("cls");
		return 0;
	}
	speedcontrol();
	Sleep(snake.speed);
	return 1;
}

int iscorrect()
{
	if (snake.snakenode[0].x == 0 || snake.snakenode[0].y == 0 || snake.snakenode[0].x == MAP_WIDTH - 1 || snake.snakenode[0].y == MAP_HEIGHT - 1)
		return 0;
	for (int i = 0;i < 5;i++)
	{
		if (b[i].x == snake.snakenode[0].x && b[i].y == snake.snakenode[0].y)
			return 0;
	}
	return 1;
}

void speedcontrol()
{
	switch (snake.length)
	{
	case 6:snake.speed = 200;break;
	case 9:snake.speed = 180;break;
	case 12:snake.speed = 160;break;
	case 15:snake.speed = 140;break;
	case 18:snake.speed = 120;break;
	case 21:snake.speed = 100;break;
	case 24:snake.speed = 80;break;
	case 27:snake.speed = 60;break;
	case 30:snake.speed = 40;break;
	default:break;
	}
}

void initbarrier()
{
	for (int i = 0;i < 5;i++)
	{
		int flag = 1;
		while (flag)
		{
			flag = 0;
			b[i].x = rand() % (MAP_WIDTH - 2) + 1;
			b[i].y = rand() % (MAP_HEIGHT - 2) + 1;
			for (int k = 0;k < snake.length - 1;k++)
			{
				if (snake.snakenode[k].x == b[i].x && snake.snakenode[k].y == b[i].y)
				{
					flag = 1;
					break;
				}
			}
			for (int j = 0;j < i;j++)
			{
				if (b[j].x == b[i].x && b[j].y == b[i].y)
				{
					flag = 1;
					break;
				}
			}
		}
		gotoxy(b[i].x, b[i].y);
		printf("#");
	}
}

void input_grade()
{
	FILE* fp;
	if ((fp = fopen("grade.txt", "ab")) == NULL)
	{
		printf("file open error\n");
		exit(0);
	}
	fprintf(fp, "%d\n", snake.length - 3);
	fclose(fp);
}
