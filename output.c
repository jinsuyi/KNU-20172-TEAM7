
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
//#include <unistd.h> linux version
#include <winsock2.h> // windows version
#define BUF_SIZE 100
void error_handling(char *message);

int main()
{
	int fd;
	char buf[BUF_SIZE];

	fd = open("data.txt", O_RDONLY); // O_RDONLY : 읽기전용 파일 오픈
	if (fd == -1)
		error_handling("open() error");

	if (read(fd, buf, sizeof(buf)) == -1)
		error_handling("read() error!");
	printf("schedule : %s", buf);
	close(fd);
	return 0;

}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}