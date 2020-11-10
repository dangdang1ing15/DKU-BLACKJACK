#include <stdio.h>
#include <stdlib.h>	//rand(), system()
#include <time.h>	//time()
#include <conio.h>	//getch();

#define WIN 1	//승리
#define LOSE 0 //패배
#define TIE -1	//무승부
#define N_DECK 5	//각 플레이어가 가질 수 있는 최대 카드
#define PLAYER 1	//1은 플레이어를 가리킴
#define DEALER 0	//0은 딜러를 가리킴
#define ACE -1		//A를 11로 변경하기 위한 상수 

/* 기본 함수 */

//카드를 출력해주는 함수
void printCard(int cardInDeck, int index);

//카드를 뽑는 함수
void drawCard(int deck[], int* save);

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
int end(int p[], int d[], int compare[][N_DECK]);

int card[52] = {	//카드 당 점수를 저장하는 배열
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13
};

int main(void)
{
	/*변수 선언*/
	int bet;	//베팅 금액
	int sumOfPlayer = 0, sumOfDealer = 0;	//플레이어, 딜러의 카드 합 저장
	int player[N_DECK] = { 0 };	//플레이어의 카드 저장
	int dealer[N_DECK] = { 0 };	//딜러의 카드 저장
	int save[2][N_DECK] = { 0 };	//인덱스를 문양 출력에 활용. 0행은 딜러, 1행은 플레이어
	int c;	//카드를 더 뽑을지 결정
	int rate;	// end가 리턴한 값 저장해 betting에 활용
	

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
	printf("금액: %d", bet);

	return 0;
}

void printCard(int cardInDeck, int index) {
	/*인덱스에 따라 문양 출력*/
	if (index < 13) printf("스페이드 ");
	else if (index < 26) printf("다이아몬드 ");
	else if (index < 39) printf("클로버 ");
	else printf("하트 ");
	/*카드값 출력*/
	switch (cardInDeck) {
	case -1:
	case 1: {
		printf("A ");
		break;
	}
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10: {
		printf("%d ", cardInDeck);
		break;
	}
	case 11: {
		printf("J ");
		break;
	}
	case 12: {
		printf("Q ");
		break;
	}
	case 13: {
		printf("K ");
		break;
	}
	}
}

void drawCard(int deck[], int *save) {
	srand((unsigned)time(NULL)); //랜덤 시드
	static int compare[10];		//중복 비교
	static int cnt = 0;			//인덱스를 저장하기 위한 변수
	int index = rand() % 52;
	/*중복 제거하며 난수 생성*/
	for (int i = 0; i < cnt; i++) {
		index = rand() % 52;
		compare[cnt] = index;	//인덱스를 저장
		for (int j = 0; j < i; j++) {
			if (compare[i] == compare[j]) {	//중복이 있으면
				cnt--;						//인덱스 다시 생성
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
				printf("A는 1과 11중 선택할 수 있습니다.\n");
				printf("1을 입력하면 1로, 2를 입력하면 11로 선택합니다.");
				int n;
				scanf_s("%d", &n);
				if (n == 1) deck[i] = card[index];
				else deck[i] = ACE;
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
	for (int i = 0; deck[i] != 0; i++) {	//저장된 숫자만 더하기
		if (deck[i] == ACE) sum += 11;
		else if (deck[i] > 10) sum += 10;
		else sum += deck[i];
	}
	return sum;
}

int end(int p[], int d[], int save[][N_DECK]) {
	system("cls");

	/*최종 덱 출력*/
	printf("플레이어가 가진 카드: ");
	for (int i = 0; p[i] != 0; i++)
		printCard(p[i], save[PLAYER][i]);
	printf(" 합: %d\n", sumOfCard(p));
	printf("딜러가 가진 카드: ");
	for (int i = 0; d[i] != 0; i++)
		printCard(d[i], save[DEALER][i]);
	printf("  합: %d\n", sumOfCard(d));

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