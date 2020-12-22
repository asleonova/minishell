#include "../minishell.h"

void ft_cd(t_commands *command, t_data *data)
{
    char *cwd;
    int status;

    if (command->count_args == 0) // cd only (without args)
    {
        change_env_values("OLDPWD=", data); // сохраняем текущий pwd в old_pwd в переменные окружения!!
		cwd = get_env_values(data, "HOME");
        printf("HOME: %s\n", cwd);
		chdir(cwd); // здесь мы попадаем в home
		free(cwd);
		cwd = getcwd(NULL, 0); // получаем новое значение для current directory
        change_env_values("PWD=", data); // сохраняем полученное значение в переменных окружения 
    }
    else // cd with path
    {
        change_env_values("OLDPWD=", data);
        status = chdir(command->arg_lst->content);
        if (status < 0)
           error_path(command);
	    else
	    {
		   cwd = getcwd(NULL, 0);
           change_env_values("PWD=", data); // сохраняем полученное значение в переменных окружения  
	    }
    }
}