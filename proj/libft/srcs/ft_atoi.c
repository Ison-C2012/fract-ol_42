/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 00:53:36 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/30 21:06:40 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	check(long nb, int sg, char c)
{
	int	x;

	x = c - '0';
	if (sg >= 0)
	{
		if (nb > LONG_MAX / 10)
			return (LONG_MAX);
		if (nb * 10 > LONG_MAX - x * sg)
			return (LONG_MAX);
	}
	else
	{
		if (nb < LONG_MIN / 10)
			return (LONG_MIN);
		if (nb * 10 < LONG_MIN - x * sg)
			return (LONG_MIN);
	}
	return (nb * 10 + x * sg);
}

int	ft_atoi(const char *nptr)
{
	long	nb;
	int		sg;

	while (ft_isspace(*nptr))
		nptr++;
	sg = 1;
	if (ft_issign(*nptr))
	{
		if (*nptr == '-')
			sg *= -1;
		nptr += 1;
	}
	nb = 0;
	while (ft_isdigit(*nptr))
	{
		nb = check(nb, sg, *nptr);
		if (nb == LONG_MAX || nb == LONG_MIN)
			return ((int)nb);
		nptr++;
	}
	return ((int)nb);
}
