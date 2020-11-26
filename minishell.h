#ifndef MINISHELL_H
#define MINISHELL_H

typedef	struct	s_list
{
	void			*content;
	struct s_list	*next;
}               t_list;

typedef enum    e_command_list
{
    echo = 0,
    cd = 1,
    pwd = 2,
    export = 3,
    unset = 4,
    env = 5,
    



}               t_command_list;
typedef struct          s_commands
{
    char                *cmd; // команда (например echo)
    int                 num_cmd; // мб потребуется, - порядковый номер команды, которые мы сами пишем, для системных один номер
    char                *cmd_dir; // директория системной команды 
    int                 count_args; // кол-во аргументов для команды (например echo hello world будет 2, так как hello - 1, world - 2 отдельно)
    int                 type_redir; // тип редиректа: < > >>
    int                 invalid; // флаг - команда невалидна
    struct s_list       *lst; // лист с аргументами команды, то есть echo hello world, hello - лсит№1, world лист #2
    struct s_commands   *redir;
    struct s_commands   *pipe;
    struct s_commands   *next; // next - это точка с запятой ;
}
                       t_commands;
typedef struct          s_data
{
    int                 fd_0;
    int                 fd_1;
    char                **envp; // переменные окружения (длинный список) - type in termibal env to see how it looks like
    int                 home_dir; // порядковый номер переменной окружения в домашней директории HOME
    int                 current_pwd; // текущиий pwd PWD=
    int                 old_pwd; // OLDPWD=
    int                 env_var; // мб вновь созданные переменные окружения
    int                 path; // PATH= 
    int                 count_str; // кол-во строк
    char                *error_string; // текст ошибки
}                       t_data;

#endif