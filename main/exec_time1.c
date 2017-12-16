extern  void tty_mode(int);

#define BUFF_SIZE 1024
#define MAX_STRING 50

void set_cr_noecho_mode(void);
int readtxt(int);

void exec_time1()
{
	char name[MAX_STRING];
	char day[MAX_STRING];
	char buf[BUFSIZ];

	//utmp
	struct utmp current;
	int utmpfd;
	int reclen = sizeof(current);
	int find = 0;
	char dev[100]="/dev/";
	
	//tty
	int fd;
	int input; //


	mvaddstr(3,2,"         1. Type the username : ");
	refresh();
	if(scanf("%s", name) != 1){
		printf("\n\n>> Wrong input\n");
		sleep(2);
		return;
	}
	 
	/*
	mvaddstr(5,2,"         2. Type the ? : ");
	refresh();
	scanf("%s", nick);*/

	if((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1)
	{
		printf("\n\n>> Can't open UTMP_FILE\n");
		sleep(2); 
		return;
	}
	while(read(utmpfd, &current, reclen) == reclen && find == 0)
	{
		if(current.ut_type == USER_PROCESS)
		{
			if(strcmp(name, current.ut_name) == 0){ 
				find = 1;
				strcat(dev, current.ut_line);
			}
		}
	}
	close(utmpfd);

	if(find == 1) //log in
	{
		printf("\n>> %s is login now [TTY : %s]\n", name, dev);
		fd = open(dev, O_WRONLY);
		if(fd == -1){
			printf("\n\n>> Can't open tty : %s\n",dev);
			sleep(2);
			return;
		}

		//tty_mode(0);

		printf(">> Press key : '1' = Send message, '2' = Send my schedule, 'q' = quit\n");
		set_cr_noecho_mode();

		while(1)
		{
			input = getchar();
			if(input == 49){
				printf("\n  -> Type message : ");

				tty_mode(1);
				if(fgets(buf, BUFSIZ, stdin) != NULL){
					if(write(fd, buf, strlen(buf)) == -1){
						printf("\n\n>> You can't send a message to \"%s\"\n",name);
						sleep(2);
						break;
					}
					else printf("           [complete to send message]\n");
				}
				set_cr_noecho_mode();
			}

			if(input == 50)
			{
				printf("\n  -> Sending my schedule\n");
				tty_mode(1);
				readtxt(fd);
				set_cr_noecho_mode();			
			}
			
			if(input == 113)
			{
				printf("\n>> Quit!\n");
				sleep(1);
				break;
			}
		}	
		close(fd);
	} 
	else //user log out
	{
		printf("\n\n>> %s is not log in...\n", name);
		sleep(2);
		return;
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

int readtxt(int fd)
{
	int ffd;
	char buff[BUFF_SIZE];
	
	if(0 <	(ffd = open("./schedule.txt",O_RDONLY)))
	{
		read(ffd, buff, BUFF_SIZE);
		puts(buff);
		if(write(fd, buff, strlen(buff)) == -1)
			printf("\n           [Sending failed]\n");
		close(ffd);
	}
	else
	{
		printf("\n\n>> Fail to open the file\n");
		sleep(2);
		exit(1);
	}
	printf("\n           [Sending complete]\n");
	return 0;
}
