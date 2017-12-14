
/****************************************
declared at exec_chat1.c

#define MAXLINE 100
#define CHATDATA 1024

char quit[] = "/quit\n";
char list[] = "/list\n";
char smsg[] = "/smsg";
*****************************************/

void chatting(int sockfd, int maxfdp1, fd_set rset, char *nickname)
{
	char chatData[CHATDATA];
	char buf[CHATDATA];
	int n;

	while (1) {
		FD_ZERO(&rset);
		FD_SET(0, &rset);
		FD_SET(sockfd, &rset);

		if (select(maxfdp1, &rset, (fd_set *)0, (fd_set *)0, (struct timeval *)0) <0) {
			printf("\n\n>> select error\n");
			sleep(2);
			return;
		}

		if (FD_ISSET(sockfd, &rset)) {
			memset(chatData, 0, sizeof(chatData));
			if ((n = read(sockfd, chatData, sizeof(chatData))) >0) {
				write(1, chatData, n);
			}
		}

		if (FD_ISSET(0, &rset)) {
			memset(buf, 0, sizeof(buf));
			if ((n = read(0, buf, sizeof(buf)))>0) {
				if (!strcmp(buf, quit)) {
					write(sockfd, buf, strlen(buf));
					break;
				}
				if (!strcmp(buf, list)) {
					write(sockfd, buf, strlen(buf));
					continue;
				}
				if (strstr(buf, smsg) != NULL) {
					write(sockfd, buf, strlen(buf));
					continue;
				}
				sprintf(chatData, "[%s] %s", nickname, buf);
				write(sockfd, chatData, strlen(chatData));
			}
		}
	}
}
void exec_chat2()
{
	int port;
	char nick[MAXLINE], ip[MAXLINE];

	int sockfd;
	struct linger ling; // CLOSE_WAIT 방지
	struct sockaddr_in servaddr;
	int maxfdp1;
	fd_set rset;

	int len;
	char chatData[CHATDATA];
	char buf[CHATDATA];
	int n;
	char* token = NULL;

	mvaddstr(3,2,"         1. Type the port number : ");
	refresh();
	if(scanf("%d", &port) != 1){
		printf("\n\n>> Wrong input\n");
		sleep(2);
		return;
	}
	 
	mvaddstr(5,2,"         2. Type your name : ");
	refresh();
	scanf("%s", nick);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// CLOSE_WAIT 방지
	ling.l_onoff = 1;
	ling.l_linger = 0;
	setsockopt(sockfd, SOL_SOCKET,SO_LINGER, &ling,sizeof(ling));

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_addr.s_addr = inet_addr("0.0.0.0");
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);


	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
		printf("\n\n>> Can not connect\n");
		sleep(2);
		return;
	}

	write(sockfd, nick, strlen(nick)); //send client's nickname
	maxfdp1 = sockfd + 1;

	chatting(sockfd, maxfdp1, rset, nick);

	close(sockfd);
}
