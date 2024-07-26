#pragma once
#include <vector>
#include <graphics.h>
#include"Button.h"
#include "Block.h"
#include "page.h"

class Tetris
{
public:
	Tetris(int rows, int cols, int left, int top, int blockSize);
	void init();
	void play();
private:

	void keyEvent(); //接收用户输入
	void updateWindow(); //渲染游戏画面
	//返回距离上一次调用该函数， 间隔了多少毫秒（ms)
	//第一次调用该函数, 返回0
	int getDelay();
	void drop();
	void clearLine();
	void moveLeftRight(int offset);
	void rotate();
	void drawLine();
	void checkOver();
	void saveScore();
	//更新游戏结束界面
	void displayOver();
	void mouseClick(int mousex, int mousey);//返回按键
	void mouseMove(int mousex, int mousey);
	void mouseClick1(int mousex, int mousey);//返回按键
	void mouseMove1(int mousex, int mousey);
private:

	int delay; //延时时间
	bool update; //是否更新

	std::vector<std::vector<int>> map;
	int rows;
	int cols;
	int leftMargin;
	int topMargin;
	int blockSize;
	int score;
	int level;
	int linecount;//已经消除多少行
	int highscore;//历史最高分
	bool gameOver;
	bool stop;
	bool backmenu;
	bool opmusic;
	int  chmusic;
	IMAGE imgOver;
	IMAGE imgWin;
	IMAGE imgBg;
	IMAGE imgback;
	Block* curBlock;
	Block* nextBlock; //预告方块
	Block bakBlock; //备用方块  当前方块降落过程中备份上一个合法位置
	Button* button_again;
	Button* button_continue;
	Button* button_bk;
	Button* button_back;
public:

	Tetris() = default;
};

