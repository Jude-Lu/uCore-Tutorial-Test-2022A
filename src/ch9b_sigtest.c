#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int sigio = 0;

void handler()
{
    sigio++;
    sigreturn();
}

int main()
{
    sigact act;

    act.handler = handler;
    act.sa_mask = 0;

    puts("start sigtest\n");
    printf("hello sigtest\n");
    assert_eq(sigaction(SIGIO, &act, NULL), 0);
    assert_eq(sigaction(SIGKILL, &act, NULL), -1);

    sleep(1000);
    assert_eq(kill(getpid(), SIGIO), 0);
    sleep(1000);

    assert_eq(sigio, 1);
    puts("sigtest passed!");
    return 0;
}
