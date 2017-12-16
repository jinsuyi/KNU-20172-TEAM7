#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utmp.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>

#define BUFF_SIZE 1024


void set_cr_noecho_mode(void);
void tty_mode(int);
int alarms = 0;//while문 빠져나가기
int readtxt(int);
void quits(int);

int exec_time1()
{
	int fd;
	char buf[BUFSIZ];

	//utmp
	struct utmp current;
	int utmpfd;
	int reclen = sizeof(current);
	
	int find = 0;
	char dev[100]="/dev/";

	int input;//

    char av[100];
    printf("please enter ttyname (ex> /dev/pts/0)\n");
    scanf("%s", av);
	/*if(ac!=2)//확인
	{
		fprintf(stderr, "ex> usage: ./write /dev/pts/0\n");
		exit(1);
	}
    */
    
	if((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1)
	{
		perror(UTMP_FILE);
		exit(1);
	}
	while(read(utmpfd, &current, reclen) == reclen && find == 0)
	{
		if(current.ut_type == USER_PROCESS)
		{
			strcat(dev, current.ut_line);
            printf("%s is exist, %s\n", dev, current.ut_user);
			if(strcmp(av, dev) == 0)
            {
				find = 1;
                printf("I find him!\n");

            }
			strcpy(dev, "/dev/");
		}
	}
	close(utmpfd);

	if(find == 1)//log in
	{
		fd = open(av, O_WRONLY);
		if(fd == -1)
		{
			perror(av);
			exit(1);
		}
		printf("he is log in\n");
		tty_mode(0);

		while(1)
		{
			printf("press key : '1' = Send message, '2' = Send my schedule, 'q' = quit\n");
			alarms=0;
			set_cr_noecho_mode();
			input = getchar();
			//printf("input : %d\n",input);
			if(input == 49)
			{
				tty_mode(1);
				printf("Send message\n");
				printf("press key : 'ctrl + c + Enter' = quit\n");
				while( fgets(buf, BUFSIZ, stdin) != NULL)
                                {
                                        if(write(fd, buf, strlen(buf)) == -1)
                                                break;
                                        signal(SIGINT, quits);
                                        if(alarms==1)
                                                break;
                                }
			}

			if(input == 50)
			{
				printf("My schedule\n");
				readtxt(fd);
			}
			
			if(input == 113)
			{
				printf("Quit\n");
				break;
			}
		}	
		close(fd);
		tty_mode(1);
	} 
	else//log out
	{
		printf("he is log out\n");
	}
}

void set_cr_noecho_mode(void)
{
        struct termios ttystate;
        tcgetattr(0, &ttystate);
        ttystate.c_lflag &= ~ICANON;
        ttystate.c_lflag &= ~ECHO;
        ttystate.c_cc[VMIN] = 1;
        tcsetattr(0, TCSANOW, &ttystate);
}

void tty_mode(int how)
{
        static struct termios original_mode;
        if(how==0)
                tcgetattr(0, &original_mode);
        else
                tcsetattr(0, TCSANOW, &original_mode);
}

void quits(int signum)
{
	alarms =1;
}

int readtxt(int fd)
{
	int ffd;
	char buff[BUFF_SIZE];
	
	if(0 <	(ffd = open("./schedule.txt",O_RDONLY)))
	{
		read(ffd, buff, BUFF_SIZE);
		puts(buff);
		if(write(fd, buff, strlen(buff)) == -1)
			printf("sending failed\n");
		close(fd);
	}
	else
	{
		printf("file open failed\n");
		exit(1);
	}
	printf("Sending complete\n");
	return 0;
}

