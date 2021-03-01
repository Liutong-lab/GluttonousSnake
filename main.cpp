#include <cstdio>
#include <cstdlib>
#include <Windows.h>
#include <ctime>
#include <iostream>
#include <conio.h> //键盘输入获取
//游戏结束
bool gameOver;
//暂停
bool stop = false;
//记录是否无操作
bool hit = false;
//游戏的边框大小
const int width = 50;
const int height = 24;
//蛇头的坐标，食物的坐标还有分数
int x,y,fruitX,fruitY,score;
//蛇每个点的坐标
int tailX[200],tailY[200];
//蛇的默认长度
int nTail=3;
//休眠时间（速度）
int sleepTime = 70;
//退出游戏
int isExit = 0;
typedef enum
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
}Direction;

Direction Dir;
/*开始菜单*/
void menu()
{
    int a;
    printf("------------------------------------------------------------------\n");
    printf("|                             Gluttonous Snake                   |\n");
    printf("|                                                                |\n");
    printf("|                               1) new game                      |\n");
    printf("|                               2) exit                          |\n");
    printf("------------------------------------------------------------------\n");
    printf("---->Type your choice: ");
    std::cin >> a;
    if (a == 1){
        system("cls");/*清除屏幕*/
        printf("------------------------------------------------------------------\n");
        printf("|                           Choose Game Speed                    |\n");
        printf("------------------------------------------------------------------\n");
        printf("---->Type a speed(lager then 1): ");
        std::cin >> sleepTime;
    }
    if (a == 2){
        isExit = 1;
    }
}

/*初始化状态*/
void setup(){
    hit = 0;
    nTail=3;
    gameOver = false;
    /*根据当前时间设置“随机数种子”*/
    srand(time(nullptr));
    Dir = STOP;

    /*贪吃蛇的位置,固定在中间*/
    x= width / 2;
    y= height / 2;
    /*食物的位置，位置是随机的*/
    fruitX = rand() % width - 1;
    if (!fruitX){
        fruitX = 1;
    }
    fruitY = rand() % height - 1;
    if (!fruitY){
        fruitY = 1;
    }
    score = 0;
}
/*绘制界面*/
void draw(){
    if(stop){
        return;
    }
    system("cls");/*清除屏幕*/
    printf("Score: %d\n",score);
    std::cout << "  (Type 'x' or ESC to exit, type SPACE to pause)\n";
    for(int i = 0; i < width+1; i++){/*上边框*/
        printf("-");
    }
    printf("\n");

    for(int h = 0; h < height; h++){/*高度*/
        for(int w = 0; w < width; w++){/*宽度*/
            /*左右边框*/
            if(w == 0 || w == width-1){
                printf("|");
            }

            if(h == fruitY && w == fruitX){/*食物的随机坐标*/
                printf("O");
            }
            else{
                bool print = false;
                /*贪吃蛇的长度 默认长度是 3*/
                for(int k = 0; k < nTail; k++){
                    if(tailX[k] == w && tailY[k] == h){
                        printf("*");
                        print = true;
                    }
                }
                /*如果这个位置打印了 * 就不要打印空格了*/
                if(!print){
                    printf(" ");
                }
            }
        }
        printf("\n");
    }

    for(int j= 0 ;j<width+1;j++){/*最后一行*/
        printf("-");
    }
}
/*按键输入控制*/
void input(){
    if(_kbhit()){
        /*获取键盘的输入字符*/
        switch(_getch()){
            case 75:/*左键*/
                if (Dir != RIGHT) {
                    Dir = LEFT;
                    hit = true;
                }
                break;
            case 72:/*上键*/
                if (Dir != DOWN) {
                    Dir = UP;
                    hit = true;
                }
                break;
            case 77:/*右键*/
                if (Dir != LEFT) {
                    Dir = RIGHT;
                    hit = true;
                }
                break;
            case 80:/*向下键盘键 */
                if (Dir != UP) {
                    Dir = DOWN;
                    hit = true;
                }
                break;
            case 'x':
            case 27:/*ESE*/
                gameOver = true;
                break;
            case 32:/*空格 暂停键*/
                stop = !stop;
                break;
        }
    }
    else if(!hit && !stop){/*如果没有改变方向*/
        x++;
    }
}
/*判断贪吃蛇的长度*/
void logic()
{
    if(stop){
        return;
    }

    /*把上一个位置记下*/
    int X = tailX[0];
    int Y = tailY[0];
    int XX, YY;

    /*遍历整条蛇的长度 把 0 的位置空出来，其余蛇的位置往后面的空间移动*/
    for(int i = 1; i < nTail; i++)
    {
        XX = tailX[i];
        YY = tailY[i];
        tailX[i] = X;
        tailY[i]= Y;
        X = XX;
        Y = YY;
    }
    /*根据方向来改变x y 的值*/
    switch(Dir)
    {
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case STOP:
            break;
    }
/*重新获取当前的位置*/
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++){
        if (hit && x == tailX[i] && y == tailY[i]){
            gameOver = true;
            /*清除屏幕*/
            system("cls");
            printf("------------------------------------------------------------------\n");
            printf("|                                                                |\n");
            printf("|                            GAME OVER                           |\n");
            printf("|                                                                |\n");
            printf("|                    input anything to continue                  |\n");
            printf("|                                                                |\n");
            printf("------------------------------------------------------------------\n");
            std::string v;
            std::cin >> v;
            return;
        }
    }
    if(x < 0 || width < x || y < 0 || height < y){
        gameOver = true;
        /*清除屏幕*/
        system("cls");
        printf("------------------------------------------------------------------\n");
        printf("|                                                                |\n");
        printf("|                            GAME OVER                           |\n");
        printf("|                                                                |\n");
        printf("|                    input anything to continue                  |\n");
        printf("|                                                                |\n");
        printf("------------------------------------------------------------------\n");
        std::string v;
        std::cin >> v;
        return;
    }

    if(x == fruitX && y == fruitY){
        /*吃了一个食物，蛇的长度增加1*/
        nTail++;
        score += 10;
        /*更新下一个食物的位置*/
        fruitX = rand() % width - 1;
        if (!fruitX){
            fruitX = 1;
        }
        fruitY = rand() % height - 1;
        if (!fruitY){
            fruitY = 1;
        }
    }
}

int main(){
    menu();
    setup();
    draw();
    /*循环画贪吃蛇的界面*/
    while (!isExit) {
        while (!gameOver) {
            draw();
            input();
            logic();
            Sleep(sleepTime);
        }
        if (isExit){
            break;
        }
        if (gameOver){
            menu();
            setup();
            draw();
        }
    }
    return 0;
}