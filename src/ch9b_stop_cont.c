#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    puts("start stop_cont\n");
    for (int iter = 0;iter < 10;++iter)
    {
        int pid = fork();
        if (pid == 0)
        {
            int64 current_time = get_mtime();
            kill(getpid(), SIGSTOP);
            if (get_mtime() < current_time + 30)
                panic("Was it really stopped?");
            return 0;
        }
        else
        {
            sleep(50);
            kill(pid, SIGCONT);
        }
    }
    puts("stop_cont passed!");
    return 0;
}