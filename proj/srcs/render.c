/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:41:51 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/29 21:03:55 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pixel(t_ctx *ctx, int x, int y, unsigned int color)
{
	char	*p;

	if (x < 0 || x >= SIZE || y < 0 || y >=SIZE)
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

/*mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->i.img, 0, 0);*/

int	render(t_ctx *ctx)
{
	ctx->v.vx_min = ctx->c.cx - 0.5 * SIZE * ctx->c.scale;
	ctx->v.vy_min = ctx->c.cy - 0.5 * SIZE * ctx->c.scale;
	ctx->v.vx_max = ctx->c.cx + 0.5 * SIZE * ctx->c.scale;
	ctx->v.vy_max = ctx->c.cy + 0.5 * SIZE * ctx->c.scale;
	clear_with_color(ctx, 0x00000000);
	ctx->f.ja = -0.33;
	ctx->f.jb = -0.30;
	draw_fractal(ctx, calc_julia);
//	draw_fractal(ctx, calc_mandelbrot);
	return (0);
}
