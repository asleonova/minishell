#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define SUCCESS 0
#define FAIL 1

typedef enum    e_command_names
{
    echo = 0,
    cd = 1,
    pwd = 2,
    export = 3,
    unset = 4,
    env = 5,
    our_exit = 6,
    bash = 7
}               t_command_names;

typedef enum    e_redirect // установить сначала -1!!!!
{
    redir = 1,
    double_redir = 2,
    back_redir = 3
}               t_redirect;

typedef struct          s_commands
{
    int                 fd_0;
    int                 fd_1;
    char                *cmd; // команда (например echo)
    int                 count_args; // кол-во аргументов для команды (например echo hello world будет 2, так как hello - 1, world - 2 отдельно)
    int                 invalid; // флаг - команда невалидна, 1
    int                 status;
    t_command_names     cmd_list;
    t_redirect          type_redir;
    struct s_list       *lst; // лист с аргументами команды, то есть echo hello world, hello - лсит№1, world лист #2
}                       t_commands;
     
typedef struct          s_data
{

    char                **envp; // переменные окружения (длинный список) - type in termibal env to see how it looks like
    char                *home; // порядковый номер переменной окружения в домашней директории HOME
    char                *cwd; // текущиий pwd PWD=
    char                *old_pwd; // OLDPWD=
    char                *env_var; // мб вновь созданные переменные окружения
    char                *path; // PATH= 
    int                 count_str; // кол-во строк
    char                *error_string; // текст ошибки
}                       t_data;

#endif