/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:36:44 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/28 14:52:55 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_circle(t_ctx *ctx)
{
	double	r;
	double	t;
	int		x;
	int		y;

	if (ctx->v.vx_max < ctx->v.vy_max)
		r = ctx->v.vx_max * 0.25;
	else
		r = ctx->v.vy_max * 0.25;
	t = 0;
	while (t < 2 * acos(-1))
	{
		x = virtual_to_screen_x(ctx->c, r * cos(t));
		y = virtual_to_screen_y(ctx->c, r * sin(t));
		put_pixel(ctx, x, y, 0x008B0000);
		t += 0.01;
	}
}
