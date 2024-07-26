#include "Button.h"
#include "page.h"
#include "Tetris.h"
int main()
{
    //int width = 750;  // 窗口宽度
    //int height = 716;  // 窗口高度
    //initgraph(width, height);  // 初始化图形窗口
    // 定义字符串缓冲区，并接收用户输入

    Page widget(720, 670);
    widget.initlize();
    widget.run();
    
   /* Tetris game(20, 10, 263 * 0.8, 133 * 0.8, 36 * 0.8);
    std::cout << 1;*/
     // Tetris game(20, 10, 210, 106, 28);
      // game.play();
    return 0;
}