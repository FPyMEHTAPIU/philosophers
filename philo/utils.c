/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msavelie <msavelie@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:38:15 by msavelie          #+#    #+#             */
/*   Updated: 2024/12/19 16:17:25 by msavelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putendl_fd(char *s, int fd)
{
	int	i;

	if (!s)
	{
		if (write(fd, "(null)", 6) < 0)
			return (-1);
		return (6);
	}
	i = 0;
	while (s[i])
	{
		i += write(fd, &s[i], 1);
		if (i < 0)
			return (-1);
	}
	i += write(fd, "\n", 1);
	return (i);
}

int	is_number(char *arg)
{
	int	i;

	if (!arg || !*arg)
		return (0);
	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	check_range(int num, int sign, const char *str)
{
	long long	check;

	while ((*str >= '0' && *str <= '9') && *str)
	{
		check = num * 10 + *str - '0';
		if ((check == -2147483648 || check == 2147483648) && sign == -1)
			return (-2147483648);
		if (check == 2147483647 && sign == 1)
			return (2147483647);
		if (check / 10 != num && sign == 1)
			return (-1);
		if (check / 10 != num && sign == -1)
			return (0);
		num = check;
		str++;
	}
	return ((num * sign));
}

int	ft_atoi(const char *str)
{
	int			sign;
	int			num;

	num = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	return (check_range(num, sign, str));
}
