/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:50:47 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/28 14:50:59 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_vline(t_ctx *ctx, int x, unsigned int color)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
		put_pixel(ctx, x, y++, color);
}

void	draw_hline(t_ctx *ctx, int y, unsigned int color)
{
	int	x;

	x = 0;
	while (x < WIDTH)
		put_pixel(ctx, x++, y, color);
}

void	draw_grid(t_ctx *ctx)
{
	int	ix;
	int	iy;

	ix = floor(ctx->v.vx_min);
	while (ix < ceil(ctx->v.vx_max))
	{
		draw_vline(ctx, virtual_to_screen_x(ctx->c, (double)ix), 0x00808080);
		ix++;
	}
	iy = floor(ctx->v.vy_min);
	while (iy < ceil(ctx->v.vy_max))
	{
		draw_hline(ctx, virtual_to_screen_y(ctx->c, (double)iy), 0x00808080);
		iy++;
	}
}
