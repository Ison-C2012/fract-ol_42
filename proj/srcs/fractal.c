/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:20:44 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/30 19:30:34 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	screen_to_gauss(t_ctx *ctx, int x, int y)
{
	int	dx;
	int	dy;

	dx = x - SIZE / 2.0;
	dy = y - SIZE / 2.0;
	ctx->z.x = ctx->c.zx + dx * ctx->c.scale;
	ctx->z.y = ctx->c.zy + dy * ctx->c.scale;
}

int	calc_julia(t_ctx *ctx, int x, int y)
{
	int			k;

	screen_to_gauss(ctx, x, y);
	ctx->z.a = ctx->f.ja;
	ctx->z.b = ctx->f.jb;
	k = 0;
	while (k < ctx->f.iter)
	{
		ctx->z.tmp = pow(ctx->z.x, 2.0) - pow(ctx->z.y, 2.0) + ctx->z.a;
		ctx->z.y = 2 * ctx->z.x * ctx->z.y + ctx->z.b;
		if (ctx->z.x == ctx->z.tmp)
			break ;
		ctx->z.x = ctx->z.tmp;
		if (pow(ctx->z.x, 2.0) + pow(ctx->z.y, 2.0) > pow(2.0, 2.0))
			break ;
		k++;
	}
	return (k);
}

int	calc_mandelbrot(t_ctx *ctx, int x, int y)
{
	int			k;

	screen_to_gauss(ctx, x, y);
	ctx->z.a = ctx->z.x;
	ctx->z.b = ctx->z.y;
	ctx->z.x = 0;
	ctx->z.y = 0;
	k = 0;
	while (k < ctx->f.iter)
	{
		ctx->z.tmp = pow(ctx->z.x, 2.0) - pow(ctx->z.y, 2.0) + ctx->z.a;
		ctx->z.y = 2 * ctx->z.x * ctx->z.y + ctx->z.b;
		ctx->z.x = ctx->z.tmp;
		if (pow(ctx->z.x, 2.0) + pow(ctx->z.y, 2.0) > pow(2.0, 2.0))
			break ;
		k++;
	}
	return (k);
}

int	draw_fractal(t_ctx *ctx, int (*f)(t_ctx *, int, int))
{
	int				x;
	int				y;
	int				count;
	unsigned int	color;

	y = 0;
	while (y < SIZE)
	{
		x = 0;
		while (x < SIZE)
		{
			count = f(ctx, x, y);
			if (count == ctx->f.iter)
				color = 0x00000000;
			else if (count % 2 == 0)
				color = 0x008B1A1A;
			else
				color = 0x00FF0000;
			put_pixel(ctx, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->i.img, 0, 0);
	return (0);
}
