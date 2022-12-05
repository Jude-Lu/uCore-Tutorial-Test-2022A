#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int sigio = 0, sigalrm = 0;

void sigio_handler()
{
    sigio++;
    sigreturn();
}

void sigalrm_handler()
{
    sigalrm++;
    sigreturn();
}

int main()
{
    sigact act;

    puts("start sigtest2\n");
    act.handler = sigio_handler;
    act.sa_mask = 0;
    assert_eq(sigaction(SIGIO, &act, NULL), 0);
    act.handler = sigalrm_handler;
    act.sa_mask = 0;
    assert_eq(sigaction(SIGALRM, &act, NULL), 0);

    assert_eq(kill(getpid(), SIGIO), 0);
    sleep(100);
    assert_eq(sigio, 1);

    assert_eq(kill(getpid(), SIGIO), 0);
    assert_eq(kill(getpid(), SIGALRM), 0);
    sleep(100);
    assert_eq(sigio, 2);
    assert_eq(sigalrm, 1);
    
    puts("sigtest2 passed!");
    return 0;
}
