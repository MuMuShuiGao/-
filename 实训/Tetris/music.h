#pragma once
#include<fstream>
#include<graphics.h>
class music
{
public:
	int musictype;
	virtual void musicplay1()
	{
		std::ifstream File("chosemusic.txt");
		File >> musictype;
		if (musictype == 1)
		{
			mciSendString("open D:\\Code\\Tetris\\Tetris\\res\\amazing.mp3 alias song", NULL, 0, NULL);
			mciSendString("play song repeat", NULL, 0, NULL);

		}
		if (musictype == 2)
		{
			mciSendString("open D:\\Code\\Tetris\\Tetris\\res\\leave.mp3 alias song", NULL, 0, NULL);
			mciSendString("play song repeat", NULL, 0, NULL);



		}
		
	}
	
};

class gg :public music
{
public:
	virtual void musicplay2()
	{
		mciSendString("open D:\\Code\\Tetris\\Tetris\\res\\over.mp3 alias song", NULL, 0, NULL);
		mciSendString("play song ", NULL, 0, NULL);
		mciSendString("close song ", 0, 0, 0);
	}

};

class winwin :public music
{
public:
	virtual void musicplay2()
	{
		mciSendString("open D:\\Code\\Tetris\\Tetris\\res\\win.mp3 alias song", NULL, 0, NULL);
		mciSendString("play song ", NULL, 0, NULL);
		mciSendString("close song ", 0, 0, 0);
	}

};