/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:36:44 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/28 14:04:33 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <X11/X.h>
#include <mlx.h>

#define WIDTH 720
#define HEIGHT 480
#define ESC 0xff1b
#define COLOR 0x00FFFFFF
#define PI acos(-1)

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_len;
	int		endian;
} t_image;

typedef struct s_camera
{
	double	cx;
	double	cy;
	double	scale;
} t_camera;

typedef struct s_virtual
{
	double	vx_min;
	double	vy_min;
	double	vx_max;
	double	vy_max;
} t_virtual;

typedef struct s_ctx
{
	void		*mlx;
	void		*win;
	t_image		i;
	t_camera	c;
	t_virtual	v;
} t_ctx;

void	put_pixel(t_ctx *ctx, int x, int y, unsigned int color)
{
	char	*p;

	if (x < 0 || x >= WIDTH || y < 0 || y >=HEIGHT)
		return ;
	p = ctx->i.addr + y * ctx->i.size_len + x * ctx->i.bpp / 8;
	*(unsigned int *)p = color;
}

int	virtual_to_screen_x(t_camera c, double vx)
{
	return (lround((vx - c.cx) / c.scale) + WIDTH / 2);
}

int	virtual_to_screen_y(t_camera c, double vy)
{
	return (lround((vy - c.cy) / c.scale) + WIDTH / 2);
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

int	render(t_ctx *ctx)
{
	clear_with_color(ctx, 0x00ffffff);

	ctx->v.vx_min = ctx->c.cx - 0.5 * WIDTH * ctx->c.scale;
	ctx->v.vy_min = ctx->c.cy - 0.5 * HEIGHT * ctx->c.scale;
	ctx->v.vx_max = ctx->c.cx + 0.5 * WIDTH * ctx->c.scale;
	ctx->v.vy_max = ctx->c.cy + 0.5 * HEIGHT * ctx->c.scale;

	draw_grid(ctx);
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->i.img, 0, 0);
}

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

void	zoom(t_ctx *ctx, int x, int y, int inout)
{
	double	vx;
	double	vy;

	vx = ctx->c.cx + (x - 0.5 * WIDTH) * ctx->c.scale;
	vy = ctx->c.cy + (y - 0.5 * HEIGHT) * ctx->c.scale;
	if (inout)
		ctx->c.scale *= 0.8;
	else
		ctx->c.scale /= 0.8;
	ctx->c.cx = vx;
	ctx->c.cy = vy;
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
