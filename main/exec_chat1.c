extern void chatting(int , int , fd_set , char *);

#define MAXLINE 100
#define CHATDATA 1024
#define INVALID_SOCK -1

int MAX_CLIENT =  1000;
int usr_max_client = 0;
char greeting[] = "\n>> Welcome to chatting room ( /quit : exit, /list : user list, /smsg : whisper)\n";
char ERROR[] = "\n>> Sorry, the room is full! ( /quit : exit )\n";
char SERVER_QUIT[] = "\n>> There is no server owner. Please input \"/quit\"\n";

char quit[] = "/quit\n";
char list[] = "/list\n";
char smsg[] = "/smsg";

struct List_c {
	int socket_num;
	char nick[CHATDATA];
	char ip[40];
	int port;
}list_c[1000];

/*************************************/
int pushClient(int, char*, char*, int);
int popClient(int);
void constr_func(int, int);
void quit_func(int);
void list_func(int);
int smsg_func(char*, int);
void make_client(char*, int, char*);
/*************************************/
int f1ser(int, int);

void exec_chat1(void ){ // first menu of chatting 
    
	int port, ppl;
	
	mvaddstr(3,2,"         1. Type the port number : ");
	refresh();
	if(scanf("%d", &port) != 1){
		printf("\n\n>> Wrong input\n");
		sleep(2);
		return;
	}

	mvaddstr(5,2,"         2. Type the max people allowed in the room : ");
	refresh();
	if(scanf("%d", &ppl) != 1){
		printf("\n\n>> Wrong input\n");
		sleep(2);
		return;
	}

	f1ser(port, ppl);
}

/*************************************************************************/
int pushClient(int connfd, char* c_nick, char* c_ip, int c_port) {
	int i;

	for (i = 0; i<usr_max_client; i++) {
		if (list_c[i].socket_num == INVALID_SOCK) {
			list_c[i].socket_num = connfd;
			strcpy(list_c[i].nick, c_nick);
			strcpy(list_c[i].ip, c_ip);
			list_c[i].port = c_port;
			return i;
		}
	}

	if (i == MAX_CLIENT)
		return -1;
}

int popClient(int s)
{
	int i;

	for (i = 0; i<usr_max_client; i++) {
		if (s == list_c[i].socket_num) {
			list_c[i].socket_num = INVALID_SOCK;
			memset(list_c[i].nick, 0, sizeof(list_c[i].nick));
			memset(list_c[i].ip, 0, sizeof(list_c[i].ip));
			break;
		}
	}
	close(s);
	return 0;
}

void constr_func(int i, int index) {
	char buf1[MAXLINE];

	memset(buf1, 0, sizeof(buf1));
	sprintf(buf1, "     [%s is connected]\r\n", list_c[index].nick);
	write(list_c[i].socket_num, buf1, strlen(buf1));

	sprintf(buf1, "     [%s is connected]\r\n", list_c[i].nick);
	write(list_c[index].socket_num, buf1, strlen(buf1));
}

void quit_func(int i) {
	int j;
	char* token = NULL;
	char buf1[MAXLINE];

	memset(buf1, 0, sizeof(buf1));
	for (j = 0; j<MAX_CLIENT; j++)
		if (j != i && list_c[j].socket_num != INVALID_SOCK) {
			sprintf(buf1, "    >> %s has left the %s\r\n", list_c[i].nick, list_c[i].ip);
			write(list_c[j].socket_num, buf1, strlen(buf1));
		}

	popClient(list_c[i].socket_num);
}

void list_func(int i) {
	int j, cnt = 0;
	char buf1[MAXLINE];

	memset(buf1, 0, sizeof(buf1));
	for (j = 0; j<MAX_CLIENT; j++)
		if (list_c[j].socket_num != INVALID_SOCK) cnt++;
	sprintf(buf1, "    >>the number of current user is %d\r\n", cnt);
	write(list_c[i].socket_num, buf1, strlen(buf1));
	for (j = 0; j<MAX_CLIENT; j++)
		if (list_c[j].socket_num != INVALID_SOCK) {
			sprintf(buf1, "     [%s from %s:%d]\r\n", list_c[j].nick, list_c[j].ip, list_c[j].port);
			write(list_c[i].socket_num, buf1, strlen(buf1));
		}
}

int smsg_func(char* chatData, int i) {
	int j, smsg_sock;
	char* token = NULL;
	char buf1[MAXLINE];

	memset(buf1, 0, sizeof(buf1));
	token = strtok(chatData, " ");
	char * end;

	if (strcmp(token, smsg)) {
		if ((end = strtok(NULL, "\n")) == NULL)
			sprintf(buf1, "%s", token);
		else sprintf(buf1, "%s %s", token, end);
		sprintf(chatData, "[%s] %s\n", list_c[i].nick, buf1);
		return 1;
	}
	else {
		token = strtok(NULL, " ");
		for (j = 0; j<MAX_CLIENT; j++)
			if (!strcmp(list_c[j].nick, token))
				smsg_sock = list_c[j].socket_num;
		token = strtok(NULL, "\n");
		memset(buf1, 0, sizeof(buf1));
		sprintf(buf1, "[smsg from %s] %s\r\n", list_c[i].nick, token);
		write(smsg_sock, buf1, strlen(buf1));
		return 0;
	}
}

void exec_client(char* ip, int port, char* nick)
{
	int sockfd;
	struct sockaddr_in servaddr;
	int maxfdp1;
	fd_set rset;

	int len;
	char chatData[CHATDATA];
	char buf[CHATDATA];
	int n;
	char* token = NULL;
		
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_addr.s_addr = inet_addr(ip);
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

int f1ser(int port,  int ppl)
{
	struct linger ling; // TIME_WAIT 방지
	int connfd, listenfd;
	struct sockaddr_in servaddr, cliaddr;
	int clilen;
	int maxfd = 0;  
	int i, j, n;
	fd_set rset;

	int pid;
	int index;

	char* token = NULL;
	char buf1[MAXLINE];
	char buf2[MAXLINE];
	char chatData[CHATDATA];
	char nick[MAXLINE];

	MAX_CLIENT = ppl;
	usr_max_client = MAX_CLIENT;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	// TIME_WAIT 방지 -> 기존에 썻던 port번호를 다시 쓸 수 있음
	ling.l_onoff = 1;
	ling.l_linger = 0;
	setsockopt(listenfd, SOL_SOCKET,SO_LINGER, &ling,sizeof(ling));

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);

	if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1) {
		printf("\n\n>> Error : that port is already being used\n");
		sleep(2);
		return -1;
	}
	if (listen(listenfd, MAX_CLIENT) == -1) {
		printf("\n\n>> Room is full\n");
		sleep(2);
		return -1;
	}

	for (i = 0; i<MAX_CLIENT; i++)
		list_c[i].socket_num = INVALID_SOCK;

	memset(buf1, 0, sizeof(buf1));
	inet_ntop(AF_INET, &servaddr.sin_addr, buf1, sizeof(buf1));
	
	printf("\n\n>> Server Domain\n");
	printf("     - Room max = %d\n", usr_max_client);
	printf("     - [server address is %s : %d]\n", buf1, ntohs(servaddr.sin_port));
	printf("     - type your nickname : ");
   	scanf("%s",nick);


	pid = fork();
	if( pid == -1)
	        perror("fork");
	else if(pid == 0){
        	exec_client(buf1,port,nick);
		exit(0);
	}
	else{
		printf("\n>> - Notice : you are admin. You get to see the address of the joiner.\n");
        	printf("   - Warning : if you close the room, other users can't chat anymore\n");

		for (; ; )
		{
		
			maxfd = listenfd;

			FD_ZERO(&rset);
			FD_SET(listenfd, &rset);
			for (i = 0; i<MAX_CLIENT; i++) {
				if (list_c[i].socket_num != INVALID_SOCK) {	
					FD_SET(list_c[i].socket_num, &rset);
					if (list_c[i].socket_num > maxfd) maxfd = list_c[i].socket_num;
				}
			}
			maxfd++;

			// close(listenfd)로 인한 error
			if (select(maxfd, &rset, (fd_set *)0, (fd_set *)0, (struct timeval *)0) < 0) {
				printf("\n\n>> The server shuts down.\n");
				sleep(2);
				return 1;
			}

			if (FD_ISSET(listenfd, &rset)) { //클라이언트 push , 연결메시지 
				clilen = sizeof(cliaddr);
				if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) > 0) {
					memset(buf1, 0, sizeof(buf1));
					memset(buf2, 0, sizeof(buf2));
					read(connfd, buf1, sizeof(buf1));//read client's nickname
					inet_ntop(AF_INET, &cliaddr.sin_addr, buf2, sizeof(buf2));
					index = pushClient(connfd, buf1, buf2, ntohs(cliaddr.sin_port));//push socknum,nick,ip,port_num of client
		        if(index!=-1)
		            printf("  (server) %s is connected from %s\r\n", list_c[index].nick, list_c[index].ip);
		        else
		            printf("  (server) due to the room full, connection rejected\n");

					if (index<0) {
						write(connfd, ERROR, strlen(ERROR));
						close(connfd);
					}
					else {
						write(connfd, greeting, strlen(greeting));
						for (i = 0; i<MAX_CLIENT; i++)
							if (i != index && list_c[i].socket_num != INVALID_SOCK) {
								constr_func(i, index);
						}
					}
				}
			}

			for (i = 0; i<MAX_CLIENT; i++) {
				if ((list_c[i].socket_num != INVALID_SOCK) && FD_ISSET(list_c[i].socket_num, &rset)) {
					memset(chatData, 0, sizeof(chatData));
					if ((n = read(list_c[i].socket_num, chatData, sizeof(chatData)))>0) {
						if (!strcmp(chatData, quit)) {//disconnect from the client "i"
							quit_func(i);
							continue;
						}
						if (!strcmp(chatData, list)) {//print the list of clients
							list_func(i);
							continue;
						}
						if (strstr(chatData, smsg) != NULL) {
							if (smsg_func(chatData, i) == 0) continue;
							else;
						}
						for (j = 0; j<MAX_CLIENT; j++) {//send chatting letters
							if (list_c[i].socket_num != INVALID_SOCK)
								if (j != i)
									write(list_c[j].socket_num, chatData, sizeof(chatData));
						}
					}
				}
			}
			if(list_c[0].socket_num == INVALID_SOCK){ // server를 갖는 client가 server에 없을 경우
				for (i = 0; i<MAX_CLIENT; i++) {// 각 client에게 /quit입력하라고 메세지 보냄
					if (list_c[i].socket_num != INVALID_SOCK)
							write(list_c[i].socket_num, SERVER_QUIT, sizeof(SERVER_QUIT));
				}
				close(listenfd);
			}
		}
	}
}
