#include <stdio.h>
#include <curses.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "f1ser.c"

int row, col;
int count = 0;

int set_ticker(int );

void main_screen(void );
void chat_menu(void );
void time_menu(void );
void exiting(void );
void exec_func1(void);
void tty_mode(int how);

int main()
{
	int c;

    tty_mode(0); // 현재 tty 저장 
	initscr(); // 초기화
	crmode();
	noecho();
	clear();


	main_screen();	// 메인 화면

	while(1) // 'Q'입력 시 종료, '1'입력 시 1번메뉴, '2'입력 시 2번 메뉴
	{
		c = getchar();
		if(c == 'Q'){
			clear();
			break;
		}
		if(c=='1'){ // 채팅 메뉴 
			clear();
			chat_menu();
			while(1){ // 'B'입력 시 메인메뉴, '1'입력 시 1번메뉴, '2'입력 시 2번 메뉴
				c= getchar();
				if(c=='1'){ 
					clear();
                    exec_func1();    					
				}
				if(c=='2'){ 
					clear();
					refresh();					
				}
				if(c=='B'){
					clear();
					main_screen();
					break;
				}
                        }
		}
		if(c=='2'){ // 시간표 메
			clear();
			time_menu();
			while(1){ // 'B'입력 시 메인메뉴, '1'입력 시 1번메뉴, '2'입력 시 2번 메뉴
				c= getchar();
				if(c=='1'){ 
					clear();
					refresh();					
				}
				if(c=='2'){ 
					clear();
					refresh();					
				}
				if(c=='B'){
					clear();
					main_screen();
					break;
				}
                        }
		}
	}

	exiting();  // 종료 화면
    tty_mode(1);
	endwin(); // 종료

	return 0;
}

void main_screen(void ) // 메인메뉴
{
	move(1, 2);
	addstr("******************* Chatting and Timetable **********************");
	move(2, 2);
	addstr(">> press key : '1' : Chatting, '2' : Time Table, 'Q' : exit");	
;
	move(5, 2);
	addstr("         1. Chatting");

	move(8, 2);
	addstr("         2. TimeTable");

	move(13, 25);
	addstr("*** System Programming - TEAM7 ***");
	
	move(14, 25);
	addstr("*       2014105078 Lee Hae-JIn   *");
	move(15, 25);
	addstr("*       2014105078 Lee Hae-JIn   *");
	move(16, 25);
	addstr("*       2014105078 Lee Hae-JIn   *");
	move(17, 25);
	addstr("*       2014105078 Lee Hae-JIn   *");
	move(18, 25);
	addstr("**********************************");
	
	refresh();
}

void chat_menu() // 채팅 메뉴
{
	move(1, 2);
	addstr("******************* Chatting - Create or Enter ******************");
	move(2, 2);
	addstr(">> press key : '1' : Create, '2' : Enter, 'B' : back");	

	move(5, 2);
	addstr("         1. Create in chat room");

	move(8, 2);
	addstr("         2. Enter the chat room");

	move(13, 25);
	addstr("*** System Programming - TEAM7 ***");
	
	move(14, 25);
	addstr("*       2014105078 Lee Hae-JIn   *");
	move(15, 25);
	addstr("*       2014105078 Lee Hae-JIn   *");
	move(16, 25);
	addstr("*       2014105078 Lee Hae-JIn   *");
	move(17, 25);
	addstr("*       2014105078 Lee Hae-JIn   *");
	move(18, 25);
	addstr("**********************************");
	
	refresh();
}

void time_menu()  // 시간표 메뉴
{
	move(1, 2);
	addstr("******************* TimeTable - Notify or Modify ****************");
	move(2, 2);
	addstr(">> press key : '1' : Notify, '2' : Modify, 'B' : back");	

	move(5, 2);
	addstr("         1. Notify my timetable & Send Message");

	move(8, 2);
	addstr("         2. Modify my timetable");

	move(13, 25);
	addstr("*** System Programming - TEAM7 ***");
	
	move(14, 25);
	addstr("*       2014105078 Lee Hae-JIn   *");
	move(15, 25);
	addstr("*       2014105078 Lee Hae-JIn   *");
	move(16, 25);
	addstr("*       2014105078 Lee Hae-JIn   *");
	move(17, 25);
	addstr("*       2014105078 Lee Hae-JIn   *");
	move(18, 25);
	addstr("**********************************");
	
	refresh();
}

void exiting(void ) // 종료 시 화면
{
	int delay = 200;
	void move_msg(int );

	mvaddstr(8, 13, "Exiting program");
	row=8, col= 28;

	signal(SIGALRM, move_msg);
	set_ticker(delay);
	
	while(1){
		if (count == 10)
			break;
	}
}

void move_msg(int signum) // 종료화면 디테일
{
	signal(SIGALRM, move_msg);
	mvaddstr(row, col, ".");	
	count++;
	col++;			
	refresh();		
}

void exec_func1(void){ // 기능 1번
    
    int port, ppl;
    char tmp[100];
    clear();
    refresh();
    tty_mode(1);
	printf("\n******************* Create Chatting Room **********************\n\n");
	printf(">> press key : 'B' : back \n\n\n\n\n");	

	printf("         1. Type the port number: ");
    scanf("%s", tmp);
    if(!strcmp(tmp,"B")){
        noecho();
        crmode();
        clear();
       
        chat_menu();
        refresh();
        return;
    }
    else
        port = atoi(tmp);
    
    printf("\n\n\n\n");
    printf("         2. Type the max people allowed in the room: ");
    scanf("%s", tmp);
    if(!strcmp(tmp,"B")){
        noecho();
        crmode();
        clear();
        chat_menu();
        refresh();
        return;
    }
    else
        ppl = atoi(tmp);
    printf("\n");
    
    clear();
    refresh();
    f1ser(port, ppl);
}

void tty_mode(int how)
{
    static struct termios original_mode;
    
    if(how == 0)
        tcgetattr(0, &original_mode);
    else
        tcsetattr(0,TCSANOW, &original_mode);
}
