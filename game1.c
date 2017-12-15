#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int computer;
	int user;
	int wincount = 0 ;
	int losecount = 0;
	int samecount = 0;
	int total = 0;
	double winpercent = 0;

	printf("가위:1, 바위:2, 보:3, 총합통계:4, 초기화:5 종료:6\n");

	while (1)
	{
		printf("\n");
		printf("user = ");
		scanf("%d", &user);
		
		if (user>6 || user<1)
			printf("input error\n");
	
		winpercent = ((double)wincount / total) * 100;

		if (user == 4)
		{
			printf("이긴 횟수 : %d번, 진 횟수 : %d번, 비긴 횟수 : %d번 \n", wincount, losecount, samecount);
			printf("total = %d, win percent:%.1lf\n", total, winpercent);
		}

		if (user == 5)
		{
			wincount = 0, losecount = 0, samecount = 0, total = 0;
			printf("초기화 완료\n");
		}

		if (user == 6)
		{
			printf("프로그램을 종료합니다.\n");
			break;
		}
		
		srand(time(NULL));
		computer = rand() % 3 + 1;

		if (computer == 1)
		{
			if (user == 1)
			{
				printf("[비겼습니다]\n");
				samecount++;
				total++;
			}
			else if (user == 2)
			{
				printf("[이겼습니다]\n");
				wincount++;
				total++;
			}
			else if (user == 3)
			{
				printf("[졌습니다]\n");
				losecount++;
				total++;
			}
		}

		if (computer == 2)
		{
			if (user == 1)
			{
				printf("[졌습니다]\n");
				losecount++;
				total++;
			}
			else if (user == 2)
			{
				printf("[비겼습니다]\n");
				samecount++;
				total++;
			}
			else if (user == 3)
			{
				printf("[이겼습니다]\n");
				wincount++;
				total++;
			}
		}

		if (computer == 3)
		{
			if (user == 1)
			{
				printf("[이겼습니다]\n");
				wincount++;
				total++;
			}
			else if (user == 2)
			{
				printf("[졌습니다]\n");
				losecount++;
				total++;
			}
			else if (user == 3)
			{
				printf("[비겼습니다]\n");
				samecount++;
				total++;
			}
		}

	}

	return 0;
}