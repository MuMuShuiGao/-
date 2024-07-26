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
    int scaledWidth = width * scale*0.8; // ���ź�İ�ť���
    int scaledHeight = height * scale*0.8; // ���ź�İ�ť�߶�
    int scaledX = x + (width - scaledWidth) / 2; // ���ź�İ�ťx����
    int scaledY = y + (height - scaledHeight) / 2; // ���ź�İ�ťy����

    if (isMouseOver)
    {
        setlinecolor(RGB(0, 120, 215)); // �����ͣʱ��ť�߿���ɫ
        setfillcolor(RGB(229, 241, 251)); // �����ͣʱ��ť�����ɫ

    }
    else
    {
        setlinecolor(RGB(173, 173, 173)); // ��ť�߿���ɫ
        setfillcolor(RGB(225, 225, 225)); // ��ť�����ɫ
      
    }

    fillrectangle(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight); // ���ư�ť
    settextcolor(BLACK); // �����ı���ɫΪ��ɫ
    setbkmode(TRANSPARENT); // �����ı�����͸��
    settextstyle(20 * scale, 0, _T("΢���ź�")); // �����ı���С������
    //������ʾ��ť�ı�
    int textX = scaledX + (scaledWidth - textwidth(text.c_str())) / 2; // �����ı��ڰ�ť�����x����
    int textY = scaledY + (scaledHeight - textheight(_T("Segoe UI Black"))) / 2; // �����ı��ڰ�ť�����y����
    outtextxy(textX, textY, text.c_str()); // �ڰ�ť�ϻ����ı�
}

void Button::checkMouseOver(int mousex, int mousey)
{
    isMouseOver = (mousex >= x && mousex <= x + width && mousey >= y && mousey <= y + height);

    if (isMouseOver) {
        scale = 0.9f; // �����ͣʱ���Ű�ť
    }
    else {
        scale = 1.0f; // �ָ���ťԭʼ��С
    }

}

bool Button::checkClick(int mousex, int mousey)
{
    if (mousex >= x && mousex <= x + width && mousey >= y && mousey <= y + height)
    {
        onClick(); // ִ�а�ť���ʱ�ĺ���
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

