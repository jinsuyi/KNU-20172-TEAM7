
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
//#include <unistd.h> : linux version
#include <WinSock2.h> // windows version

void error_handling(char *message);

int main()
{
	int fd;
	char buf[] = "schedule input \n";

	fd = open("data.txt", O_CREAT | O_APPEND | O_WRONLY); // O_CREAT : 파일생성, O_APPEND : 기존파일 보존 및 저장, O_WRONLY : write mode로 파일 오픈
	if (fd == -1)
		error_handling("error");
	
	printf("file descriptor : %d \n", fd);

	if (write(fd, buf, sizeof(buf)) == -1)
		error_handling("write() error!");
	close(fd);
	return 0;

}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}