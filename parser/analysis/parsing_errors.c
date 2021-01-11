#include "../../minishell.h"

int syntax_error(void)
{
    ft_putstr_fd("minishell: syntax error near unexpected token\n", 1);
	g_error = 258;
	return (g_error);
}