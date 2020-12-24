#include <stdio.h>

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)
			|| (c >= 48 && c <= 57))
		return (1);
	return (0);
}

int main()
{
    int res;
    int i = 23;
    res = ft_isalnum(i);
    printf("RES: %d\n", res);
    return(0);
}