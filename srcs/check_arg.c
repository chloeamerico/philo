/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:17:47 by camerico          #+#    #+#             */
/*   Updated: 2025/05/22 20:32:01 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *str)
{
	int		i;
	int		sign;
	long	number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	return (number * sign);
}

// on verifie que les arguments donnes en argv sont bien que 
//des entiers positifs
int	check_arg(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i <= argc - 1)
	{
		if (is_num(argv[i]) == 1 || is_limits(argv[i]) == 1)
			ft_exit_error("Invalid arguments.", NULL);
		i++;
	}
	return (0);
}

//check si c'est bien des numbres
int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

//check si le nb est entre 0 et INT_MAX
int	is_limits(char *str)
{
	long	nb;

	nb = ft_atol(str);
	if (nb <= 0 || nb > INT_MAX)
		return (1);
	return (0);
}
