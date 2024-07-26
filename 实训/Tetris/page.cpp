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
0:���˵�
1:����վ������������
2:����˹���������ѶȽ���
3:����
4:����
5:���а�
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

	Button* button0_1 = new Button(160, 100, 324, 136, "����ս��", [&]() {
		setCurrentIndex(1); // �����ť1ʱ���л���ҳ��1
		});
	addButton(0, button0_1); // ����ť1��ӵ�ҳ��0

	//�������ð�ť
	Button* button0_2 = new Button(160, 270, 324, 136, "����", [&]() {
		setCurrentIndex(4);
		});
	addButton(0, button0_2);

	//����������ť
	Button* button0_3 = new Button(160, 440, 324, 136, "����", [&]() {
		setCurrentIndex(3);
		});
	addButton(0, button0_3);

	//�������а�
	Button* button0_5 = new Button(0, 20, 120, 80, "���а�", [&]() {
		setCurrentIndex(5);
		});
	addButton(0, button0_5);
	




	addPage(&background0);//1
	addPage(&background0);//2
	addPage(&background1);//3
	addPage(&set);//4
	addPage(&rank);//5
		Button* button1_99 = new Button(0, 12, 100, 50, "����", [&]() {
		setCurrentIndex(0); // �����ť1ʱ���л���ҳ��0
		});
	addButton(5, button1_99); // ����ť��ӵ�ҳ��5

	//��1_1�����ϴ������ذ�ť
	Button* button1_1 = new Button(12, 12, 100, 50, "����", [&]() {
		setCurrentIndex(0); // �����ť1ʱ���л���ҳ��0
		});
	addButton(1, button1_1); // ����ť��ӵ�ҳ��1

	//������ͨ��Ϸģʽ��ť
	Button* button1_2 = new Button(120, 200, 400, 138, "�����Ѷ�", [&]() {

		//������Ϸ����
		setCurrentIndex(2); // �����ť"����ģʽ"ʱ���л�ҳ��2

		});
	addButton(1, button1_2); // ����ť��ӵ�ҳ��1

	Button* button1_3 = new Button(120, 400, 400, 138, "�����Ѷ�", [&]() {

		//������Ϸ����
		setCurrentIndex(2); // �����ť"����ģʽ"ʱ���л�ҳ��2

		});
	addButton(1, button1_3); // ����ť��ӵ�ҳ��1

	Button* button_jiantou = new Button(350, 45, 300, 150, "�������Ҽ�ͷ", [&]() {
		key = 0;
		std::ofstream openFile("keycontrol.txt", std::ios::trunc);
		openFile << key;
		openFile.close();
		});
	addButton(4, button_jiantou); // ����ť��ӵ�ҳ��4
	Button* button_wasd = new Button(15, 45, 300, 150, "wasd", [&]() {
		key = 1;
		std::ofstream openFile("keycontrol.txt", std::ios::trunc);
		openFile << key;
		openFile.close();
		});
	addButton(4, button_wasd); // ����ť��ӵ�ҳ��1
	Button* button_kai = new Button(15, 210, 300, 140, "������", [&]() {
		std::ofstream openFile("openmusic.txt", std::ios::trunc);
		openFile << 1;
		openFile.close();
		});
	addButton(4, button_kai); // ����ť��ӵ�ҳ��1
	Button* button_guan = new Button(350, 210, 300, 140, "�ر�����", [&]() {
		std::ofstream openFile("openmusic.txt", std::ios::trunc);
		openFile << 0;
		openFile.close();
		});
	addButton(4, button_guan); // ����ť��ӵ�ҳ��1

	Button* button_pk = new Button(15, 355, 300, 150, "������", [&]() {
		std::ofstream File3("chosemusic.txt", std::ios::trunc);
		File3 << 1;
		File3.close();
		});
	addButton(4, button_pk); // ����ť��ӵ�ҳ��1

	Button* button_lea = new Button(350, 355, 300, 150, "���", [&]() {
		std::ofstream File3("chosemusic.txt", std::ios::trunc);
		File3 << 2;
		File3.close();
		});
	addButton(4, button_lea); // ����ť��ӵ�ҳ��1


	//�������ϴ������ذ�ť
	Button* button_set = new Button(620, 0, 120, 70, "�������˵�", [&]() {
		
		setCurrentIndex(0); // �����ť1ʱ���л���ҳ��0

		});
	addButton(4, button_set); // ����ť��ӵ�ҳ��1

	//�ڰ����ϴ������ذ�ť
	Button* button_help = new Button(12, 12, 100, 50, "����", [&]() {

		setCurrentIndex(0); // �����ť1ʱ���л���ҳ��0
		});
	addButton(3, button_help); // ����ť��ӵ�ҳ��1




	setCurrentIndex(0); // ���ó�ʼ��ʾҳ��Ϊҳ��0

}

void Page::run()
{
	ExMessage msg;

	BeginBatchDraw(); // ��ʼ��������

	while (true)
	{
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
		}

		draw(); // ���Ƶ�ǰҳ������
		FlushBatchDraw(); // ��������������ʾ����Ļ��
		Sleep(10);
	}

	EndBatchDraw(); // ������������
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
		putimage(0, 0, pages[currentIndex]); // �ڴ����л��Ƶ�ǰҳ���ͼƬ
		if (currentIndex >= 0 && currentIndex < buttons.size())
		{
			for (Button* button : buttons[currentIndex])
			{
				button->draw(); // ���Ƶ�ǰҳ���ϵ����а�ť
			}
		}
	}
	if (currentIndex == 2) {

		////��������
		//std::cout << "*****��ӭ�������˹����*****" << std::endl;
		//std::cout << "*****�������˺�ID*****" << std::endl;
		//std::string s;
		//std::cin >> s;
		////��
		//std::ofstream File("rank.txt", std::ios::app);
		//File << s << "\t";
		//File.close();
		////�������
		//std::ifstream File1("playernum.txt");
		//int a;
		//File1 >> a;
		//File1.close();
		//std::ofstream File2("playernum.txt", std::ios::trunc);
		//File << (a + 1);
		//File.close();

		//std::cout << "@@@���ڼ��أ�����������������������������������@@@" << std::endl;
		//Sleep(1000);
		//std::cout << "*****�������*****" << std::endl;
		char str[1000] = "";
		InputBox(str, 100, "�������˺�id", "���id����");
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

		setCurrentIndex(1); // ���ó�ʼ��ʾҳ��Ϊҳ��1
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
		gettextstyle(&f);//��ȡ����
		f.lfHeight = 90;
		f.lfWidth = 45;
		f.lfQuality = ANTIALIASED_QUALITY;//�����Ч��
		strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("Segoe UI Black"));
		settextstyle(&f);

		setbkmode(TRANSPARENT);//���屳������͸��


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

	//	setCurrentIndex(1); // ����ʱ����ҳ��1
	//}
	//if (currentIndex == 4) {



	//}

}
