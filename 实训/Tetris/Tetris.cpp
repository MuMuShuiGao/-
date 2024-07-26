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
	button_back = new Button(12, 12, 100, 50, "返回", [&]() {
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
	//初始化游戏区中的数据
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
	//初始化最高分

	std::ifstream file("highestscore.txt");
	if (!file.is_open())
	{
		std::cout << "打开失败" << std::endl;
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
		//easyx的点击功能
		ExMessage msg;
		if (peekmessage(&msg)) // 检查是否有消息
		{
			int mouseX = msg.x; // 获取鼠标x坐标
			int mouseY = msg.y; // 获取鼠标y坐标

			switch (msg.message)
			{
			case WM_LBUTTONDOWN: // 鼠标左键按下事件
				mouseClick(mouseX, mouseY); // 处理鼠标点击事件
				break;
			case WM_MOUSEMOVE: // 鼠标移动事件
				mouseMove(mouseX, mouseY); // 处理鼠标移动事件
				break;
			}
			FlushBatchDraw(); // 将缓冲区内容显示在屏幕上
			Sleep(10);
		}

		if (backmenu)
		{
			return ;
		}


		if (stop == 1)
		{

			putimage(85, 0, &imgback);
			button_continue = new Button(150, 100, 400, 138, "继续游戏", [&]() {
				std::cout << "*****请继续游戏*****"<<std::endl;
				stop = 0;

				});
			button_continue->draw();
			button_again = new Button(150, 300, 400, 138, "重新开始", [&]() {
				std::cout << "*****请重新开始*****" << std::endl;
				stop = 0;	
				play();
				});
			button_again->draw();
			button_bk = new Button(150, 500, 400, 138, "返回菜单", [&]() {
				std::cout << "*****已返回主菜单*****" << std::endl;
				backmenu=1; // 点击按钮1时，切换回页面0
				stop = 0;
				});
			button_bk->draw();
			//easyx的点击功能
			while (true)
			{
				if (stop == 0)
				{
					break;
				}
				ExMessage msg;
				if (peekmessage(&msg)) // 检查是否有消息
				{
					int mouseX = msg.x; // 获取鼠标x坐标
					int mouseY = msg.y; // 获取鼠标y坐标
					
					switch (msg.message)
					{
					case WM_LBUTTONDOWN: // 鼠标左键按下事件
						mouseClick1(mouseX, mouseY); // 处理鼠标点击事件
						
						break;
					case WM_MOUSEMOVE: // 鼠标移动事件
						mouseMove1(mouseX, mouseY); // 处理鼠标移动事件
						break;
					}
					FlushBatchDraw(); // 将缓冲区内容显示在屏幕上
					Sleep(10);
				}
			}
		}




		//接受用户按键输入
		keyEvent();

		//算时间

		timer += getDelay();
		checkOver();
		if (timer > delay)
		{
			timer = 0;
			//掉落方块
			drop();
			update = true;
		}
		if (update)
		{
			update = 0;
			//渲染游戏画面
			updateWindow();
			//更新游戏数据
			clearLine();
		}
		if (gameOver)
		{
			//保存分数
			saveScore();
			//更新游戏结束界面
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
			// 如果按下 向上方向键, 会先后返回: 224, 72
		   // 如果按下 向下方向键, 会先后返回: 224, 80
		   // 如果按下 向左方向键, 会先后返回: 224, 75
		   // 如果按下 向右方向键, 会先后返回: 224, 77
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
	//绘制背景图片
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
	//预告方块
	nextBlock->draw(689 * 0.8, 150 * 1.1);
	drawLine();//分数关卡等等
	EndBatchDraw();


}

int Tetris::getDelay()
{
	//第一次调用返回0，返回距离上一次调用间隔多少ms
	static unsigned long long lastTime = 0;
	//系统时钟
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
	//备用方块  当前方块降落过程中备份上一个合法位置
	bakBlock = *curBlock;
	curBlock->drop();
	if (!curBlock->blockInMap(map))
	{
		//把这个方块固化
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
	int k = rows - 1;//存储数据的行数
	for (int i = rows - 1; i >= 0; i--)
	{
		//检查第i行是否满行
		int count = 0;
		for (int j = 0; j < cols; j++)
		{
			if (map[i][j])
			{
				count++;
			}
			map[k][j] = map[i][j];//一边扫描一边存储
		}
		if (count < cols)
		{
			k--;
			//不是满行
		}
		else
		{

			//mciSendString(_T("open D:\\Code\\Tetris\\Tetris\\res\\xiaochu1.mp3 alias bkmusic"), NULL, 0, NULL);//播放音乐
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
		// mciSendString(_T("open D:\\Code\\Tetris\\Tetris\\res\\xiaochu1.mp3 alias bkmusic"), NULL, 0, NULL);//播放音乐
		//mciSendString(_T("play bkmusic "), NULL, 0, NULL);
		//计算得分
		int addScore[4] = { 10,30,60,80 };
		score += addScore[lines - 1];
		update = true;
		//关卡
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
	gettextstyle(&f);//获取字体
	f.lfHeight = 90;
	f.lfWidth = 45;
	f.lfQuality = ANTIALIASED_QUALITY;//抗锯齿效果
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("Segoe UI Black"));
	settextstyle(&f);

	setbkmode(TRANSPARENT);//字体背景设置透明

	//outtextxy(443, 257, scoreText);

	////绘制消除多少行
	sprintf_s(scoreText, sizeof(scoreText), "%d", linecount);
	gettextstyle(&f);
	outtextxy(689 * 0.8, 150 * 2, scoreText);

	//////绘制当前关数
	sprintf_s(scoreText, sizeof(scoreText), "%d", level);
	outtextxy(689 * 0.8, 150 * 2.65, scoreText);

	//////绘制当前最高分
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

