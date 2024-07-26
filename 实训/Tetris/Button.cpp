#include "Button.h"
#include<graphics.h>
#include<conio.h>

Button::Button(int x, int y, int width, int height, const std::string& text, const std::function<void()>& onClick)
    : x(x), y(y), width(width), height(height), text(text), onClick(onClick), scale(1.0f), isMouseOver(false)
{
    this->width = width;
}

void Button::draw()
{
    int scaledWidth = width * scale*0.8; // 缩放后的按钮宽度
    int scaledHeight = height * scale*0.8; // 缩放后的按钮高度
    int scaledX = x + (width - scaledWidth) / 2; // 缩放后的按钮x坐标
    int scaledY = y + (height - scaledHeight) / 2; // 缩放后的按钮y坐标

    if (isMouseOver)
    {
        setlinecolor(RGB(0, 120, 215)); // 鼠标悬停时按钮边框颜色
        setfillcolor(RGB(229, 241, 251)); // 鼠标悬停时按钮填充颜色

    }
    else
    {
        setlinecolor(RGB(173, 173, 173)); // 按钮边框颜色
        setfillcolor(RGB(225, 225, 225)); // 按钮填充颜色
      
    }

    fillrectangle(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight); // 绘制按钮
    settextcolor(BLACK); // 设置文本颜色为黑色
    setbkmode(TRANSPARENT); // 设置文本背景透明
    settextstyle(20 * scale, 0, _T("微软雅黑")); // 设置文本大小和字体
    //居中显示按钮文本
    int textX = scaledX + (scaledWidth - textwidth(text.c_str())) / 2; // 计算文本在按钮中央的x坐标
    int textY = scaledY + (scaledHeight - textheight(_T("Segoe UI Black"))) / 2; // 计算文本在按钮中央的y坐标
    outtextxy(textX, textY, text.c_str()); // 在按钮上绘制文本
}

void Button::checkMouseOver(int mousex, int mousey)
{
    isMouseOver = (mousex >= x && mousex <= x + width && mousey >= y && mousey <= y + height);

    if (isMouseOver) {
        scale = 0.9f; // 鼠标悬停时缩放按钮
    }
    else {
        scale = 1.0f; // 恢复按钮原始大小
    }

}

bool Button::checkClick(int mousex, int mousey)
{
    if (mousex >= x && mousex <= x + width && mousey >= y && mousey <= y + height)
    {
        onClick(); // 执行按钮点击时的函数
        isMouseOver = false;
        scale = 1.0f;
        return true;
    }
    return false;

}

int Button::getWidth()
{
    return width;
}

