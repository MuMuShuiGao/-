#include "Tetris.h"
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <iostream>
#include "Button.h"
//music
#include <mmsystem.h>
#include "page.h"
#include "music.h"

#pragma comment(lib,"Winmm.lib")
const int SPEED_NORMAL = 500; //ms
const int SPEED_QUICK = 50; //ms

Tetris::Tetris(int rows, int cols, int left, int top, int blockSize)
{
	this->rows = rows;
	this->cols = cols;
	this->leftMargin = left;
	this->topMargin = top;
	this->blockSize = blockSize;

	for (int i = 0; i < rows; i++)
	{
		std::vector<int>mapRow;
		for (int j = 0; j < cols; j++)
		{
			mapRow.push_back(0);
		}
		map.push_back(mapRow);
	}
}

void Tetris::init()
{

	delay = SPEED_NORMAL;
	button_back = new Button(12, 12, 100, 50, "����", [&]() {
		stop = true;
		});
	srand((unsigned int)time(NULL));
	music bg;
	
	std::ifstream File8("openmusic.txt");
	File8 >> opmusic;
	std::ifstream File6("chosemusic.txt");
	File6 >> bg.musictype;
	std::cout << bg.musictype;
	if (opmusic)
	{
		bg.musicplay1();
	}

	loadimage(&imgBg, "D:\\Code\\Tetris\\Tetris\\res\\gamebg.png");
	//loadimage(&imgWin, "C:\\Users\\23026\\Desktop\\.png");
	loadimage(&imgOver, "D:\\Code\\Tetris\\Tetris\\res\\gameover.png");
	loadimage(&imgback, "D:\\Code\\Tetris\\Tetris\\res\\bg3.png");
	//��ʼ����Ϸ���е�����
	char data[20][20];
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)

		{
			map[i][j] = 0;
		}
	}
	score = 0;
	level = 1;
	linecount = 0;
	gameOver = 0;
	stop = false;
	backmenu=0;
	//��ʼ����߷�

	std::ifstream file("highestscore.txt");
	if (!file.is_open())
	{
		std::cout << "��ʧ��" << std::endl;
	}
	else
	{
		file >> highscore;
	}
	file.close();
}

void Tetris::play()
{
	init();
	nextBlock = new Block;
	curBlock = nextBlock;
	nextBlock = new Block;
	int timer = 0;
	while (1)
	{
		//easyx�ĵ������
		ExMessage msg;
		if (peekmessage(&msg)) // ����Ƿ�����Ϣ
		{
			int mouseX = msg.x; // ��ȡ���x����
			int mouseY = msg.y; // ��ȡ���y����

			switch (msg.message)
			{
			case WM_LBUTTONDOWN: // �����������¼�
				mouseClick(mouseX, mouseY); // ����������¼�
				break;
			case WM_MOUSEMOVE: // ����ƶ��¼�
				mouseMove(mouseX, mouseY); // ��������ƶ��¼�
				break;
			}
			FlushBatchDraw(); // ��������������ʾ����Ļ��
			Sleep(10);
		}

		if (backmenu)
		{
			return ;
		}


		if (stop == 1)
		{

			putimage(85, 0, &imgback);
			button_continue = new Button(150, 100, 400, 138, "������Ϸ", [&]() {
				std::cout << "*****�������Ϸ*****"<<std::endl;
				stop = 0;

				});
			button_continue->draw();
			button_again = new Button(150, 300, 400, 138, "���¿�ʼ", [&]() {
				std::cout << "*****�����¿�ʼ*****" << std::endl;
				stop = 0;	
				play();
				});
			button_again->draw();
			button_bk = new Button(150, 500, 400, 138, "���ز˵�", [&]() {
				std::cout << "*****�ѷ������˵�*****" << std::endl;
				backmenu=1; // �����ť1ʱ���л���ҳ��0
				stop = 0;
				});
			button_bk->draw();
			//easyx�ĵ������
			while (true)
			{
				if (stop == 0)
				{
					break;
				}
				ExMessage msg;
				if (peekmessage(&msg)) // ����Ƿ�����Ϣ
				{
					int mouseX = msg.x; // ��ȡ���x����
					int mouseY = msg.y; // ��ȡ���y����
					
					switch (msg.message)
					{
					case WM_LBUTTONDOWN: // �����������¼�
						mouseClick1(mouseX, mouseY); // ����������¼�
						
						break;
					case WM_MOUSEMOVE: // ����ƶ��¼�
						mouseMove1(mouseX, mouseY); // ��������ƶ��¼�
						break;
					}
					FlushBatchDraw(); // ��������������ʾ����Ļ��
					Sleep(10);
				}
			}
		}




		//�����û���������
		keyEvent();

		//��ʱ��

		timer += getDelay();
		checkOver();
		if (timer > delay)
		{
			timer = 0;
			//���䷽��
			drop();
			update = true;
		}
		if (update)
		{
			update = 0;
			//��Ⱦ��Ϸ����
			updateWindow();
			//������Ϸ����
			clearLine();
		}
		if (gameOver)
		{
			//�������
			saveScore();
			//������Ϸ��������
			displayOver();
			putimage(0, 0, &imgOver);
			/*gg g;
			g.musicplay2();*/
			system("pause");
			init();


		}
	}

}


void Tetris::keyEvent()
{
	unsigned char ch;
	bool rotateFlag = false;
	int dx = 0;

	if (_kbhit())
	{
		ch = _getch();
		if (Page::key == 0)
		{
			// ������� ���Ϸ����, ���Ⱥ󷵻�: 224, 72
		   // ������� ���·����, ���Ⱥ󷵻�: 224, 80
		   // ������� �������, ���Ⱥ󷵻�: 224, 75
		   // ������� ���ҷ����, ���Ⱥ󷵻�: 224, 77
			if (ch == 224)
			{
				ch = _getch();
				switch (ch)
				{
				case 72:
					rotateFlag = true;
					break;
				case 80:
					delay = SPEED_QUICK;
					break;
				case 75:
					dx = -1;
					break;
				case 77:
					dx = 1;
					break;
				default:
					break;
				}
			}
			
		}
		else
		{
			switch (ch)
			{
			case 119:
				rotateFlag = true;
				break;
			case 115:
				delay = SPEED_QUICK;
				break;
			case 97:
				dx = -1;
				break;
			case 100:
				dx = 1;
				break;
			default:
				break;
			}

		}

		
	}

	if (rotateFlag)
	{
		rotate();
		update = true;
	}

	if (dx != 0)
	{
		moveLeftRight(dx);
		update = true;
	}
}

void Tetris::updateWindow()
{
	//���Ʊ���ͼƬ
	putimage(0, 0, &imgBg);
	button_back->draw();

	IMAGE** imgs = Block::getImage();
	BeginBatchDraw();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (map[i][j] == 0)
			{
				continue;
			}
			else
			{
				int x = leftMargin + j * blockSize;
				int y = topMargin + i * blockSize;
				putimage(x, y, imgs[map[i][j] - 1]);
			}
		}
	}
	curBlock->draw(leftMargin, topMargin);
	//Ԥ�淽��
	nextBlock->draw(689 * 0.8, 150 * 1.1);
	drawLine();//�����ؿ��ȵ�
	EndBatchDraw();


}

int Tetris::getDelay()
{
	//��һ�ε��÷���0�����ؾ�����һ�ε��ü������ms
	static unsigned long long lastTime = 0;
	//ϵͳʱ��
	unsigned long long currentTime = GetTickCount();
	if (lastTime == 0)
	{
		lastTime = currentTime;
		return 0;
	}
	else
	{
		int ret = (int)(currentTime - lastTime);
		lastTime = (int)currentTime;
		return ret;
	}

}

void Tetris::drop()
{
	//���÷���  ��ǰ���齵������б�����һ���Ϸ�λ��
	bakBlock = *curBlock;
	curBlock->drop();
	if (!curBlock->blockInMap(map))
	{
		//���������̻�
		bakBlock.solidify(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;
	}

	delay = SPEED_NORMAL;

}

void Tetris::clearLine()
{
	int lines = 0;
	int k = rows - 1;//�洢���ݵ�����
	for (int i = rows - 1; i >= 0; i--)
	{
		//����i���Ƿ�����
		int count = 0;
		for (int j = 0; j < cols; j++)
		{
			if (map[i][j])
			{
				count++;
			}
			map[k][j] = map[i][j];//һ��ɨ��һ�ߴ洢
		}
		if (count < cols)
		{
			k--;
			//��������
		}
		else
		{

			//mciSendString(_T("open D:\\Code\\Tetris\\Tetris\\res\\xiaochu1.mp3 alias bkmusic"), NULL, 0, NULL);//��������
			//mciSendString(_T("play bkmusic "), NULL, 0, NULL);
			//std::cout << 1;
			//mciSendString(_T("close bkmusic "), NULL, 0, NULL);

			lines++;
			linecount++;
		}
	}
	if (lines > 0)
	{
		//mciSendString("D:\\Code\\Tetris\\Tetris\\res\\xiaochu1.mp3", 0, 0, 0);
		// mciSendString(_T("open D:\\Code\\Tetris\\Tetris\\res\\xiaochu1.mp3 alias bkmusic"), NULL, 0, NULL);//��������
		//mciSendString(_T("play bkmusic "), NULL, 0, NULL);
		//����÷�
		int addScore[4] = { 10,30,60,80 };
		score += addScore[lines - 1];
		update = true;
		//�ؿ�
		level = (score + 99) / 100;
		if (level > 5)
		{
			gameOver = 1;
		}
		

	}

}

void Tetris::moveLeftRight(int offset)
{
	bakBlock = *curBlock;
	curBlock->moveLeftRight(offset);

	if (!curBlock->blockInMap(map))
	{
		*curBlock = bakBlock;
	}

}

void Tetris::rotate()
{
	if (curBlock->getBlockType() == 7) return;

	bakBlock = *curBlock;
	curBlock->rotate();

	if (!curBlock->blockInMap(map))
	{
		*curBlock = bakBlock;
	}
}

void Tetris::drawLine()
{
	char scoreText[32];
	setcolor(RGB(29, 40, 115));

	LOGFONT f;
	gettextstyle(&f);//��ȡ����
	f.lfHeight = 90;
	f.lfWidth = 45;
	f.lfQuality = ANTIALIASED_QUALITY;//�����Ч��
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("Segoe UI Black"));
	settextstyle(&f);

	setbkmode(TRANSPARENT);//���屳������͸��

	//outtextxy(443, 257, scoreText);

	////��������������
	sprintf_s(scoreText, sizeof(scoreText), "%d", linecount);
	gettextstyle(&f);
	outtextxy(689 * 0.8, 150 * 2, scoreText);

	//////���Ƶ�ǰ����
	sprintf_s(scoreText, sizeof(scoreText), "%d", level);
	outtextxy(689 * 0.8, 150 * 2.65, scoreText);

	//////���Ƶ�ǰ��߷�
	sprintf_s(scoreText, sizeof(scoreText), "%d", highscore);
	outtextxy(689 * 0.8, 150 * 3.2, scoreText);

}

void Tetris::checkOver()
{
	gameOver = (curBlock->blockInMap(map) == 0);
}

void Tetris::saveScore()
{
	if (score > highscore)
	{
		highscore = score;
		std::ofstream file("highestscore.txt");
		file << highscore;
		file.close();
		std::ofstream File("rank.txt", std::ios::app);
		File << highscore << "\t";
		File.close();
	}

}

void Tetris::displayOver()
{
	//mciSendString("", 0, 0, 0);
	if (level <= 5)
	{
		//putimage(262, 361, &imgOver);
	}
	else
	{
		//putimage(262, 361, &imgWin);
	}

}

void Tetris::mouseClick(int mousex, int mousey)
{
	button_back->checkClick(mousex, mousey);

}

void Tetris::mouseMove(int mousex, int mousey)
{
	button_back->checkMouseOver(mousex, mousey);

}

void Tetris::mouseClick1(int mousex, int mousey)
{
	button_bk->checkClick(mousex, mousey);
	button_continue->checkClick(mousex, mousey);
	button_again->checkClick(mousex, mousey);
}

void Tetris::mouseMove1(int mousex, int mousey)
{
	button_bk->checkMouseOver(mousex, mousey);
	button_continue->checkMouseOver(mousex, mousey);
	button_again->checkMouseOver(mousex, mousey);
}

