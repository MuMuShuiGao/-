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

	void keyEvent(); //�����û�����
	void updateWindow(); //��Ⱦ��Ϸ����
	//���ؾ�����һ�ε��øú����� ����˶��ٺ��루ms)
	//��һ�ε��øú���, ����0
	int getDelay();
	void drop();
	void clearLine();
	void moveLeftRight(int offset);
	void rotate();
	void drawLine();
	void checkOver();
	void saveScore();
	//������Ϸ��������
	void displayOver();
	void mouseClick(int mousex, int mousey);//���ذ���
	void mouseMove(int mousex, int mousey);
	void mouseClick1(int mousex, int mousey);//���ذ���
	void mouseMove1(int mousex, int mousey);
private:

	int delay; //��ʱʱ��
	bool update; //�Ƿ����

	std::vector<std::vector<int>> map;
	int rows;
	int cols;
	int leftMargin;
	int topMargin;
	int blockSize;
	int score;
	int level;
	int linecount;//�Ѿ�����������
	int highscore;//��ʷ��߷�
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
	Block* nextBlock; //Ԥ�淽��
	Block bakBlock; //���÷���  ��ǰ���齵������б�����һ���Ϸ�λ��
	Button* button_again;
	Button* button_continue;
	Button* button_bk;
	Button* button_back;
public:

	Tetris() = default;
};

