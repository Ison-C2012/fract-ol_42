/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:00:50 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/28 18:01:47 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	window_close(t_ctx *ctx)
{
	mlx_destroy_window(ctx->mlx, ctx->win);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_ctx *ctx)
{
	if (keycode == ESC)
		window_close(ctx);
	return (0);
}

void	zoom(t_ctx *ctx, int x, int y, int inout)
{
	double	vx;
	double	vy;
	double	zoom;

	vx = ctx->c.cx + (x - 0.5 * SIZE) * ctx->c.scale;
	vy = ctx->c.cy + (y - 0.5 * SIZE) * ctx->c.scale;
	zoom = 0.9;
	if (inout)
		ctx->c.scale *= zoom;
	else
		ctx->c.scale /= zoom;
	ctx->c.cx = vx - ((double)x - 0.5 * SIZE) * ctx->c.scale;
	ctx->c.cy = vy - ((double)y - 0.5 * SIZE) * ctx->c.scale;
}

int	mouse_hook(int button,int x,int y,void *param)
{
	t_ctx	*ctx;

//	printf("button:%d\tx:%d\ty:%d\n", button, x, y);
	ctx = (t_ctx *)param;
	if (button == 4)
		zoom(ctx, x, y, 1);
	if (button == 5)
		zoom(ctx, x, y, 0);
	render(ctx);
	return (0);
}
