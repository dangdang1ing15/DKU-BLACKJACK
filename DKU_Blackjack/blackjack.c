#include <stdio.h>
#include <stdlib.h>	//rand(), system()
#include <time.h>	//time()
#include <conio.h>	//getch();

#define WIN 1	//�¸�
#define LOSE 0 //�й�
#define TIE -1	//���º�
#define N_DECK 5	//�� �÷��̾ ���� �� �ִ� �ִ� ī��
#define PLAYER 1	//1�� �÷��̾ ����Ŵ
#define DEALER 0	//0�� ������ ����Ŵ
#define ACE -1		//A�� 11�� �����ϱ� ���� ��� 

/* �⺻ �Լ� */

//ī�带 ������ִ� �Լ�
void printCard(int cardInDeck, int index);

//ī�带 �̴� �Լ�
void drawCard(int deck[], int* save);

/* ���� �κ� */

//���� �޴� UI�� �����ϴ� �Լ�
void startMenu(void);

//���� �ݾ��� ��ȯ�ϴ� �Լ�
int betting(int money, int rate);

/* �÷��� �� */

//�ʱ� ī�� �й� �Լ�
void devideCard(int p[], int d[], int compare[][N_DECK]);

//ī���� ���� ���ϴ� �Լ�
int sumOfCard(int deck[]);

/* ������ */

//�º� ���� �Լ�
int end(int p[], int d[], int compare[][N_DECK]);

int card[52] = {	//ī�� �� ������ �����ϴ� �迭
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13
};

int main(void)
{
	/*���� ����*/
	int bet;	//���� �ݾ�
	int sumOfPlayer = 0, sumOfDealer = 0;	//�÷��̾�, ������ ī�� �� ����
	int player[N_DECK] = { 0 };	//�÷��̾��� ī�� ����
	int dealer[N_DECK] = { 0 };	//������ ī�� ����
	int save[2][N_DECK] = { 0 };	//�ε����� ���� ��¿� Ȱ��. 0���� ����, 1���� �÷��̾�
	int c;	//ī�带 �� ������ ����
	int rate;	// end�� ������ �� ������ betting�� Ȱ��
	

	/*���� �÷���*/
	startMenu();	//���۸޴�
	/*����*/
	printf("�󸶸� �����Ͻðڽ��ϱ�?(��): ");
	scanf_s("%d", &bet);

	system("cls");	//ȭ�� �ʱ�ȭ

	/*1�� ī�� �й�*/
	devideCard(player, dealer, save);
	printf("������ ī�� �� �� ��: ");
	printCard(dealer[0], save[DEALER][0]);
	printf("\n");
	printf("�÷��̾��� ī��: ");
	printCard(player[0], save[PLAYER][0]);

	printCard(player[1], save[PLAYER][1]);
	printf("\n");

	/*�÷��̾��� ī�� �߰�*/
	for (int i = 2; i < N_DECK; i++) {
		printf("�÷��̾ ���� ī���� ��: %d\n", sumOfCard(player));
		if (sumOfCard(player) > 21) break;	//bust�� ��� ���� ����
		printf("ī�带 �� �����ðڽ��ϱ�?('y' or 'n') ");
		getchar();	//���� ����
		c = getchar();
		if (c == 'y') {	//y�� �Է��ϸ� ī�带 �� �̰� ���� ī�带 ������
			drawCard(player, &save[PLAYER][i], PLAYER);
			printCard(player[i], save[PLAYER][i]);
			printf("\n");
		}
		else break;
	}

	/*������ ī�� �߰�*/
	for (int i = 2; i < N_DECK; i++) {
		if (sumOfCard(dealer) > 21) break;	//bust�� ��� ���� ����
		if (sumOfCard(dealer) < 17) drawCard(dealer, &save[DEALER][i], DEALER);
	}

	rate = end(player, dealer, save);
	bet = betting(bet, rate);
	printf("�ݾ�: %d", bet);

	return 0;
}

void printCard(int cardInDeck, int index) {
	/*�ε����� ���� ���� ���*/
	if (index < 13) printf("�����̵� ");
	else if (index < 26) printf("���̾Ƹ�� ");
	else if (index < 39) printf("Ŭ�ι� ");
	else printf("��Ʈ ");
	/*ī�尪 ���*/
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
	srand((unsigned)time(NULL)); //���� �õ�
	static int compare[10];		//�ߺ� ��
	static int cnt = 0;			//�ε����� �����ϱ� ���� ����
	int index = rand() % 52;
	/*�ߺ� �����ϸ� ���� ����*/
	for (int i = 0; i < cnt; i++) {
		index = rand() % 52;
		compare[cnt] = index;	//�ε����� ����
		for (int j = 0; j < i; j++) {
			if (compare[i] == compare[j]) {	//�ߺ��� ������
				cnt--;						//�ε��� �ٽ� ����
				break;
			}
		}
	}
	*save = index;
	for (int i = 0; i < N_DECK; i++) {
		if (deck[i] == 0) {
			deck[i] = card[index];	//���̸��� ���� ī�� �߰�
			/*A�� 1�� 11�� ����, 11�� �����ϸ� ACE(-1)�� �����Ͽ� �հ迡 ���*/
			if (deck[i] == 1) {
				printf("A�� 1�� 11�� ������ �� �ֽ��ϴ�.\n");
				printf("1�� �Է��ϸ� 1��, 2�� �Է��ϸ� 11�� �����մϴ�.");
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
	printf("���� �����Դϴ�. �÷����Ϸ��� �ƹ�Ű�� ��������.\n");
	_getch();	//�ƹ� Ű �Է¹ޱ�
	system("cls");	//ȭ�� �ʱ�ȭ
}
int betting(int money, int rate) {
	if (rate == WIN) return money * 2;	//�̱�� 2��
	else if (rate == LOSE) return 0; 	//���� ��� �Ҵ´�
	return money;	//���ºθ� �״��
}

void devideCard(int p[], int d[], int save[][N_DECK]) {
	/*�� ���� ī�� �̱�*/
	drawCard(p, &save[PLAYER][0], PLAYER);
	drawCard(p, &save[PLAYER][1], PLAYER);
	drawCard(d, &save[DEALER][0], DEALER);
	drawCard(d, &save[DEALER][1], DEALER);
}

int sumOfCard(int deck[]) {
	int sum = 0;
	for (int i = 0; deck[i] != 0; i++) {	//����� ���ڸ� ���ϱ�
		if (deck[i] == ACE) sum += 11;
		else if (deck[i] > 10) sum += 10;
		else sum += deck[i];
	}
	return sum;
}

int end(int p[], int d[], int save[][N_DECK]) {
	system("cls");

	/*���� �� ���*/
	printf("�÷��̾ ���� ī��: ");
	for (int i = 0; p[i] != 0; i++)
		printCard(p[i], save[PLAYER][i]);
	printf(" ��: %d\n", sumOfCard(p));
	printf("������ ���� ī��: ");
	for (int i = 0; d[i] != 0; i++)
		printCard(d[i], save[DEALER][i]);
	printf("  ��: %d\n", sumOfCard(d));

	/*���� 21�� �Ѵ� ���� Bust*/
	if (sumOfCard(p) > 21 && sumOfCard(d) > 21) {
		printf("��� Bust! ���º��Դϴ�.\n");
		return TIE;
	}
	if (sumOfCard(p) > 21 && sumOfCard(d) <= 21) {
		printf("�÷��̾��� Bust! �й��ϼ̽��ϴ�.\n");
		return LOSE;
	}
	else if (sumOfCard(d) > 21) {
		printf("��ǻ���� Bust! �¸��ϼ̽��ϴ�.\n");
		return WIN;
	}
	else if (sumOfCard(p) > sumOfCard(d)) {
		printf("�¸��ϼ̽��ϴ�.\n");
		return WIN;
	}
	else if (sumOfCard(p) < sumOfCard(d)) {
		printf("�й��ϼ̽��ϴ�.\n");
		return LOSE;
	}
	else if (sumOfCard(p) == sumOfCard(d))
		printf("���º�!\n");
	return TIE;
}