/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:36:39 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/28 14:49:08 by keitotak         ###   ########.fr       */
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
	printf("%dn", keycode);
	return (0);
}

int	mouse_hook(int button,int x,int y,void *param)
{
	t_ctx	*ctx;

	printf("button:%d\tx:%d\ty:%d\n", button, x, y);
	ctx = (t_ctx *)param;
	if (button == 4)
		zoom(ctx, x, y, 1);
	if (button == 5)
		zoom(ctx, x, y, 0);
	render(ctx);
	return (0);
}

int	main(void)
{
	t_ctx	ctx;

	ctx.mlx = mlx_init();
	ctx.win = mlx_new_window(ctx.mlx, WIDTH, HEIGHT, "keitotak's screen");
	ctx.i.img = mlx_new_image(ctx.mlx, WIDTH, HEIGHT);
	ctx.i.addr = mlx_get_data_addr(ctx.i.img, &ctx.i.bpp, &ctx.i.size_len,
			&ctx.i.endian);
	ctx.c.cx = 0.0;
	ctx.c.cy = 0.0;
	ctx.c.scale = 0.01;
	render(&ctx);
	mlx_mouse_hook(ctx.win, mouse_hook, &ctx);
	mlx_key_hook(ctx.win, key_hook, &ctx);
	mlx_hook(ctx.win, DestroyNotify, StructureNotifyMask, window_close, &ctx);
	mlx_loop(ctx.mlx);
	return 0;
}
