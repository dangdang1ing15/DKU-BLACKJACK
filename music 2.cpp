#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

#define song "C:\\song.wav"

void main()
{
	PlaySound(TEXT(song), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	while (1)
	{
		int a;
		printf("종료하려면 1을 입력하시오");
		scanf_s("%d", &a);
		if (a = 1)
		{
			PlaySound(NULL, 0, 0);
			Sleep(1000);
			printf("노래를 종료했습니다. 함수도 종료합니다.");
			return;
		}
	}
}