#include "../minishell.h"

int ft_cd(t_commands *command, t_data *data)
{
    char *cwd;
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
        // здесь нужно сначала записать старое значение в пвд, потом сделать chdir с тем значением, которое пришло в аргументы
        // потом проверить на валиднсть
        // и если валидно, то записать в пвд новое значение!
	    if (chdir(command->lst) < 0) // если путь, который записан в аргументы невалидный
        {
            error_path(command);
            return(FAIL);
        }
	    else // тут продумать лучше, как менять!!!!
	    {
            change_env_values("OLDPWD=", data); // сохраняем текущий pwd в old_pwd в переменные окружения!!!
		    cwd = getcwd(NULL, 0);
            change_env_values("PWD=", cwd); // сохраняем полученное значение в переменных окружения  
	    }
    }
}

