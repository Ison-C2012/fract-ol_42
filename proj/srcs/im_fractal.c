/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   im_fractal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:20:44 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/29 21:14:27 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	calc_julia(t_ctx *ctx, int ix, int iy)
{
	t_complex	z;
	int			k;

	z.a = ctx->f.ja;
	z.b = ctx->f.jb;
	z.x = (ix - (ctx->v.vx_max - ctx->v.vx_min) / 2.0) * (4.0 / (ctx->v.vx_max - ctx->v.vx_min));
	z.y = (iy - (ctx->v.vy_max - ctx->v.vy_min) / 2.0) * (4.0 / (ctx->v.vy_max - ctx->v.vy_min));
	k = 0;
	while (k < ITER_MAX)
	{
		z.tmp = pow(z.x, 2.0) - pow(z.y, 2.0) + z.a;
		z.y = 2 * z.x * z.y + z.b;
		if (z.x == z.tmp)
			break ;
		z.x = z.tmp;
		if (pow(z.x, 2.0) + pow(z.y, 2.0) > pow(2.0, 2.0))
			break ;
		k++;
	}
	return (k);
}

int	calc_mandelbrot(t_ctx *ctx, int ix, int iy)
{
	t_complex	z;
	int			k;

	(void)ctx;
	z.a = (ix - (ctx->v.vx_max - ctx->v.vx_min) / 2.0) * (4.0 / (ctx->v.vx_max - ctx->v.vx_min));
	z.b = (iy - (ctx->v.vy_max - ctx->v.vy_min) / 2.0) * (4.0 / (ctx->v.vy_max - ctx->v.vy_min));
	z.x = 0;
	z.y = 0;
	k = 0;
	while (k < ITER_MAX)
	{
		z.tmp = pow(z.x, 2.0) - pow(z.y, 2.0) + z.a;
		z.y = 2 * z.x * z.y + z.b;
		z.x = z.tmp;
		if (pow(z.x, 2.0) + pow(z.y, 2.0) > pow(2.0, 2.0))
			break ;
		k++;
	}
	return (k);
}

int	draw_fractal(t_ctx *ctx, int (*f)(t_ctx *, int, int))
{
	int	ix;
	int	iy;
	int	res;
	unsigned int	color;

	iy = ctx->v.vy_min;
	while (iy < ctx->v.vy_max)
	{
		ix = ctx->v.vx_min;
		while (ix < ctx->v.vx_max)
		{
			res = f(ctx, ix, iy);
			if (res == ITER_MAX)
				color = 0x00000000;
			else if (res % 2 == 0)
				color = 0x008B1A1A;
			else
				color = 0x00FF0000;
			put_pixel(ctx, ix, iy, color);
			ix++;
		}
		iy++;
	}
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->i.img, 0, 0);
	return (0);
}
