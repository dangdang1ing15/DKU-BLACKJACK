#include <stdio.h>

#include <Windows.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

#define song "C:\\test\\song.wav" /*파일 위치로 지정*/
void main()
{
	PlaySound(TEXT(song), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);  /*Playsound(주소, NULL, 옵션|옵션|옵션....)*/
	                                                                   /*SND_ASYNC : 재생하면서 다음 코드 실행, SND_LOOP : 반복재생*/
	while (1)
	{
		int a;
		printf("종료?");
		scanf_s("%d", &a);
		if (a = 0)
		{
			PlaySound(NULL, 0, 0);
			Sleep(1000);
			printf("노래를 종료했습니다. 함수도 종료합니다.");
			return;
		}
	}
}