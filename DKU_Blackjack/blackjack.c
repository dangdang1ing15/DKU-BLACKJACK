#include <stdio.h>
#include <stdlib.h>	//rand(), system()
#include <time.h>	//time()
#include <conio.h>	//getch();

#define WIN 1	//�¸�
#define LOSE 0 //�й�
#define TIE -1	//���º�
#define N_DECK 5	//�� �÷��̾ ���� �� �ִ� �ִ� ī�� ��

/* �⺻ �Լ� */

//ī�带 ������ִ� �Լ�
void printCard(int cardInDeck);

//ī�带 �̴� �Լ�
void drawCard(int deck[]);

/* ���� �κ� */

//���� �޴� UI�� �����ϴ� �Լ�
void startMenu(void);

//���� �ݾ��� ��ȯ�ϴ� �Լ�
int betting(int money, int rate);

/* �÷��� �� */

//�ʱ� ī�� �й� �Լ�
void devideCard(int p[], int d[]);

//ī���� ���� ���ϴ� �Լ�
int sumOfCard(int deck[]);

//���� ī�带 �����ִ� �Լ�
void showCard(int deck[]);

//ī�带 �߰��ϴ� �Լ�
void addCard(void);	

/* ������ */

//�º� ���� �Լ�
int end(int p[], int d[]);

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
	int c;	//ī�带 �� ������ ����
	int rate;	// end ������ �� ������ betting�� Ȱ��

	/*���� �÷���*/
	startMenu();	//���۸޴�
	/*����*/
	printf("�󸶸� �����Ͻðڽ��ϱ�?(��): ");
	scanf_s("%d", &bet);

	system("cls");	//ȭ�� �ʱ�ȭ

	/*1�� ī�� �й�*/
	devideCard(player, dealer);
	printf("������ ī�� �� �� ��: ");
	printCard(dealer[0]);
	printf("\n");
	printf("�÷��̾��� ī��: ");
	printCard(player[0]);
	printCard(player[1]);
	printf("\n");

	for (int i = 2; i < N_DECK; i++) {
		printf("�÷��̾ ���� ī���� ��: %d\n", sumOfCard(player));
		if (sumOfCard(player) > 21) break;
		printf("ī�带 �� �����ðڽ��ϱ�?('y' or 'n') ");
		getchar();	//���� ����
		c = getchar();
		if (c == 'y') drawCard(player);
		else break;
	}

	for (int i = 2; i < N_DECK; i++) {
		if (sumOfCard(dealer) > 21) break;
		if (sumOfCard(dealer) < 17) drawCard(dealer);
		else break;
	}

	rate = end(player, dealer);
	bet = betting(bet, rate);
	printf("�ݾ�: %d", bet);

	return 0;
}

void printCard(int cardInDeck) {
	switch (cardInDeck) {
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

void drawCard(int deck[]) {
	srand((unsigned)time(NULL)); //���� �õ�
	static int compare[10];		//�ߺ��� ���� �迭
	static int cnt = 0;			//�Լ� ���� Ƚ��
	int index = rand() % 52;
	/*�ߺ� �����ϸ� ���� ����*/
	for (int i = 0; i < cnt; i++) {
		index = rand() % 52;
		compare[i] = index;	//�ε����� ����
		for (int j = 0; j < i; j++) {
			if (compare[i] == compare[j]) {	//�ߺ��� ������
				i--;						//�ε��� �ٽ� ����
				break;
			}
		}
	}
	for (int i = 0; i < N_DECK; i++) {
		if (deck[i] == 0) {
			deck[i] = card[index];	//���̸��� ���� ī�� �߰�
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

void devideCard(int p[], int d[]) {
	drawCard(p);	//�� ���� ī�� �̱�
	drawCard(p);
	drawCard(d);
	drawCard(d);
}

int sumOfCard(int deck[]) {
	int sum = 0;
	for (int i = 0; deck[i] != 0; i++) {	//����� ���ڸ� ���ϱ�
		if (deck[i] > 10) sum += 10;
		else sum += deck[i];
	}
	return sum;
}
void showCard(int cardInDeck) {

}
int end(int p[], int d[]) {
	system("cls");
	printf("�÷��̾ ���� ī��: ");
	for (int i = 0; p[i] != 0; i++)
		printCard(p[i]);
	printf(" ��: %d\n", sumOfCard(p));
	printf("������ ���� ī��: ");
	for (int i = 0; d[i] != 0; i++)
		printCard(d[i]);
	printf("  ��: %d\n", sumOfCard(d));

	//���� 21�� �Ѵ� ���� Bust(�й�ó��)
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