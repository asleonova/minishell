#include "minishell.h"

void ijk_zero(t_var *var)//, t_data *data)
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
	//data->home = get_env_values(data->envp, "HOME");
	
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
	//t_data  data;
	//t_commands command;
	//t_list lst_global;
	int 	i;
	envp =NULL;
	i = 1;
	argc = 0;
	argv = NULL;
	//data.envp = envp;
	//parsing_env(&envp, "HOME");
	ijk_zero(&var);//, &data);
	
	while(i && !var.error)
	{
        signal(SIGINT, handler);
        signal(SIGQUIT, handler);
		ijk_zero(&var);//, &data);
		intro();
		get_next_line(0, &var.str);
		parser(&var);
		analysis_list(&var, &envp);
		//executor(&command, &lst_global, &data);
		i = done(&var);
	}
	if(var.error)
		write(1, "Error program", 14);
	return(0);
}
