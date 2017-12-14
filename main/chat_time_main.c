#include "header.h"

#include "exec_chat1.c"
#include "exec_chat2.c"
//#include "exec_time1.c"
//#include "exec_time2.c"

#define BACKMENU "Back to top menu"
#define EXITING "Exiting program"

int row, col;
int count = 0;

int set_ticker(int );
void tty_mode(int);

void main_screen(void );
void chat_menu(int );
void time_menu(int );
void loading(char* );

int main()	
{
	int c;
 
	tty_mode(0);
	initscr(); // 초기화

	crmode();
	noecho();

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
			while(1){ // 'B'입력 시 메인메뉴, '1'입력 시 1번메뉴, '2'입력 시 2번 메뉴
				chat_menu(0);
				c= getchar();
				if(c=='1'){
					clear();
					chat_menu(1);
					tty_mode(1);

					exec_chat1(); // 해당 함수 끝난 후 다시 상위 메뉴로 돌아가기

					loading(BACKMENU); 
				}
				if(c=='2'){ 
					clear();
					chat_menu(2);
					tty_mode(1);

					exec_chat2();					

					loading(BACKMENU);					
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
			while(1){ // 'B'입력 시 메인메뉴, '1'입력 시 1번메뉴, '2'입력 시 2번 메뉴
				time_menu(0);
				c= getchar();
				if(c=='1'){ 
					clear();
					time_menu(1);
					tty_mode(1);

					//exec_time1();
				
					loading(BACKMENU); 						
				}
				if(c=='2'){ 
					clear();
					time_menu(1);
					tty_mode(1);
		
					//exec_time2();					

					loading(BACKMENU); 				
				}
				if(c=='B'){
					clear();
					main_screen();
					break;
				}
                        }
		}
	}

	loading(EXITING);  // 종료 화면

	return 0;
}

void main_screen() // 메인메뉴
{
	clear();
	
	move(1, 2);
	addstr("******************* Chatting and Timetable **********************");
	move(2, 2);
	addstr(">> press key : '1' : Chatting, '2' : Time Table, 'Q' : exit");	

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

void chat_menu(int mode) // 채팅 메뉴
{
	clear();
	if(mode == 0){
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
	}
	else if(mode == 1){
		move(1, 2);
		addstr("********************** Create Chatting Room *********************");
		//move(2, 2);
		//addstr(">> press key : 'B' : back");	
	}
	else if(mode == 2){
		move(1, 2);
		addstr("*********************** Enter Chatting Room *********************");
		//move(2, 2);
		//addstr(">> press key : 'B' : back");	
	}
	
	refresh();
}

void time_menu(int mode)  // 시간표 메뉴
{
	clear();
	
	if(mode == 0){
		move(1, 2);	
		addstr("******************* TimeTable - Notify or Modify ****************");
		move(2, 2);
		addstr(">> press key : '1' : Notify, '2' : Modify, 'B' : back");	
		move(5, 2);
		addstr("         1. Notify my timetable");

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
	}
	else if(mode == 1){
		move(1, 2);	
		addstr("*********************** Notify my timetable *********************");
		//move(2, 2);
		//saddstr(">> press key : 'B' : back");
	}
	else if(mode == 2){
		move(1, 2);	
		addstr("*********************** Modify my timetable *********************");
		//move(2, 2);
		//addstr(">> press key : 'B' : back");
	}	

	refresh();
}

void loading(char *string ) // 종료 시 화면
{
	int delay = 200;
	void move_msg(int signum){
		signal(SIGALRM, move_msg);
		mvaddstr(row, col, ".");	
		count++;
		col++;			
		refresh();
	}
	clear();
	if(strcmp(string, BACKMENU) == 0 ){
		crmode();
		noecho();	
	}
	mvaddstr(8, 13, string);
	row=8, col= 13 + strlen(string);

	signal(SIGALRM, move_msg);
	set_ticker(delay);
	
	while(1){
		if (count == 10){
			count=0;
			alarm(0);
			break;
		}
	}

	if(strcmp(string, EXITING) == 0 ){
		tty_mode(1);
		endwin();
	}
}

int set_ticker(int n_msecs)
{
	struct itimerval new_timeset;
	long n_sec, n_usecs;

	// sec, usec 조정
	n_sec = n_msecs / 1000;
	n_usecs = (n_msecs % 1000) * 1000L ;  
	
	new_timeset.it_interval.tv_sec = n_sec;
	new_timeset.it_interval.tv_usec = n_usecs;
	new_timeset.it_value.tv_sec = n_sec;
	new_timeset.it_value.tv_usec = n_usecs;

	// setitimer : 구조체에서 명시된 값에 의해 타이머를 설정
	// ITIMER_REAL : 실시간으로 감소하고타이머 만료 시 SIGALRM 신호 전달
	return setitimer(ITIMER_REAL, &new_timeset, NULL);
}

void tty_mode(int how)
{
	static struct termios original_mode;
	if(how == 0)
		tcgetattr(0, &original_mode);
	else
		tcsetattr(0, TCSANOW, &original_mode);
}
