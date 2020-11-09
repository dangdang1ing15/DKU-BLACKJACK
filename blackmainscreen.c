
#include <stdio.h>
#include <windows.h>

//키보드 값
#define UP 0
#define DOWN 1
#define SUBMIT 3

int keycontrol();
void syssett();
void gotoxy(int, int);
void drawbanner();
void selectXY();

int main(){
    syssett();
    drawbanner();
    selectxy();
    int menuSelect()=selecyXY();
    return 0;
}

int keycontrol(){
    char temp=getch():
    
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
        int n = keycontrol():
        switch (n) {
                case UP: {
                        if(y>20){
                            gotoxy(x-2, y);
                            printf(" ");
                            gotoxy(x-2, --y);
                            printf(">")
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
                    return y-20;
                }
    }
}
