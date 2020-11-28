#include <unistd.h>
#include "minishell.h"
int main()
{
	char *param;
	param = "hello";
	ft_putstr_fd("minishell: cd: ", 1);
	ft_putstr_fd(param, 1);
	ft_putstr_fd(": No such file or directory\n", 1);
	return (0);
}
