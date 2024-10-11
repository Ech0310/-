// test.c
#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

void menu() {
    printf("*****************************\n");
    printf("*********** 1 Play **********\n");
    printf("*********** 0 Exit **********\n");
    printf("*****************************\n");
}

void game() {
    char mine[ROWS][COLS] = { 0 }; //布置雷的信息
    char show[ROWS][COLS] = { 0 };//已知雷的信息
    //初始数组为指定的内容
    //设定mine数组初始为“&”
    InitBoard(mine, ROWS, COLS, '&');
    //设定show数组初始为“*”
    InitBoard(show, ROWS, COLS, '*');
    //设置雷
    SetMine(mine, ROW, COL);
    //DisPlayBoard(mine, ROW, COL);
    DisPlayBoard(show, ROW, COL);
    //排查雷
    FindMine(mine, show, ROW, COL);
    //DisPlayBoard(show, ROW, COL);

}

int main() {

    srand((unsigned int)time(NULL));
    int inpute = 0;
    int result = 0;

    do {
        menu();
        printf("请输入你的选择: ");
        result = scanf("%d", &inpute);

        // 检查输入是否为整数
        if (result != 1) {
            // 清除输入缓冲区
            while (getchar() != '\n');
            printf("输入无效，请输入一个整数。\n");
            continue;
        }

        switch (inpute) {
        case 1:
            printf("游戏：扫雷\n");
            printf("纵坐标为Y，横坐标为X\n");
            game();
            break;
        case 0:
            printf("退出游戏\n");
            break;
        default:
            printf("选择错误，选择应为1或者0\n");
            break;
        }
    } while (inpute );

    return 0;
}