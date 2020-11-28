#include "../minishell.h"

int ft_cd(t_commands *command, t_data *data)
{
    char *cwd;
    if (command->count_args == 0) // cd only (without args)
    {
        // обязательно нужно сохранить значение pwd в old_pwd перед запуском функции в переменные окружения!!!
		cwd = get_env_values(data->envp, "HOME");
		chdir(cwd); // здесь мы попадаем в home
		free(cwd);
		data->cwd = getcwd(NULL, 1000); // получаем новое значение для current directory
        // обязательно нужно сохранить значение текущее значение pwd в переменные окружения
    }
    else // cd with path
    {
	    if (chdir(command->lst) < 0) // если путь, который записан в аргументы невалидный
		    error_path(command);
	    else
	    {
		    // обязательно нужно сохранить значение pwd в old_pwd перед запуском!
		    data->cwd = getcwd(NULL, 1000);
            // обязательно нужно сохранить значение текущее значение pwd в переменные окружения
	    }
    }
    
}

