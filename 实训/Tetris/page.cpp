#include"Button.h"
#include"Page.h"
#include<graphics.h>
#include"Tetris.h"
#include<stdio.h>
#include <mmsystem.h>
#include "page.h"
#include <conio.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "music.h"
#pragma comment(lib,"Winmm.lib")
const auto SETTINGS = "settings.txt";
void Page::ranking(player t[])
{
	int num;
	std::ifstream File("playernum.txt");
	File >> num;
	File.close();

	std::vector<player>arr(num);
	std::ifstream File1("rank.txt");
	for (int i = 0; i < num; i++)
	{
		File1 >> arr[i].name >> arr[i].score;
	}
	File1.close();

	std::sort(arr.begin(), arr.end(), [](const player& a, const player& b) {
		return a.score > b.score;
		});
	t[0] = arr[0];
	t[1] = arr[1];
	t[2] = arr[2];
}
/*
0:主菜单
1:进入站斗的两个界面
2:俄罗斯方块正常难度界面
3:帮助
4:设置
5:排行榜
*/
Page::Page(int width, int height) :width(width), height(height), currentIndex(-1)
{
}
int Page::key;


void Page::initlize()
{
	initgraph(width, height);
	loadimage(&background0, "D:\\Code\\Tetris\\Tetris\\res\\bg1.jpg");
	loadimage(&background1, "D:\\Code\\Tetris\\Tetris\\res\\help.png");
	loadimage(&set, "D:\\Code\\Tetris\\Tetris\\res\\set.png");
	loadimage(&rank, "D:\\Code\\Tetris\\Tetris\\res\\rank.png");
	addPage(&background0);//0

	Button* button0_1 = new Button(160, 100, 324, 136, "进行战斗", [&]() {
		setCurrentIndex(1); // 点击按钮1时，切换到页面1
		});
	addButton(0, button0_1); // 将按钮1添加到页面0

	//创建设置按钮
	Button* button0_2 = new Button(160, 270, 324, 136, "设置", [&]() {
		setCurrentIndex(4);
		});
	addButton(0, button0_2);

	//创建帮助按钮
	Button* button0_3 = new Button(160, 440, 324, 136, "帮助", [&]() {
		setCurrentIndex(3);
		});
	addButton(0, button0_3);

	//创建排行榜
	Button* button0_5 = new Button(0, 20, 120, 80, "排行榜", [&]() {
		setCurrentIndex(5);
		});
	addButton(0, button0_5);
	




	addPage(&background0);//1
	addPage(&background0);//2
	addPage(&background1);//3
	addPage(&set);//4
	addPage(&rank);//5
		Button* button1_99 = new Button(0, 12, 100, 50, "返回", [&]() {
		setCurrentIndex(0); // 点击按钮1时，切换回页面0
		});
	addButton(5, button1_99); // 将按钮添加到页面5

	//在1_1背景上创建返回按钮
	Button* button1_1 = new Button(12, 12, 100, 50, "返回", [&]() {
		setCurrentIndex(0); // 点击按钮1时，切换回页面0
		});
	addButton(1, button1_1); // 将按钮添加到页面1

	//创建普通游戏模式按钮
	Button* button1_2 = new Button(120, 200, 400, 138, "正常难度", [&]() {

		//进入游戏界面
		setCurrentIndex(2); // 点击按钮"正常模式"时，切换页面2

		});
	addButton(1, button1_2); // 将按钮添加到页面1

	Button* button1_3 = new Button(120, 400, 400, 138, "地狱难度", [&]() {

		//进入游戏界面
		setCurrentIndex(2); // 点击按钮"地狱模式"时，切换页面2

		});
	addButton(1, button1_3); // 将按钮添加到页面1

	Button* button_jiantou = new Button(350, 45, 300, 150, "上下左右箭头", [&]() {
		key = 0;
		std::ofstream openFile("keycontrol.txt", std::ios::trunc);
		openFile << key;
		openFile.close();
		});
	addButton(4, button_jiantou); // 将按钮添加到页面4
	Button* button_wasd = new Button(15, 45, 300, 150, "wasd", [&]() {
		key = 1;
		std::ofstream openFile("keycontrol.txt", std::ios::trunc);
		openFile << key;
		openFile.close();
		});
	addButton(4, button_wasd); // 将按钮添加到页面1
	Button* button_kai = new Button(15, 210, 300, 140, "打开音乐", [&]() {
		std::ofstream openFile("openmusic.txt", std::ios::trunc);
		openFile << 1;
		openFile.close();
		});
	addButton(4, button_kai); // 将按钮添加到页面1
	Button* button_guan = new Button(350, 210, 300, 140, "关闭音乐", [&]() {
		std::ofstream openFile("openmusic.txt", std::ios::trunc);
		openFile << 0;
		openFile.close();
		});
	addButton(4, button_guan); // 将按钮添加到页面1

	Button* button_pk = new Button(15, 355, 300, 150, "竞技场", [&]() {
		std::ofstream File3("chosemusic.txt", std::ios::trunc);
		File3 << 1;
		File3.close();
		});
	addButton(4, button_pk); // 将按钮添加到页面1

	Button* button_lea = new Button(350, 355, 300, 150, "离别", [&]() {
		std::ofstream File3("chosemusic.txt", std::ios::trunc);
		File3 << 2;
		File3.close();
		});
	addButton(4, button_lea); // 将按钮添加到页面1


	//在设置上创建返回按钮
	Button* button_set = new Button(620, 0, 120, 70, "返回主菜单", [&]() {
		
		setCurrentIndex(0); // 点击按钮1时，切换回页面0

		});
	addButton(4, button_set); // 将按钮添加到页面1

	//在帮助上创建返回按钮
	Button* button_help = new Button(12, 12, 100, 50, "返回", [&]() {

		setCurrentIndex(0); // 点击按钮1时，切换回页面0
		});
	addButton(3, button_help); // 将按钮添加到页面1




	setCurrentIndex(0); // 设置初始显示页面为页面0

}

void Page::run()
{
	ExMessage msg;

	BeginBatchDraw(); // 开始批量绘制

	while (true)
	{
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
		}

		draw(); // 绘制当前页面内容
		FlushBatchDraw(); // 将缓冲区内容显示在屏幕上
		Sleep(10);
	}

	EndBatchDraw(); // 结束批量绘制
}

void Page::addPage(IMAGE* page)
{
	pages.push_back(page);
	buttons.push_back({});
}

void Page::addButton(int index, Button* button)
{
	if (index >= 0 && index < buttons.size())
	{
		buttons[index].push_back(button);
	}

}

void Page::setCurrentIndex(int index)
{
	if (index >= 0 && index < pages.size())
	{
		currentIndex = index;
	}
}

void Page::mouseClick(int mousex, int mousey)
{
	if (currentIndex >= 0 && currentIndex < buttons.size())
	{
		for (Button* button : buttons[currentIndex])
		{
			if (button->checkClick(mousex, mousey))
			{
				break;
			}
		}
	}

}

void Page::mouseMove(int mousex, int mousey)
{
	if (currentIndex >= 0 && currentIndex < buttons.size())
	{
		for (Button* button : buttons[currentIndex])
		{
			button->checkMouseOver(mousex, mousey);
		}
	}

}

void Page::draw()
{
	if (currentIndex >= 0 && currentIndex < pages.size())
	{
		putimage(0, 0, pages[currentIndex]); // 在窗口中绘制当前页面的图片
		if (currentIndex >= 0 && currentIndex < buttons.size())
		{
			for (Button* button : buttons[currentIndex])
			{
				button->draw(); // 绘制当前页面上的所有按钮
			}
		}
	}
	if (currentIndex == 2) {

		////输入名字
		//std::cout << "*****欢迎来玩俄罗斯方块*****" << std::endl;
		//std::cout << "*****请输入账号ID*****" << std::endl;
		//std::string s;
		//std::cin >> s;
		////存
		//std::ofstream File("rank.txt", std::ios::app);
		//File << s << "\t";
		//File.close();
		////玩家数量
		//std::ifstream File1("playernum.txt");
		//int a;
		//File1 >> a;
		//File1.close();
		//std::ofstream File2("playernum.txt", std::ios::trunc);
		//File << (a + 1);
		//File.close();

		//std::cout << "@@@正在加载！！！！！！！！！！！！！！！！！！@@@" << std::endl;
		//Sleep(1000);
		//std::cout << "*****加载完成*****" << std::endl;
		char str[1000] = "";
		InputBox(str, 100, "请输入账号id", "玩家id输入");
		std::string s;
		s = str;
		std::ofstream File("rank.txt", std::ios::app);
		File << s << "\t";
		File.close();
		std::ifstream File1("playernum.txt");
		int a;
		File1 >> a;
		File1.close();
		std::ofstream File2("playernum.txt", std::ios::trunc);
		File << (a + 1);
		File.close();
		Sleep(1000);


		Tetris game(20, 10, 263 * 0.8, 133 * 0.8, 36 * 0.8);
		game.play();

		setCurrentIndex(1); // 设置初始显示页面为页面1
	}
	if (currentIndex == 5)
	{
		player winer[3];
		ranking(winer);
		std::string n1 = winer[0].name;
		int s1 = winer[0].score;
		char scoreText[32];
		setcolor(RGB(205, 190, 112));
		//std::cout << n1;
		LOGFONT f;
		gettextstyle(&f);//获取字体
		f.lfHeight = 90;
		f.lfWidth = 45;
		f.lfQuality = ANTIALIASED_QUALITY;//抗锯齿效果
		strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("Segoe UI Black"));
		settextstyle(&f);

		setbkmode(TRANSPARENT);//字体背景设置透明


		outtextxy(689 * 0.25, 125, n1.c_str());
		sprintf_s(scoreText, sizeof(scoreText), "%d", s1);
		outtextxy(689 * 0.65, 125, scoreText);


		std::string n2 = winer[1].name;
		int s2 = winer[1].score;


		outtextxy(689 * 0.25, 275, n2.c_str());
		sprintf_s(scoreText, sizeof(scoreText), "%d", s2);
		outtextxy(689 * 0.65, 275, scoreText);

		std::string n3 = winer[2].name;
		int s3 = winer[2].score;
		//std::cout << s2;
		outtextxy(689 * 0.25, 425, n3.c_str());
		sprintf_s(scoreText, sizeof(scoreText), "%d", s3);
		outtextxy(689 * 0.65, 425, scoreText);




	}

	//	setCurrentIndex(1); // 返回时到达页面1
	//}
	//if (currentIndex == 4) {



	//}

}
