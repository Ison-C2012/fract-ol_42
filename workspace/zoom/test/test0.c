/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:36:44 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/27 21:47:53 by keitotak         ###   ########.fr       */
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

typedef struct s_idata
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_len;
	int		endian;
} t_idata;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_idata	d;
} t_vars;

typedef struct s_coo
{
	int		cx;
	int		cy;
	int		x;
	int		y;
	int		r;
	double	t;
} t_coo;

void	put_pixel(t_idata *d, int x, int y, unsigned int color)
{
	int	bytes;

	bytes = d->bpp / 8;

	if (x < 0 || x >= WIDTH || y < 0 || y >=HEIGHT)
		return ;
	*(unsigned int *)(d->addr + y * d->size_len + x * bytes) = color;
}

void	area_circle(t_idata *d, t_coo *c, unsigned int color)
{
	int	r;

	r = 0;
	while (r < c->r)
	{
		c->x = c->cx + (int)lround(r * cos(c->t));
		c->y = c->cy + (int)lround(r * sin(c->t));
		put_pixel(d, c->x, c->y, color);
		r++;
	}
}

void	line_circle(t_idata *d, t_coo *c, unsigned int color)
{
	c->x = c->cx + (int)lround(c->r * cos(c->t));
	c->y = c->cy + (int)lround(c->r * sin(c->t));
	put_pixel(d, c->x, c->y, color);
}

int	render_circle(t_idata idata, unsigned int color, int fill)
{
	t_coo	c;

	c.cx = WIDTH / 2;
	c.cy = HEIGHT / 2;
	c.r = HEIGHT / 4;
	c.t = 0;
	while (c.t < 2 * PI)
	{
		if (fill)
			area_circle(&idata, &c, color);
		else
			line_circle(&idata, &c, color);
		c.t += 1.0 / c.r;
	}
	return (0);
}

int	clear_with_color(t_idata idata, unsigned int color)
{
	char	*pnt;
	size_t	x;
	size_t	y;
	int		bypp;

	bypp = idata.bpp / 8;
	y = 0;
	while (y < HEIGHT)
	{
		pnt = idata.addr + y++ * idata.size_len;
		x = 0;
		while (x < WIDTH)
			*(unsigned int *)(pnt + x++ * bypp) = color;
	}
	return (0);
}

int	window_close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESC)
		window_close(vars);
	printf("%d\n", keycode);
	return (0);
}

int	zoom(t_vars *vars, int button, int x, int y)
{
	return (0);
}

int	mouse_hook(int button,int x,int y,void *param)
{
	if (button == 4 || button == 5)
		zoom((t_vars *)param, button, x, y);
	printf("button:%d\tx:%d\ty:%d\t\n", button, x, y);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "keitotak's screen");
	vars.d.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.d.addr = mlx_get_data_addr(vars.d.img, &vars.d.bpp,
			&vars.d.size_len, &vars.d.endian);
	clear_with_color(vars.d, 0x00FFFFFF);
	render_circle(vars.d, 0x000000FF, 1);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.d.img, 0, 0);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, window_close, &vars);
	mlx_loop(vars.mlx);
	return 0;
}
