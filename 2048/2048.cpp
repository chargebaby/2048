// 2048.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
// #include "Struct2048.hpp"
#include "Core2048.h"

int _tmain(int argc, _TCHAR* argv[])
{

	Core2048 s;

	s.Random();
	s.Random();

 	print(s);

	do 
	{
		switch (getchar())
		{
		case 'w':
			s.Up();
			s.Random();
			print(s);
			break;

		case 'a':
			s.Left();
			s.Random();
			print(s);
			break;

		case 'd':
			s.Right();
			s.Random();
			print(s);
			break;

		case 's':
			s.Down();
			s.Random();
			print(s);
			break;

		default:
			break;
		}
	} while (true);

	return 0;
}

