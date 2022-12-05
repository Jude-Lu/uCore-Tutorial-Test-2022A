#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    puts("start multiprocsignals\n");
    int pid = fork();
    if (pid == 0)
    {
        sleep(100);
        panic("It should be unreachable");
        return -1;
    }
    else
    {
        int code;
        assert_eq(kill(pid, SIGKILL), 0);
        assert_eq(waitpid(pid, &code), pid);
        assert_eq(code, 137);
    }
    puts("multiprocsignals passed!");
    return 0;
}