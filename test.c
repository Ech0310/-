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
    char mine[ROWS][COLS] = { 0 }; //�����׵���Ϣ
    char show[ROWS][COLS] = { 0 };//��֪�׵���Ϣ
    //��ʼ����Ϊָ��������
    //�趨mine�����ʼΪ��&��
    InitBoard(mine, ROWS, COLS, '&');
    //�趨show�����ʼΪ��*��
    InitBoard(show, ROWS, COLS, '*');
    //������
    SetMine(mine, ROW, COL);
    //DisPlayBoard(mine, ROW, COL);
    DisPlayBoard(show, ROW, COL);
    //�Ų���
    FindMine(mine, show, ROW, COL);
    //DisPlayBoard(show, ROW, COL);

}

int main() {

    srand((unsigned int)time(NULL));
    int inpute = 0;
    int result = 0;

    do {
        menu();
        printf("���������ѡ��: ");
        result = scanf("%d", &inpute);

        // ��������Ƿ�Ϊ����
        if (result != 1) {
            // ������뻺����
            while (getchar() != '\n');
            printf("������Ч��������һ��������\n");
            continue;
        }

        switch (inpute) {
        case 1:
            printf("��Ϸ��ɨ��\n");
            printf("������ΪY��������ΪX\n");
            game();
            break;
        case 0:
            printf("�˳���Ϸ\n");
            break;
        default:
            printf("ѡ�����ѡ��ӦΪ1����0\n");
            break;
        }
    } while (inpute );

    return 0;
}