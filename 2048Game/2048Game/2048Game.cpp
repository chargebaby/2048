// 2048Game.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <ctime>

struct Node
{
	int	 value;		//数字值
	bool null;	//是否是有效的，判断是否可以合并
};

struct Plane
{
	Node	plane[4][4];
};

static Plane  global_plane;

void InitPlane(Plane& p)
{
	Node init_node = { 0, true };

	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			p.plane[i][j] = init_node;
		}
	}
}

bool CheckPlane(const Plane& p)
{
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			if (p.plane[i][j].null)
				return true;
		}
	}

	return false;
}

bool Random2(Plane& p)
{
	srand(time(nullptr));

	do
	{
		if (!CheckPlane(p))
			return false;

		int i = abs(rand()) % 4;
		int j = abs(rand()) % 4;

		if (p.plane[i][j].null)
		{
			p.plane[i][j].value  = 2;
			p.plane[i][j].null = false;

			return true;
		}
	} while (true);
}

void Print(const Plane& p)
{
	system("cls");

	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			if (p.plane[i][j].null)
			{
				std::cout << "*";
			}
			else
			{
				std::cout << p.plane[i][j].value;
			}

			std::cout << "  ";
		}

		std::cout << std::endl;
	}
}

bool Megre(Node& n1, Node& n2)
{
	Node init_node = { 0, true };

	if (n1.null)
	{
		if (!n2.null)
		{
			n1 = n2;
			n2 = init_node;
		}
	}
	else if (!n2.null)
	{
		if (n1.value == n2.value)
		{
			n1.value += n2.value;
			n2 = init_node;

			return true;
		}
	}

	return false;
}

void Up(Plane& p)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 2; j >= 0; --j)
		{
			for (int k = j + 1; k < 4; ++k)
			{
				if (Megre(p.plane[k - 1][i], p.plane[k][i]))
					break;
			}
		}
	}
}

void Down(Plane& p)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 1; j < 4; ++j)
		{
			for (int k = j - 1; k >= 0; --k)
			{
				if (Megre(p.plane[k + 1][i], p.plane[k][i]))
					break;
			}
		}
	}
}

void Left(Plane& p)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 2; j >= 0; --j)
		{
			for (int k = j + 1; k < 4; ++k)
			{
				if (Megre(p.plane[i][k - 1], p.plane[i][k]))
					break;
			}
		}
	}
}

void Right(Plane& p)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 1; j < 4; ++j)
		{
			for (int k = j - 1; k >= 0; --k)
			{
				if (Megre(p.plane[i][k + 1], p.plane[i][k]))
					break;
			}
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	InitPlane(global_plane);

	Random2(global_plane);
	Print(global_plane);

	do
	{
		switch (getchar())
		{
		case 'w' :
		{
			Up(global_plane);

			if (!Random2(global_plane))
				return 0;

			Print(global_plane);

			break;
		}

		case 's':
		{
			Down(global_plane);

			if (!Random2(global_plane))
				return 0;

			Print(global_plane);

			break;
		}

		case 'a':
		{
			Left(global_plane);

			if (!Random2(global_plane))
				return 0;

			Print(global_plane);

			break;
		}

		case 'd':
		{
			Right(global_plane);

			if (!Random2(global_plane))
				return 0;

			Print(global_plane);

			break;
		}
		
		default:
			break;
		}

	} while (CheckPlane(global_plane));

	return 0;
}

