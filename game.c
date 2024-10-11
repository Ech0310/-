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
            // ȷ����Խ��
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
    // �����λ���ǿ�λ����δ����ʾ
    if (mine[x][y] == '&' && show[x][y] == '*') {
        show[x][y] = '0'; // ����Ϊ��λ��

        int count = gat_mine_count(mine, x, y); // ������Χ�׵�����
        show[x][y] = count + '0'; // ��ʾ��Χ�׵�����

        // �����Χû���ף��ݹ��ʾ��Χλ��
        if (count == 0) {
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int newX = x + i;
                    int newY = y + j;
                    // ȷ����Խ�粢�����ظ�λ��
                    if ((i != 0 || j != 0) && newX >= 1 && newX <= 9 && newY >= 1 && newY <= 9) {
                        is_mine(mine, show, newX, newY); // �ݹ��ʾ��Χλ��
                    }
                }
            }
        }
    }
}



// ����� is_win ����
int is_win(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col) {
    int remaining = 0;
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            // ͳ��δ�����ķ��׸�������
            if (show[i][j] == '*' && mine[i][j] != '#') {
                remaining++;
            }
        }
    }
    return remaining;  // ����δ�����ķ��׸�����
}


// �����Ǻ�ȡ����ǵĺ���
void flagmine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int x, int y) {
    if (show[x][y] == '*') {
        show[x][y] = '^'; // ���Ϊ��
    }
    else if (show[x][y] == '^') {
        show[x][y] = '*'; // ȡ�����
    }
    DisPlayBoard(show, ROW, COL); // ������ʾ����
}


// ������뻺�����ĺ���
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // ���ѵ��������е������ַ���ֱ���������з��� EOF
    }
}

// ������ģʽ�ĺ���
void handleFlagMode(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col) {
    int flagx = 0, flagy = 0;
    while (1) {
        printf("���ģʽ����ѡ��Ҫ��ǻ�ȡ����ǵ����� x y (����999 999�˳����ģʽ): ");

        // ��� scanf �ķ���ֵ��ȷ������ĸ�ʽ��ȷ
        if (scanf("%d %d", &flagx, &flagy) != 2) {
            printf("������Ч���������������ꡣ\n");
            clear_input_buffer();  // ������뻺������������ѭ��
            continue;  // ������ʾ�û�����
        }

        // ����Ƿ��˳����ģʽ
        if (flagx == 999 && flagy == 999) {
            printf("�˳����ģʽ...\n");
            break;  // �˳����ģʽ
        }

        // ȷ���������Ϸ�
        if (flagx > 0 && flagx <= row && flagy > 0 && flagy <= col) {
            flagmine(mine, show, row, col, flagx, flagy);  // ���ñ�ǻ�ȡ����Ǻ���
        }
        else {
            printf("������겻�Ϸ��������ԡ�\n");
        }
    }
}


// ����Ϸ�߼�
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col) {
    int x = 0, y = 0;
    int remaining_non_mine = 0;  // δ�����ķ��׸�������

    while (1) {
        // ��ʾ�û�ѡ��ģʽ
        printf("ѡ��ģʽ���������Ų������(1-%d)��������99 99��������ģʽ:>", row);
        scanf("%d %d", &x, &y);

        // ����׵����������handleFlagMode�����ǲ���
        if (x == 99 && y == 99) {
            handleFlagMode(mine, show, row, col);  // ������ģʽ
            continue;  // ������ѭ��������ִ���Ų��߼�
        }

        // ȷ��������Ų�����Ϸ�
        if (x > 0 && x <= row && y > 0 && y <= col) {
            // �������
            if (mine[x][y] == '#') {
                printf("Game Over��\n");
                DisPlayBoard(mine, ROW, COL);  // ��ʾ����������
                printf("��Ϊ#\n\n");
                break;
            }
            // ����ǿ�λ����δ����ʾ
            else if (mine[x][y] == '&' && show[x][y] == '*') {
                is_mine(mine, show, x, y);  // ������Χ����
                DisPlayBoard(show, ROW, COL);
            }
            // ������������Ѿ�����ʾ
            else {
                int count = gat_mine_count(mine, x, y);  // ������Χ������
                show[x][y] = count + '0'; // ת�������ַ���ʾ
                DisPlayBoard(show, ROW, COL);
            }
        }
        else {
            printf("����ӦΪ1-%d֮�䣬�����ԡ�\n", row);  // ��̬��ʾ����
            continue;  // ����ѭ����ʼ������ִ�к�������
        }

        // ����δ�������׸��ӵ�����
        remaining_non_mine = is_win(mine, show, row, col);
        if (remaining_non_mine == 0) {  // ���з��׵ĸ��Ӷ�����������ʤ
            printf("WIN!!\n");
            DisPlayBoard(mine, ROW, COL);  // ��ʾ�����ĵ�����
            printf("��Ϊ#\n\n");
            break;
        }
    }
}