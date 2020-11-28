#include "../minishell.h"

int ft_cd(t_commands *command, t_data *data)
{
    char *cwd;
    if (command->count_args == 0) // cd only (without args)
    {
        set_env_values("OLDPWD", cwd = get_env_values(data->envp, "PWD")); // сохраняем текущий pwd в old_pwd в переменные окружения!!!
		free(cwd);
		cwd = get_env_values(data->envp, "HOME");
		chdir(cwd); // здесь мы попадаем в home
		free(cwd);
		cwd = getcwd(NULL, 1000); // получаем новое значение для current directory
        set_env_values("PWD", cwd); // сохраняем полученное значение в переменных окружения 
    }
    else // cd with path
    {
	    if (chdir(command->lst) < 0) // если путь, который записан в аргументы невалидный
        {
            error_path(command);
            return(FAIL);
        }
	    else
	    {
            set_env_values("OLDPWD", cwd = get_env_values(data->envp, "PWD")); // сохраняем текущий pwd в old_pwd в переменные окружения!!!
            free(cwd);
		    cwd = getcwd(NULL, 1000);
            set_env_values("PWD", cwd); // сохраняем полученное значение в переменных окружения  
	    }
    }
}

