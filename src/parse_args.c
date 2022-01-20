/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:54:49 by tlemma            #+#    #+#             */
/*   Updated: 2022/01/20 14:04:28 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	isvalidstr(const char *s)
{
	int	i;
	int	foundnum;

	i = 0;
	foundnum = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]))
			foundnum = 1;
		if (!(s[i] == ' ' || s[i] == '\n' || s[i] == '\t'
				|| s[i] == '\v' || s[i] == '\f' || s[i] == '\r'
				|| s[i] == '+' || s[i] == '-'))
			if (!foundnum)
				return (0);
		if ((s[i] == '+' || s[i] == '-') && !ft_isdigit(s[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

int	check_input(char **nums)
{
	char	*num;

	while (*nums)
	{
		num = *nums;
		if (!isvalidstr(num))
			return (0);
		if (ft_atoi(num) > INT_MAX || ft_atoi(num) < INT_MIN
			|| ft_atoi(num) <= 0)
			return (0);
		while (*num)
		{
			if (!ft_isdigit(*num) && *num != ' ' && *num != '-')
				return (0);
			num++;
		}
		nums++;
	}
	return (1);
}

long	ft_atoi(const char *str)
{
	int				i;
	long			num;
	long			sign;
	unsigned int	digit;

	i = 0;
	num = 0;
	sign = -1;
	if (!isvalidstr(str))
		return (-1);
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && num)
			break ;
		if (ft_isdigit(str[i]))
		{
			digit = (str[i] - 48);
			num = 10 * num - digit;
		}
		if (str[i] == '-')
			sign = 1;
		i++;
	}
	return (sign * num);
}
