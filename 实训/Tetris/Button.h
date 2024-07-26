#pragma once

#include <graphics.h>
#include <functional>
#include <string>
#include <vector>
#include <iostream>

class Button
{
public:
    Button(int x, int y, int width, int height, const std::string& text, const std::function<void()>& onClick);

    void draw();
    void checkMouseOver(int mousex, int mousey);//检查鼠标是否在按钮上方
    bool checkClick(int mousex, int mousey);//检查是否点击并执行按钮
    int getWidth();


private:
    int x; // 按钮左上角x坐标
    int y; // 按钮左上角y坐标
    int width; // 按钮宽度
    int height; // 按钮高度
    float scale; // 缩放比例，用于实现鼠标悬停效果
    bool isMouseOver; // 表示鼠标是否在按钮上方
    std::string text; // 按钮文本
    std::function<void()> onClick; // 点击按钮触发的函数



};

