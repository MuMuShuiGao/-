#pragma once
#include <graphics.h>
#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include"Button.h"
struct player
{
	std::string name;
	int score;
};
class Page
{
private:
	int width; // ���
	int height; // �߶�
	int currentIndex; // ��ǰҳ������
	char settings[4]{ 'w','s','a','d' };
	IMAGE background0;
	IMAGE background1;
	IMAGE set;
	IMAGE rank;
	void ranking(player t[]);

	std::vector<IMAGE*> pages; // �洢����ҳ���ͼƬָ��
	std::vector<std::vector<Button*>> buttons; // �洢ÿ��ҳ���ϵİ�ť
	int a = buttons.size();
public:
	static int key;

public:
	Page(int width, int height);

	void initlize();
	void run();
	void addPage(IMAGE* page);
	void addButton(int index, Button* button);
	void setCurrentIndex(int index);//����ҳ������
	void mouseClick(int mousex, int mousey);//����������¼�
	void mouseMove(int mousex, int mousey);//��������ƶ�
	void draw();//����ҳ������


};

