#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int sigio = 0;
int sigkill = 0;

void handler(int signum, void *info, void *context)
{
	if(signum == SIGIO) {
		sigio++;
		printf("SIGIO   signal: %d\n", signum);
	}
	else if(signum == SIGKILL) {
		sigkill++;
		printf("SIGKILL   signal: %d\n", signum);
	}
	else
		printf("error\n");
}

int main()
{
	sigact act;

	act.handler = handler;
	act.sa_mask = SA_SIGINFO;

	puts("start sigtest\n");
	printf("hello sigtest\n");
	sigaction(SIGIO, &act, NULL);
	sigaction(SIGKILL, &act, NULL);

	sleep(1000);
	kill(getpid(), SIGIO);
	sleep(1000);
	kill(getpid(), SIGKILL);
	sleep(1000);

	assert_eq(sigio, 1);
	assert_eq(sigkill, 1);
	puts("sigtest passed!");
	return 0;
}
