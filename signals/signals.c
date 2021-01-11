#include "../minishell.h"

void handler(int signal) 
{
    if (signal == SIGINT)
    {
       write(1, "\b\b  \n", 5);
	   intro();
    }
	if (signal == SIGQUIT)
		write(1, "\b\b  \b\b", 6); 
}

void signals_default(void)
{
    signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void signals_ignore(void)
{
    signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}