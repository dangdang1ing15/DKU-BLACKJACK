
#include <stdio.h>
#include <stdlib.h>	//rand(), system()
#include <time.h>	//time()
#include <conio.h>	//getch();
#include <windows.h>

#define WIN 1	//승리
#define LOSE 0 //패배
#define TIE -1	//무승부
#define N_DECK 5	//각 플레이어가 가질 수 있는 최대 카드
#define PLAYER 1	//1은 플레이어를 가리킴
#define DEALER 0	//0은 딜러를 가리킴
#define ACE -1		//A를 11로 변경하기 위한 상수 

//키보드 값
#define UP 10
#define DOWN 11
#define SUBMIT 13

int keycontrol();
void syssett();
void gotoxy(int, int);
void drawbanner();
void selectXY();

int main(){
    init();
    while (1) {
        drawbanner();
        int menuSelect() = selectXY();
        if(menuSelect == 0){
            //게임 시작
        } else if(menuSelect == 1){
            //게임 인포
        } else if(menuSelect == 2){
            //게임 종료
        }
        system("cls");
    }
    return 0;
}

int keycontrol(){
    char temp=getch();
    
    if(temp == 'UP'){
        return UP;
    } else if (temp == 'DOWN'){
        return DOWN;
    } else if (temp == " "){
        return SUBMIT;
    }
}

void syssett(){
    system("mode con cols=48 lines=24 | title Blackjack");
}
void drawbanner(){
    printf("************************************************");
    printf("*  #####    #        ###       ###    #    ##  *");
    printf("*  #    #   #       #   #     #       #   #    *");
    printf("*  #    #   #       #   #     #       #  #     *");
    printf("*  #####    #       #####     #       ###      *");
    printf("*  #    #   #      #     #    #       #  #     *");
    printf("*  #    #   #      #     #    #       #   #    *");
    printf("*  #####    ####   #     #     ###    #    ##  *");
    printf("*                                              *");
    printf("*    ######      ###         ###     #    ##   *");
    printf("*       #       #   #       #        #   #     *");
    printf("*       #       #   #       #        #  #      *");
    printf("*       #       #####       #        ###       *");
    printf("*       #      #     #      #        #  #      *");
    printf("*       #      #     #      #        #   #     *");
    printf("*    ###       #     #       ###     #    ##   *");
    printf("*                                              *");
    printf("************************************************");
}

void gotoxy(int x, int y){
    HANDLE consoleHandle = getStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
}

int selectXY(){
    gotoxy(24-2, 20);
    printf("> 게임 시작");
    gotoxy(24, 21);
    printf("게임 정보");
    gotoxy(24, 22);
    printf("게임 종료");
    while (1) {
        int n = keycontrol();
        switch (n) {
                case UP: {
                        if(y>20){
                            gotoxy(x-2, y);
                            printf(" ");
                            gotoxy(x-2, --y);
                            printf(">");
                        }
                        break;
                }
                case DOWN: {
                        if(y<22){
                            gotoxy(x-2, y);
                            printf(" ");
                            gotoxy(x-2, ++y);
                            printf(">")
                        }
                        break;
                }
                case SUBMIT: {
                    return y-10;
                }
    }
}
