#include "../minishell.h"

int ft_cd(t_commands *command, t_data *data)
{
    char *cwd;
    int status;

    if (command->count_args == 0) // cd only (without args)
    {
        change_env_values("OLDPWD=", data); // сохраняем текущий pwd в old_pwd в переменные окружения!!
		cwd = get_env_values(data->envp, "HOME");
		chdir(cwd); // здесь мы попадаем в home
		free(cwd);
		cwd = getcwd(NULL, 0); // получаем новое значение для current directory
        change_env_values("PWD", cwd); // сохраняем полученное значение в переменных окружения 
    }
    else // cd with path
    {
        change_env_values("OLDPWD=", data);
        status = chdir(command->lst);
        if (status < 0)
           error_path(command);
	    else
	    {
		    cwd = getcwd(NULL, 0);
            change_env_values("PWD=", cwd); // сохраняем полученное значение в переменных окружения  
	    }
    }
}