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

	printf("����:1, ����:2, ��:3, �������:4, �ʱ�ȭ:5 ����:6\n");

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
			printf("�̱� Ƚ�� : %d��, �� Ƚ�� : %d��, ��� Ƚ�� : %d�� \n", wincount, losecount, samecount);
			printf("total = %d, win percent:%.1lf\n", total, winpercent);
		}

		if (user == 5)
		{
			wincount = 0, losecount = 0, samecount = 0, total = 0;
			printf("�ʱ�ȭ �Ϸ�\n");
		}

		if (user == 6)
		{
			printf("���α׷��� �����մϴ�.\n");
			break;
		}
		
		srand(time(NULL));
		computer = rand() % 3 + 1;

		if (computer == 1)
		{
			if (user == 1)
			{
				printf("[�����ϴ�]\n");
				samecount++;
				total++;
			}
			else if (user == 2)
			{
				printf("[�̰���ϴ�]\n");
				wincount++;
				total++;
			}
			else if (user == 3)
			{
				printf("[�����ϴ�]\n");
				losecount++;
				total++;
			}
		}

		if (computer == 2)
		{
			if (user == 1)
			{
				printf("[�����ϴ�]\n");
				losecount++;
				total++;
			}
			else if (user == 2)
			{
				printf("[�����ϴ�]\n");
				samecount++;
				total++;
			}
			else if (user == 3)
			{
				printf("[�̰���ϴ�]\n");
				wincount++;
				total++;
			}
		}

		if (computer == 3)
		{
			if (user == 1)
			{
				printf("[�̰���ϴ�]\n");
				wincount++;
				total++;
			}
			else if (user == 2)
			{
				printf("[�����ϴ�]\n");
				losecount++;
				total++;
			}
			else if (user == 3)
			{
				printf("[�����ϴ�]\n");
				samecount++;
				total++;
			}
		}

	}

	return 0;
}