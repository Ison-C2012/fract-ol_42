/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:58:26 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/30 21:55:16 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdbool.h>

int	is_number(char *str)
{
	int	dp;

	if (ft_issign(*str))
		str++;
	dp = 0;
	while (*str)
	{
		if (ft_isdigit(*str))
			;
		else if (*str == '.' && ft_isdigit(str[1]))
		{
			dp++;
			if (dp > 1)
				return (false);
		}
		else
			return (false);
		str++;
	}
	return (true);
}

size_t	getsize_dp(char *str)
{
	size_t	size;

	while (*str && *str != '.')
		str++;
	if (*str == '\0')
		return (0);
	else
		str++;
	size = 0;
	while (str[size])
		size++;
	return (size);
}

double	atod(char *str)
{
	int		sign;
	size_t	size_dp;
	char	*ba_dp;
	double	nb;

	sign = 1;
	if (*str == '-')
		sign = -1 * (*str++ == '-');
	size_dp = getsize_dp(str);
	ba_dp = ft_substr(str, 0, ft_strlen(str) - size_dp);
	if (ba_dp == NULL)
		failed_malloc();
	nb = (double)ft_atoi(ba_dp);
	free(ba_dp);
	if (size_dp)
	{
		ba_dp = ft_substr(str, ft_strlen(str) - size_dp, size_dp);
		if (ba_dp == NULL)
			failed_malloc();
		nb += (double)ft_atoi(ba_dp) / pow(10, size_dp);
		free(ba_dp);
	}
	return (nb * sign);
}

void	check_args(t_ctx *ctx, char **args, int count)
{
	int	check;

	check = 0;
	if (ft_strncmp("M", args[0], 2) == 0 && count == 1)
		ctx->f.type = MANDELBROT;
	else if (ft_strncmp("J", args[0], 2) == 0 && count == 3)
	{
		if (!is_number(args[1]))
			check = 1;
		if (!is_number(args[2]))
			check = 1;
		ctx->f.type = JULIA;
		ctx->f.ja = atod(args[1]);
		ctx->f.jb = atod(args[2]);
		if (ctx->f.ja > 2.0 || ctx->f.ja < -2.0)
			check = 1;
		if (ctx->f.jb > 2.0 || ctx->f.jb < -2.0)
			check = 1;
	}
	else
		check = 1;
	if (check)
		invalid_args();
}
