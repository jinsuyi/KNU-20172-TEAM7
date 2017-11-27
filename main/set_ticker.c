/* 각 소스파일 상단에 반드시 다음 네 가지 주석 추가
- file: set_ticker.c
- author: 2014105078_이해진
- datetime: 2017_11_21
- description: 지정된 시간마다 SIGALRM호출 -> 해당 handler 실행
		sec, usec 2개 조정
*/

#include <stdio.h>
#include <sys/time.h>

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
