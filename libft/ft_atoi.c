/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:33:06 by vicperri          #+#    #+#             */
/*   Updated: 2025/05/29 12:18:11 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *nptr)
{
	size_t			i;
	int				sign;
	unsigned long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign *= -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (((nb * 10) + (nptr[i] - '0')) > LONG_LONG_INT && sign == 1)
			return (-1);
		else if (((nb * 10) + (nptr[i] - '0')) > LONG_LONG_INT
			&& sign == -1)
			return (-1);
		nb = nb * 10 + (nptr[i++] - '0');
	}
	return (nb * sign);
}
