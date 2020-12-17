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