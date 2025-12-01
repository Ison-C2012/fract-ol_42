/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:41:51 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/01 13:31:06 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pixel(t_ctx *ctx, unsigned int color)
{
	char	*p;

	p = ctx->i.addr + ctx->s.y * ctx->i.size_len + ctx->s.x * ctx->i.bpp / 8;
	*(unsigned int *)p = color;
}

unsigned int	select_color(t_ctx *ctx)
{
	if (ctx->f.iter_cnt == ctx->f.iter_max)
		return (0x00000000);
	else if (ctx->f.iter_cnt % 4 == 0)
		return (0x00330000);
	else if (ctx->f.iter_cnt % 4 == 1)
		return (0x00660000);
	else if (ctx->f.iter_cnt % 4 == 2)
		return (0x00990000);
	else
		return (0x00FF0000);
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
