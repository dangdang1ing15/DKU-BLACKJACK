#include <stdio.h>
#include <stdlib.h>	//rand(), system()
#include <time.h>	//time()
#include <conio.h>	//getch();
#include <windows.h>	//키보드 입력

#define WIN 1	//승리
#define LOSE 0 //패배
#define TIE -1	//무승부
#define N_DECK 5	//각 플레이어가 가질 수 있는 최대 카드
#define PLAYER 1	//1은 플레이어를 가리킴
#define DEALER 0	//0은 딜러를 가리킴
#define ACE -1		//A를 11로 변경하기 위한 상수 

/*키보드 값*/
#define UP 10
#define DOWN 11
#define SUBMIT 12

/* 기본 함수 */
//카드를 출력해주는 함수
void printCard(int cardInDeck, int index);
//카드를 뽑는 함수
void drawCard(int deck[], int* save, int playerOrDealer);

/* 시작 부분 */
//시작 메뉴 UI를 구성하는 함수
void startMenu(void);
//베팅 금액을 반환하는 함수
int betting(int money, int rate);

/* 플레이 중 */
//초기 카드 분배 함수
void devideCard(int p[], int d[], int compare[][N_DECK]);
//카드의 합을 구하는 함수
int sumOfCard(int deck[]);

/* 마무리 */
//승부 결정 함수
int end(int p[], int d[], int save[][N_DECK]);

/*메인메뉴 구성을 위한 함수*/
//키보드에서 값을 입력받아 메뉴 이동, 선택
int keycontrol();
// 초기 화면 크기 조정
void syssett();
//지정한 좌표로 이동
void gotoxy(int, int);
//blackjack 메인 이미지 그리기
void drawbanner();
//메뉴 출력 및 이동
int selectXY();
//제작정보
void gameInfo();

int card[52] = {	//카드 당 점수를 저장하는 배열
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13
};


int main(void)
{
	syssett();		//화면 크기 조정
	system("chcp 65001");	//인코딩 문제로 콘솔의 한글이 깨질 수도 있어서 추가. 필요에 따라 삭제
	system("cls");	//화면 초기화

	while (1) {
		drawbanner();
		int menuSelect = selectXY();	//메뉴 선택
		system("cls");
		if (menuSelect == 0) {	//'게임 시작' 선택하면 실행
			system("mode con cols=100 lines=30");	//크기 재조정
			COORD bufferSize = { 100, 9001 }; // 출력버퍼 조절 - 화면 잘림 방지
			SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
			/*변수 선언*/
			int bet;	//베팅 금액
			int sumOfPlayer = 0, sumOfDealer = 0;	//플레이어, 딜러의 카드 합 저장
			int player[N_DECK] = { 0 };	//플레이어의 카드 저장
			int dealer[N_DECK] = { 0 };	//딜러의 카드 저장
			int save[2][N_DECK];	//인덱스를 문양 출력에 활용. 0행은 딜러, 1행은 플레이어
			int c;	//카드를 더 뽑을지 결정
			int rate;	// end가 리턴한 값 저장해 betting에 활용

			for (int i = 0; i < 2; i++)
				for (int j = 0; j < N_DECK; j++)
					save[i][j] = -1;	//save의 기본값은 음수로 지정함.

			/*게임 플레이*/
			startMenu();	//시작메뉴
			/*베팅*/
			printf("얼마를 베팅하시겠습니까?(원): ");
			scanf_s("%d", &bet);

			system("cls");	//화면 초기화

			/*1차 카드 분배*/
			devideCard(player, dealer, save);
			printf("딜러의 카드 중 한 장: ");
			printCard(dealer[0], save[DEALER][0]);
			printf("\n");
			printf("플레이어의 카드: ");
			printCard(player[0], save[PLAYER][0]);

			printCard(player[1], save[PLAYER][1]);
			printf("\n");

			/*플레이어의 카드 추가*/
			for (int i = 2; i < N_DECK; i++) {
				printf("플레이어가 가진 카드의 합: %d\n", sumOfCard(player));
				if (sumOfCard(player) > 21) break;	//bust면 즉시 게임 종료
				printf("카드를 더 뽑으시겠습니까?('y' or 'n') ");
				getchar();	//버퍼 비우기
				c = getchar();
				if (c == 'y') {	//y를 입력하면 카드를 더 뽑고 뽑은 카드를 보여줌
					drawCard(player, &save[PLAYER][i], PLAYER);
					printCard(player[i], save[PLAYER][i]);
					printf("\n");
				}
				else break;
			}

			/*딜러의 카드 추가*/
			for (int i = 2; i < N_DECK; i++) {
				if (sumOfCard(dealer) > 21) break;	//bust면 즉시 게임 종료
				if (sumOfCard(dealer) < 17) drawCard(dealer, &save[DEALER][i], DEALER);
			}

			rate = end(player, dealer, save);
			bet = betting(bet, rate);
			printf("=======================\n");
			printf("금액: %d", bet);

			return 0;
		}
		else if (menuSelect == 1) {		//'게임정보' 선택하면 실행
			//게임 인포
			gameInfo();
		}
		else if (menuSelect == 2) {		//'게임종료' 선택하면 실행
			//게임 종료
			printf("게임을 종료합니다.\n");
			return 0;
		}
		system("cls");
	}
	return 0;
}

void printCard(int cardInDeck, int index) {
	/*카드를 출력해주는 함수
	cardInDeck: 카드 번호를 출력에 이용, player, dealer 변수의 값을 받는다
	index: 문양 출력에 이용, save 변수의 값을 받는다*/

	char pattern[4] = "";
	/*인덱스에 따라 문양 출력*/
	if (index < 0) printf("");	//비어있으면 아무것도 출력하지 않음
	else if (index < 13) strcpy_s(pattern, 4, "♠");
	else if (index < 26) strcpy_s(pattern, 4, "◆");
	else if (index < 39) strcpy_s(pattern, 4, "♣");
	else strcpy_s(pattern, 4, "♥");

	/*카드값 출력*/
	switch (cardInDeck) {
	case -1:
	case 1: {
		printf("\n");
		printf("┌──────────┐\n");
		printf("│%s        │\n", pattern);
		printf("│ %c        │\n", 'A');
		printf("│          │\n");
		printf("│          │\n");
		printf("│          │\n");
		printf("│         %c│\n", 'A');
		printf("│        %s│\n", pattern);
		printf("└──────────┘\n");
		break;
	}
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9: {
		printf("\n");
		printf("┌──────────┐\n");
		printf("│%s        │\n", pattern);
		printf("│ %d        │\n", cardInDeck);
		printf("│          │\n");
		printf("│          │\n");
		printf("│          │\n");
		printf("│         %d│\n", cardInDeck);
		printf("│        %s│\n", pattern);
		printf("└──────────┘\n");
		break;
	}
	case 10: {
		printf("\n");
		printf("┌──────────┐\n");
		printf("│%s        │\n", pattern);
		printf("│%d        │\n", cardInDeck);
		printf("│          │\n");
		printf("│          │\n");
		printf("│          │\n");
		printf("│        %d│\n", cardInDeck);
		printf("│        %s│\n", pattern);
		printf("└──────────┘\n");
		break;
	}
	case 11: {
		printf("\n");
		printf("┌──────────┐\n");
		printf("│%s        │\n", pattern);
		printf("│ %c        │\n", 'J');
		printf("│          │\n");
		printf("│          │\n");
		printf("│          │\n");
		printf("│         %c│\n", 'J');
		printf("│        %s│\n", pattern);
		printf("└──────────┘\n");
		break;
	}
	case 12: {
		printf("\n");
		printf("┌──────────┐\n");
		printf("│%s        │\n", pattern);
		printf("│ %c        │\n", 'Q');
		printf("│          │\n");
		printf("│          │\n");
		printf("│          │\n");
		printf("│         %c│\n", 'Q');
		printf("│        %s│\n", pattern);
		printf("└──────────┘\n");
		break;
	}
	case 13: {
		printf("\n");
		printf("┌──────────┐\n");
		printf("│%s        │\n", pattern);
		printf("│ %c        │\n", 'K');
		printf("│          │\n");
		printf("│          │\n");
		printf("│          │\n");
		printf("│         %c│\n", 'K');
		printf("│        %s│\n", pattern);
		printf("└──────────┘\n");
		break;
	}
	}
}

void drawCard(int deck[], int* save, int playerOrDealer) {
	/*카드를 뽑는 함수
deck: player 또는 dealer의 덱, player, dealer 변수의 값을 받는다
*save: 뽑은 카드의 위치 저장(문양 출력에 이용), save의 값을 받는다
playerOrDealer: 플레이어인지 딜러인지 확인하고 A 선택권 부여*/

	srand((unsigned)time(NULL)); //랜덤 시드
	static int compare[10];		//지금까지 뽑은 카드를 저장하는 곳
	static int cnt = 0;			//지금까지 뽑은 카드의 개수
	int index = rand() % 52;	//카드를 뽑을 때 사용하는 변수
	/*중복 제거하며 난수 생성*/
	for (int i = 0; i < cnt; i++) {
		index = rand() % 52;
		compare[cnt] = index;	//인덱스를 저장
		for (int j = 0; j < i; j++) {
			if (compare[cnt] == compare[j]) {	//중복이 있으면
				i--;						//인덱스 다시 생성
				break;
			}
		}
	}
	*save = index;
	for (int i = 0; i < N_DECK; i++) {
		if (deck[i] == 0) {
			deck[i] = card[index];	//게이머의 덱에 카드 추가
			/*A는 1과 11중 선택, 11을 선택하면 ACE(-1)로 저장하여 합계에 사용*/
			if (deck[i] == 1) {
				if (playerOrDealer == PLAYER) {	//플레이어는 A를 1과 11중 선택
					printf("A는 1과 11중 선택할 수 있습니다.\n");
					printf("1을 입력하면 1로, 2를 입력하면 11로 선택합니다.");
					int n;
					scanf_s("%d", &n);
					if (n == 1) deck[i] = card[index];
					else deck[i] = ACE;
				}
			}
			break;
		}
	}
	cnt++;
}

void startMenu(void) {
	printf("블랙잭 게임입니다. 플레이하려면 아무키나 누르세요.\n");
	_getch();	//아무 키 입력받기
	system("cls");	//화면 초기화
}
int betting(int money, int rate) {
	/*베팅 금액을 반환하는 함수
money: 베팅한 금액, bet 변수를 받는다
rate: 승패 확인, rate 변수를 받는다*/

	if (rate == WIN) return money * 2;	//이기면 2배
	else if (rate == LOSE) return 0; 	//지면 모두 잃는다
	return money;	//무승부면 그대로
}

void devideCard(int p[], int d[], int save[][N_DECK]) {
	/*두 번씩 카드 뽑기*/
	drawCard(p, &save[PLAYER][0], PLAYER);
	drawCard(p, &save[PLAYER][1], PLAYER);
	drawCard(d, &save[DEALER][0], DEALER);
	drawCard(d, &save[DEALER][1], DEALER);
}

int sumOfCard(int deck[]) {
	int sum = 0;
	for (int i = 0; i < N_DECK; i++) {	//합 구하기
		if (deck[i] == ACE) sum += 11;
		else if (deck[i] > 10) sum += 10;
		else sum += deck[i];
	}
	return sum;
}

int end(int p[], int d[], int save[][N_DECK]) {
	/*승부 결정 함수
p는 player 변수를 받는다
d는 dealer 변수를 받는다
save는 save 변수를 받는다*/

	system("cls");

	/*최종 덱 출력*/
	printf("플레이어가 가진 카드:\n");
	for (int i = 0; i < N_DECK; i++)
		printCard(p[i], save[PLAYER][i]);
	printf(" 합: %d\n", sumOfCard(p));
	printf("=======================\n");
	printf("딜러가 가진 카드:\n");
	for (int i = 0; i < N_DECK; i++)
		printCard(d[i], save[DEALER][i]);
	printf("  합: %d\n", sumOfCard(d));
	printf("=======================\n");

	/*합이 21이 넘는 경우는 Bust*/
	if (sumOfCard(p) > 21 && sumOfCard(d) > 21) {
		printf("모두 Bust! 무승부입니다.\n");
		return TIE;
	}
	if (sumOfCard(p) > 21 && sumOfCard(d) <= 21) {
		printf("플레이어의 Bust! 패배하셨습니다.\n");
		return LOSE;
	}
	else if (sumOfCard(d) > 21) {
		printf("컴퓨터의 Bust! 승리하셨습니다.\n");
		return WIN;
	}
	else if (sumOfCard(p) > sumOfCard(d)) {
		printf("승리하셨습니다.\n");
		return WIN;
	}
	else if (sumOfCard(p) < sumOfCard(d)) {
		printf("패배하셨습니다.\n");
		return LOSE;
	}
	else if (sumOfCard(p) == sumOfCard(d))
		printf("무승부!\n");
	return TIE;
}

int keycontrol() {
	char temp = _getch();

	if (temp == 'w') {	//w를 입력하면 UP 반환(위로 이동)
		return UP;
	}
	else if (temp == 's') {	//s를 입력하면 DOWN 반환(아래로 이동)
		return DOWN;
	}
	else if (temp == ' ') {	//space(공백을 입력하면 SUBMIT 반환(선택)
		return SUBMIT;
	}
}

void syssett() {
	system("mode con cols=48 lines=24 | title Blackjack");	//배너가 잘 출력될 수 있게 화면 크기 조정
}
void drawbanner() {
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

void gotoxy(int x, int y) {		//원하는 좌표로 이동하기 위한 함수
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

int selectXY() {
	int x = 24, y = 20;
	/*메뉴 출력*/
	gotoxy(x - 6, y - 2);
	printf("(w, s로 이동, space로 선택)");
	gotoxy(x - 2, y);
	printf("> 게임 시작");	//>는 현재 선택한 메뉴를 보여줌
	gotoxy(x, y + 1);
	printf("게임 정보");
	gotoxy(x, y + 2);
	printf("게임 종료");

	while (1) {
		int n = keycontrol();	//키보드에서 값을 입력받기
		switch (n) {
		case UP: {		//w를 입력하면
			if (y > 20) {
				gotoxy(x - 2, y);	//원래 '>'가 있던 자리에
				printf(" ");		//공백을 덮어써서 지우고
				gotoxy(x - 2, --y);	//위 메뉴로 올라가
				printf(">");		//'>'를 출력.
			}
			break;
		}
		case DOWN: {
			if (y < 22) {	//s를 입력하면
				gotoxy(x - 2, y);	//원래 '>'가 있던 자리에
				printf(" ");		//공백을 덮어써서 지우고
				gotoxy(x - 2, ++y);	//아래 메뉴로 내려가
				printf(">");		//'>'를 출력.
			}
			break;
		}
		case SUBMIT: {
			return y - 20;	//y는 20, 21, 22 내에서 움직이므로 
							//y - 20을 반환하면 main()의 menuSelect에 원하는 값 전달 가능
		}
		}
	}
}

void gameInfo() {
	system("cls");
	printf("\n\n");
	printf("               [DKU BLACKJAK]\n\n");
	printf("룰 설명\n");
	printf("1. 먼저 베팅을 진행합니다.\n");
	printf("2. 카드 두 장을 나누어주고, 딜러는 한 장만 공개합니다.\n");
	printf("3. 카드 합이 21에 가까운 사람이 승리합니다.\n");
	printf("4. 21을 넘으면 버스트(Bust), 패배입니다.\n");
	printf("5. 딜러는 카드 합이 16 이하면 한 장을 더 받습니다.\n");
	printf("6.A는 1 또는 11으로, 10, J, Q, K는 모두 10으로 취급합니다.\n");
	printf("\n제작자: 김성현, 김민성, 전종휘, 홍준서, 방지석\n");
	printf("\n스페이스바를 누르면 메인화면으로 돌아갑니다.");

	while (13) {
		if (keycontrol() == SUBMIT) {
			break;
		}
	}
}