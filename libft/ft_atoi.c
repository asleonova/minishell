/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbliss <dbliss@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 18:21:07 by dbliss            #+#    #+#             */
/*   Updated: 2020/05/21 12:59:57 by dbliss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	unsigned long long		res;
	int						i;
	int						n;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
			|| str[i] == '\n' || str[i] == '\v' || str[i] == '\f')
		str++;
	res = 0;
	if (str[0] == '-')
		n = -1;
	else
		n = 1;
	if (str[0] == '-' || str[0] == '+')
		str = str + 1;
	while (str[0] == '0')
		str++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (i > 19 || res >= 9223372036854775807)
		return (n == 1 ? -1 : 0);
	return (n * res);
}
