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

int main()
{
    sigact act;

    puts("start sigtest3\n");
    act.handler = sigio_handler;
    act.sa_mask = 0;
    assert_eq(sigaction(SIGIO, &act, NULL), 0);

    assert_eq(kill(getpid(), SIGIO), 0);
    sleep(1000);
    assert_eq(sigio, 1);

    sigprocmask(1U << SIGIO);
    assert_eq(kill(getpid(), SIGIO), -1);
    sigprocmask(0);

    assert_eq(kill(getpid(), SIGIO), 0);
    sleep(1000);
    assert_eq(sigio, 2);
    
    puts("sigtest3 passed!");
    return 0;
}
