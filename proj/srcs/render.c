/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:41:51 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/30 21:29:02 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pixel(t_ctx *ctx, int x, int y, unsigned int color)
{
	char	*p;

	if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
		return ;
	p = ctx->i.addr + y * ctx->i.size_len + x * ctx->i.bpp / 8;
	*(unsigned int *)p = color;
}

int	clear_with_color(t_ctx *ctx, unsigned int color)
{
	int		x;
	int		y;

	y = 0;
	while (y < SIZE)
	{
		x = 0;
		while (x < SIZE)
			put_pixel(ctx, x++, y, color);
		y++;
	}
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->i.img, 0, 0);
	return (0);
}

int	render(t_ctx *ctx)
{
	mlx_clear_window(ctx->mlx, ctx->win);
	ctx->z.x_min = ctx->c.zx - 0.5 * SIZE * ctx->c.scale;
	ctx->z.x_max = ctx->c.zx + 0.5 * SIZE * ctx->c.scale;
	ctx->z.y_min = ctx->c.zy - 0.5 * SIZE * ctx->c.scale;
	ctx->z.y_max = ctx->c.zy + 0.5 * SIZE * ctx->c.scale;
	if (ctx->f.type == MANDELBROT)
		draw_fractal(ctx, calc_mandelbrot);
	if (ctx->f.type == JULIA)
		draw_fractal(ctx, calc_julia);
	return (0);
}
