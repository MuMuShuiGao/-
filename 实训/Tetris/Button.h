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
    void checkMouseOver(int mousex, int mousey);//�������Ƿ��ڰ�ť�Ϸ�
    bool checkClick(int mousex, int mousey);//����Ƿ�����ִ�а�ť
    int getWidth();


private:
    int x; // ��ť���Ͻ�x����
    int y; // ��ť���Ͻ�y����
    int width; // ��ť���
    int height; // ��ť�߶�
    float scale; // ���ű���������ʵ�������ͣЧ��
    bool isMouseOver; // ��ʾ����Ƿ��ڰ�ť�Ϸ�
    std::string text; // ��ť�ı�
    std::function<void()> onClick; // �����ť�����ĺ���



};

