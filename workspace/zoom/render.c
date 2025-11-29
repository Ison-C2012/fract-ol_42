/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:41:51 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/29 20:40:49 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pixel(t_ctx *ctx, int x, int y, unsigned int color)
{
	char	*p;

	if (x < 0 || x >= WIDTH || y < 0 || y >=HEIGHT)
		return ;
	p = ctx->i.addr + y * ctx->i.size_len + x * ctx->i.bpp / 8;
	*(unsigned int *)p = color;
}

int	clear_with_color(t_ctx *ctx, unsigned int color)
{
	int		x;
	int		y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
			put_pixel(ctx, x++, y, color);
		y++;
	}
	return (0);
}


int	render(t_ctx *ctx)
{
	clear_with_color(ctx, 0x00ffffff);

	ctx->v.vx_min = ctx->c.cx - 0.5 * WIDTH * ctx->c.scale;
	ctx->v.vy_min = ctx->c.cy - 0.5 * HEIGHT * ctx->c.scale;
	ctx->v.vx_max = ctx->c.cx + 0.5 * WIDTH * ctx->c.scale;
	ctx->v.vy_max = ctx->c.cy + 0.5 * HEIGHT * ctx->c.scale;

	draw_grid(ctx);
	draw_circle(ctx);
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->i.img, 0, 0);
	return (0);
}
