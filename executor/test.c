#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
// #include "srcs/cub3d.h"

typedef struct  s_data {
    int resolution_x;
    int resolution_y;
}               t_data;


typedef struct  s_all 
{
    t_data *data;
    int start_map;
    int end_map;
    int max_str;
    int height_map;
    char **map;
    int direction;
}               t_all;

int ft_strlen(char *str)
{
    int i = 0;
    while(str[i])
        i++;
    return(i);
}

int get_next_line(char **line, int fd)
{
    char c;
    int readed;
    char *tmp;
    int i = 0;

    if((readed = read(fd, &c, 1)) < 0)
        return(-1);
    if(!(*line = malloc(sizeof(char*))))
        return(0);
    line[0][0] = '\0';
    while(c != '\n' && readed != 0)    
    {
        tmp = *line;
        if(!(*line = malloc(ft_strlen(tmp) * sizeof(char*) + 2)))
            return(-1);
        while(tmp[i])
        {
            line[0][i] = tmp[i];
            i++;
        }
        line[0][i] = c;
        line[0][++i] = '\0';
        free(tmp);
        tmp = NULL;
        i = 0;
        readed = read(fd, &c, 1);
    }
    if(c == '\n')
        return(1);
    if(readed == 0)
        return(0);
    return(-1);
}

int	ft_atoi_mod(const char *line, int *i)
{
	int new_s;
	int negative;

	new_s = 0;
	negative = 1;
	while (line[*i] == ' ' || line[*i] == '\n' || line[*i] == '\t' ||
		line[*i] == '\v' || line[*i] == '\f' || line[*i] == '\r')
		(*i)++;
	if (line[*i] == '-')
		negative = -1;
	if (line[*i] == '-' || line[*i] == '+')
		(*i)++;
	while (line[*i] >= 48 && line[*i] <= 57)
	{
		new_s = new_s * 10 + (line[*i] - 48);
		(*i)++;
	}
	new_s = new_s * negative;
	return (new_s);
}

void ft_pass_space(char *line, int *i)
{
    while (line[*i] == ' ' || line[*i] == '\n' || line[*i] == '\t' ||
		line[*i] == '\v' || line[*i] == '\f' || line[*i] == '\r')
		(*i)++;
}

void checking_resolution(t_all *all, char *line, int *i)
{
    if(all->data->resolution_x != 0 && all->data->resolution_y != 0)
    {
        printf("4");
    }
    (*i)++;
    all->data->resolution_x = ft_atoi_mod(line, i);
    all->data->resolution_y = ft_atoi_mod(line, i);

    ft_pass_space(line, i);
}

int ft_parser_map(t_all *all, char *line, int num_str)
{
    int i;

    i = 0;
    while(line[i])
        if(line[i] == ' ' || line[i] == '1')
        {
            i++;
        }
        else
            return (-1);
    all->start_map = num_str;
    return (0);
}

int ft_parser(t_all *all, char *line, int num_str)
{
    int i;
    int n;

    i = 0;
    if(ft_strlen(line) == 0)
        return (-1);
    if(all->start_map < 0)
    {
        ft_parser_map(all, line, num_str);  
    }
    if(num_str >= all->start_map)
    {
        n = ft_strlen(line);
        if(n > all->max_str)
            all->max_str = n;
    }
    ft_pass_space(line, &i); // поправить для мап
    if(line[i] == 'R' && line[i + 1] == ' ')
        checking_resolution(all, line, &i);
    return (0);
}

t_data *create_data_struct()
{
    t_data *data;

    if(!(data = (t_data*)malloc(sizeof(t_data))))
        return (NULL);
    data->resolution_x = 0;
    data->resolution_y = 0;
    return (data);
}

t_all *create_all_struct()
{
    t_all *all;

    if(!(all = (t_all*)malloc(sizeof(t_all))))
        return (NULL);
    all->data = NULL;
    return (all);
}

t_all *initialization_of_structures(t_all *all)
{
    t_data *data;
    
    all = create_all_struct();
    all->data = create_data_struct();
    all->start_map = -1;
    all->end_map = -1;
    all->max_str = -1;
    all->height_map = -1;
    all->direction = -1;
    all->map = NULL;
    return (all);
}

int check_cell(t_all *all, char **map, char c, int i, int j)
{
    if(c != 'N' && c != 'S' && c != 'W' && c != 'E' && c != '0' && c != '2')
    {
        if (c == '1' || c == ' ')
            return (0);
        else
            return (1);
    }
    if(c == 'N' || c == 'S' || c == 'W' || c == 'E')
    {
        if(all->direction > 0)
            return (1);
        all->direction = 1;
    }
    if(map[i][j + 1] == ' ' || map[i][j - 1] == ' ' || map[i + 1][j] == ' ' || map[i - 1][j] == ' ') 
        return (1);
    if(!(map[i + 1][j] || !(map[i - 1][j])))
        return (1);
    return(0);
}

int check_edge_end(t_all *all, int i, int up)
{
    int j;

    up = 0;
    j = ft_strlen(all->map[i]) - 1;
    while(j >= 0 && all->map[i][j] != '0')
    {
        if(all->map[i - 1][j] == '1')
            up++;
        if(up == 0 && all->map[i - 1][j] == '0')
            return (1);
        j--;
    }
    if(up == 0)
        return (1);
    return (0);
}

int check_edge_origin(t_all *all, int i)
{
    int j;
    int up;

    j = 0;
    up = 0;
    if(i == 0)
        return (0);
    while(all->map[i][j] && all->map[i][j] != '0')
    {
        if(all->map[i][j] == ' ')
        {    
            j++;
            continue;
        }
        if(all->map[i - 1][j] == '1')
            up++;
        if(up == 0 && all->map[i - 1][j] == '0')
            return (1);
        j++;
    }
    printf("%d\n", up);
    if(up == 0)
        return (1);
    if(check_edge_end(all, i, up))
        return (1);
    return (0);
}

int validator_map(t_all *all)
{
    int i;
    int j;

    i = 0;
    while(all->map[i])
    {
        if(all->map[i][0] != ' ' && all->map[i][0] != '1')
            return (1);
        if(all->map[i][ft_strlen(all->map[i]) - 1] != ' ' && all->map[i][ft_strlen(all->map[i]) - 1] != '1')
            return (1);
        j = 0;
        printf("%s\n", all->map[i]);
        if(i == 0 || i == all->height_map - 1) 
        {
            while(all->map[i][j])
            {
                if(all->map[i][j] == '1' || all->map[i][j] == ' ')
                    j++;
                else
                    return (1);
            }
        }
        else
        {
            j++;
            while(j < ft_strlen(all->map[i]))
            {
                if(check_cell(all, all->map, all->map[i][j], i, j))
                    return (1);
                j++;
            }
        }
        if(check_edge_origin(all, i))
            return (1);
        i++;
    }
    return (0);
}

int main(int argc, char **argv)
{
    int i;
    int r;
    int fd;
    char *line;
    t_all *all;
    char **map;
    all = initialization_of_structures(all);
    i = 0;
    line = NULL;
    fd = open(argv[1], O_RDONLY);
    while((r = get_next_line(&line, fd)) > 0)
    {
        ft_parser(all, line, i);
        i++;
        free(line);
        line = NULL;
    }
    all->end_map = i;
    close(fd);
    fd = open(argv[1], O_RDONLY);
    i = 0;
    while(i < all->start_map)
    {
        get_next_line(&line, fd);
        i++;
    }
    all->height_map = all->end_map - all->start_map + 1;
    map = (char **)malloc(sizeof(char *) * (all->height_map + 1));
    i = 0;
    while(i < all->height_map)
    {
        map[i] = (char *)malloc(sizeof(char) * all->max_str);
        get_next_line(&line, fd);
        map[i] =  line;
        i++;
    }
    map[i] = NULL;
    all->map = map;
    if(validator_map(all))
    {
        printf("error map\n");
        return (1);
    }
    if(all->direction == -1)
    {
        printf("error no player\n");
        return (1);
    }
    printf("map ok\n");
    return (0);
}
