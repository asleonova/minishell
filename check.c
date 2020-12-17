#include <unistd.h>
#include <signal.h>

#include "minishell.h"

int sigint;
int sigquit;

void handler(int signal) 
{
    if (signal == SIGINT)
    {
       // write(1, "\b\b ^C\n", 4);
    }
	
}

int main()
{
	signal(SIGINT, handler);
return (0);
}