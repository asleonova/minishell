#include <unistd.h>
#include "minishell.h"
int main()
{
	write(1, "hello\n",6);
	return (0);
}
