#include "Button.h"
#include "page.h"
#include "Tetris.h"
int main()
{
    //int width = 750;  // ���ڿ��
    //int height = 716;  // ���ڸ߶�
    //initgraph(width, height);  // ��ʼ��ͼ�δ���
    // �����ַ������������������û�����

    Page widget(720, 670);
    widget.initlize();
    widget.run();
    
   /* Tetris game(20, 10, 263 * 0.8, 133 * 0.8, 36 * 0.8);
    std::cout << 1;*/
     // Tetris game(20, 10, 210, 106, 28);
      // game.play();
    return 0;
}