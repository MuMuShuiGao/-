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
	int width; // 宽度
	int height; // 高度
	int currentIndex; // 当前页面索引
	char settings[4]{ 'w','s','a','d' };
	IMAGE background0;
	IMAGE background1;
	IMAGE set;
	IMAGE rank;
	void ranking(player t[]);

	std::vector<IMAGE*> pages; // 存储所有页面的图片指针
	std::vector<std::vector<Button*>> buttons; // 存储每个页面上的按钮
	int a = buttons.size();
public:
	static int key;

public:
	Page(int width, int height);

	void initlize();
	void run();
	void addPage(IMAGE* page);
	void addButton(int index, Button* button);
	void setCurrentIndex(int index);//设置页面索引
	void mouseClick(int mousex, int mousey);//处理鼠标点击事件
	void mouseMove(int mousex, int mousey);//处理鼠标移动
	void draw();//绘制页面内容


};

