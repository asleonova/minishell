#include "minishell.h"

void ijk_zero(t_var *var)
{
	var->i = 0;
	var->j = 0;
	var->k = 0;
	var->error = 0;
	var->cf = 0;
	var->ef = 0;
	var->sf = 0;
	var->df = 0;
	var->quote = 0;
	var->env = NULL;
	var->list = NULL;
}

void intro(void)
{
	write(1, "minishell: ", 11);
}

int done(t_var *var)
{
	if(!(ft_strncmp(var->str, "exit", 4)))
		return (0);
 	return (1);
}

int main(int argc, char **argv, char **envp)
{
	t_var	var;
	int 	i;
	
	i = 1;
	argc = 0;
	argv = NULL;
	//parsing_env(&envp, "HOME");
	ijk_zero(&var);
	
	while(i && !var.error)
	{
        signal(SIGINT, handler);
        signal(SIGQUIT, handler);
		ijk_zero(&var);
		intro();
		get_next_line(0, &var.str);
		parser(&var);
		analysis_list(&var, &envp);
		i = done(&var);
	}
	if(var.error)
		write(1, "Error program", 14);
	return(0);
}