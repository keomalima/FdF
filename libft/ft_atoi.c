/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:30:19 by keomalima         #+#    #+#             */
/*   Updated: 2024/11/30 14:29:58 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_atoi(const char *str, int *error)
{
	int		sign;
	long	nb;

	nb = 0;
	sign = 1;
	while ((*(str) >= '\t' && *(str) <= '\r') || *(str) == ' ')
		str++;
	if (*(str) == '-' || *(str) == '+')
	{
		if (*(str) == '-')
			sign *= -1;
		str++;
	}
	while (*(str) >= '0' && *(str) <= '9')
	{
		if (nb > (LONG_MAX - (*(str) - '0')) / 10)
			if (sign == 1)
				return ((*error = -1), -1);
		nb = (nb * 10) + *(str) - '0';
		str++;
	}
	nb *= sign;
	if (nb < INT_MIN || nb > INT_MAX)
		return ((*error = -1), -1);
	return ((int)nb);
}
