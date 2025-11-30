/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:00:50 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/01 01:34:25 by keitotak         ###   ########.fr       */
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

#define IN 0
#define OUT 1
#define ZOOM 0.60

void	zoom(t_ctx *ctx, int sx, int sy, int inout)
{
	double	dx;
	double	dy;
	double	zx;
	double	zy;

	dx = (double)sx - 0.5 * SIZE;
	dy = (double)sy - 0.5 * SIZE;
	zx = ctx->c.zx + dx * ctx->c.scale;
	zy = ctx->c.zy + dy * ctx->c.scale;
	if (inout == IN)
		ctx->c.scale *= ZOOM;
	else
		ctx->c.scale /= ZOOM;
	ctx->c.zx = zx - dx * ctx->c.scale;
	ctx->c.zy = zy - dy * ctx->c.scale;
}

int	mouse_hook(int button, int sx, int sy, void *param)
{
	t_ctx	*ctx;

	printf("button:%d\tx:%d\ty:%d\n", button, sx, sy);
	ctx = (t_ctx *)param;
	if (button == 4)
	{
		zoom(ctx, sx, sy, IN);
		ctx->f.iter_max += 4;
	}
	if (button == 5)
	{
		zoom(ctx, sx, sy, OUT);
		ctx->f.iter_max -= 4;
	}
	render(ctx);
	return (0);
}
