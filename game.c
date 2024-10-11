#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            board[i][j] = set;
        }
    }
}

void DisPlayBoard(char board[ROWS][COLS], int row, int col) {
    printf("--------------------\n");
    for (int i = 0; i <=col; i++)
    {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 1; i <= col; i++) 
    {
        printf("%d ", i);
        for (int j = 1; j <= row; j++) 
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("--------------------\n");
    printf("\n");

}

void SetMine(char board[ROWS][COLS], int row, int col) {
    int count = EASY_COUNT;
    while (count) {
        int x = rand() % row + 1;
        int y = rand() % col + 1;
        if (board[x][y] == '&') {
            board[x][y] = '#';
            count--;
        }
    }
}



int gat_mine_count(char board[ROWS][COLS], int x, int y) {
    int sum = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newX = x + i;
            int newY = y + j;
            // 确保不越界
            if ((i != 0 || j != 0) && newX >= 1 && newX <= 9 && newY >= 1 && newY <= 9) {
                if (board[newX][newY] == '#') {
                    sum++;
                }
            }
        }
    }
    return sum;
}

void is_mine(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y) {
    // 如果该位置是空位置且未被揭示
    if (mine[x][y] == '&' && show[x][y] == '*') {
        show[x][y] = '0'; // 更新为空位置

        int count = gat_mine_count(mine, x, y); // 计算周围雷的数量
        show[x][y] = count + '0'; // 显示周围雷的数量

        // 如果周围没有雷，递归揭示周围位置
        if (count == 0) {
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int newX = x + i;
                    int newY = y + j;
                    // 确保不越界并避免重复位置
                    if ((i != 0 || j != 0) && newX >= 1 && newX <= 9 && newY >= 1 && newY <= 9) {
                        is_mine(mine, show, newX, newY); // 递归揭示周围位置
                    }
                }
            }
        }
    }
}



// 定义的 is_win 函数
int is_win(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col) {
    int remaining = 0;
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            // 统计未翻开的非雷格子数量
            if (show[i][j] == '*' && mine[i][j] != '#') {
                remaining++;
            }
        }
    }
    return remaining;  // 返回未翻开的非雷格子数
}


// 处理标记和取消标记的函数
void flagmine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int x, int y) {
    if (show[x][y] == '*') {
        show[x][y] = '^'; // 标记为雷
    }
    else if (show[x][y] == '^') {
        show[x][y] = '*'; // 取消标记
    }
    DisPlayBoard(show, ROW, COL); // 更新显示棋盘
}


// 清空输入缓冲区的函数
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // 消费掉缓冲区中的所有字符，直到遇到换行符或 EOF
    }
}

// 处理标记模式的函数
void handleFlagMode(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col) {
    int flagx = 0, flagy = 0;
    while (1) {
        printf("标记模式：请选择要标记或取消标记的坐标 x y (输入999 999退出标记模式): ");

        // 检查 scanf 的返回值，确保输入的格式正确
        if (scanf("%d %d", &flagx, &flagy) != 2) {
            printf("输入无效，请输入整数坐标。\n");
            clear_input_buffer();  // 清空输入缓冲区，避免死循环
            continue;  // 重新提示用户输入
        }

        // 检查是否退出标记模式
        if (flagx == 999 && flagy == 999) {
            printf("退出标记模式...\n");
            break;  // 退出标记模式
        }

        // 确保标记坐标合法
        if (flagx > 0 && flagx <= row && flagy > 0 && flagy <= col) {
            flagmine(mine, show, row, col, flagx, flagy);  // 调用标记或取消标记函数
        }
        else {
            printf("标记坐标不合法，请重试。\n");
        }
    }
}


// 主游戏逻辑
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col) {
    int x = 0, y = 0;
    int remaining_non_mine = 0;  // 未翻开的非雷格子数量

    while (1) {
        // 提示用户选择模式
        printf("选择模式：请输入排查的坐标(1-%d)，或输入99 99进入标记雷模式:>", row);
        scanf("%d %d", &x, &y);

        // 标记雷的情况，调用handleFlagMode处理标记操作
        if (x == 99 && y == 99) {
            handleFlagMode(mine, show, row, col);  // 进入标记模式
            continue;  // 返回主循环，避免执行排查逻辑
        }

        // 确保输入的排查坐标合法
        if (x > 0 && x <= row && y > 0 && y <= col) {
            // 如果是雷
            if (mine[x][y] == '#') {
                printf("Game Over！\n");
                DisPlayBoard(mine, ROW, COL);  // 显示完整地雷盘
                printf("雷为#\n\n");
                break;
            }
            // 如果是空位置且未被揭示
            else if (mine[x][y] == '&' && show[x][y] == '*') {
                is_mine(mine, show, x, y);  // 翻开周围格子
                DisPlayBoard(show, ROW, COL);
            }
            // 如果不是雷且已经被揭示
            else {
                int count = gat_mine_count(mine, x, y);  // 计算周围地雷数
                show[x][y] = count + '0'; // 转成数字字符显示
                DisPlayBoard(show, ROW, COL);
            }
        }
        else {
            printf("坐标应为1-%d之间，请重试。\n", row);  // 动态提示行数
            continue;  // 返回循环开始，避免执行后续代码
        }

        // 计算未翻开非雷格子的数量
        remaining_non_mine = is_win(mine, show, row, col);
        if (remaining_non_mine == 0) {  // 所有非雷的格子都被翻开，获胜
            printf("WIN!!\n");
            DisPlayBoard(mine, ROW, COL);  // 显示完整的地雷盘
            printf("雷为#\n\n");
            break;
        }
    }
}