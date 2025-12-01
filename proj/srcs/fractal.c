/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:20:44 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/01 13:28:25 by keitotak         ###   ########.fr       */
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

int	calc_julia(t_ctx *ctx)
{
	screen_to_gauss(ctx, ctx->s.x, ctx->s.y);
	ctx->z.a = ctx->f.ja;
	ctx->z.b = ctx->f.jb;
	ctx->f.iter_cnt = 0;
	while (ctx->f.iter_cnt < ctx->f.iter_max)
	{
		ctx->z.tmp = pow(ctx->z.x, 2.0) - pow(ctx->z.y, 2.0) + ctx->z.a;
		ctx->z.y = 2 * ctx->z.x * ctx->z.y + ctx->z.b;
		ctx->z.x = ctx->z.tmp;
		if (pow(ctx->z.x, 2.0) + pow(ctx->z.y, 2.0) > pow(2.0, 2.0))
			return (false);
		ctx->f.iter_cnt++;
	}
	return (true);
}

int	calc_mandelbrot(t_ctx *ctx)
{
	screen_to_gauss(ctx, ctx->s.x, ctx->s.y);
	ctx->z.a = ctx->z.x;
	ctx->z.b = ctx->z.y;
	ctx->z.x = 0;
	ctx->z.y = 0;
	ctx->f.iter_cnt = 0;
	while (ctx->f.iter_cnt < ctx->f.iter_max)
	{
		ctx->z.tmp = pow(ctx->z.x, 2.0) - pow(ctx->z.y, 2.0) + ctx->z.a;
		ctx->z.y = 2 * ctx->z.x * ctx->z.y + ctx->z.b;
		ctx->z.x = ctx->z.tmp;
		if (pow(ctx->z.x, 2.0) + pow(ctx->z.y, 2.0) > pow(2.0, 2.0))
			return (false);
		ctx->f.iter_cnt++;
	}
	return (true);
}

int	draw_fractal(t_ctx *ctx, int (*f)(t_ctx *))
{
	ctx->s.y = ctx->s.y_min;
	while (ctx->s.y < ctx->s.y_max)
	{
		ctx->s.x = ctx->s.x_min;
		while (ctx->s.x < ctx->s.x_max)
		{
			if (f(ctx))
				ctx->f.flag = 1;
			put_pixel(ctx, select_color(ctx));
			ctx->s.x++;
		}
		ctx->s.y++;
		mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->i.img, 0, 0);
	}
	if (ctx->f.flag == 0)
		invalid_args(INVALID_ARGS_FOR_JULIA);
	return (0);
}
