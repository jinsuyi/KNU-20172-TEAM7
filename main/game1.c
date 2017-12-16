#define _CRT_SECURE_NO_WARNINGS

void game1()
{
	int computer;
	int user;
	int wincount = 0 ;
	int losecount = 0;
	int samecount = 0;
	int total = 0;
	double winpercent = 0;
    printf(" < Rock Paper Scissor game >\n");
    printf(" Select your menu : \n");
	printf(" Scissor:1, Rock:2, Paper:3, Statistics:4, Reset:5 Quit:6\n");

	while (1)
	{
		printf("\n");
		printf("user = ");
		if(scanf("%d", &user) != 1){
			printf("\n\n>> Wrong input\n");
			sleep(2);
			break;
		}
		
		if (user>6 || user<1)
			printf("input error\n");
	
		winpercent = ((double)wincount / total) * 100;

		if (user == 4)
		{
			printf("Win Count : %dtimes, Lose Count : %dtimes, Draw count : %dtimes \n", wincount, losecount, samecount);
			printf("Total games = %d, Win Ratio:%.1lf\n", total, winpercent);
		}

		if (user == 5)
		{
			wincount = 0, losecount = 0, samecount = 0, total = 0;
			printf("Reset Done\n");
		}

		if (user == 6)
		{
			printf("Exiting Program.\n");
			break;
		}
		
		srand(time(NULL));
		computer = rand() % 3 + 1;

		if (computer == 1)
		{
			if (user == 1)
			{
				printf("[You Draw]\n");
				samecount++;
				total++;
			}
			else if (user == 2)
			{
				printf("[You Won]\n");
				wincount++;
				total++;
			}
			else if (user == 3)
			{
				printf("[You Lost]\n");
				losecount++;
				total++;
			}
		}

		if (computer == 2)
		{
			if (user == 1)
			{
				printf("[You Lost]\n");
				losecount++;
				total++;
			}
			else if (user == 2)
			{
				printf("[You Draw]\n");
				samecount++;
				total++;
			}
			else if (user == 3)
			{
				printf("[You Won]\n");
				wincount++;
				total++;
			}
		}

		if (computer == 3)
		{
			if (user == 1)
			{
				printf("[You Won]\n");
				wincount++;
				total++;
			}
			else if (user == 2)
			{
				printf("[You Lost]\n");
				losecount++;
				total++;
			}
			else if (user == 3)
			{
				printf("[You Draw]\n");
				samecount++;
				total++;
			}
		}

	}

	return;
}
