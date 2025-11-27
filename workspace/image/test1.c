/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:36:44 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/27 15:01:33 by keitotak         ###   ########.fr       */
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
} t_vars;

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

void	put_pixel(t_idata *d, int x, int y, unsigned int color)
{
	int	bytes;

	bytes = d->bpp / 8;

	if (x < 0 || x >= WIDTH || y < 0 || y >=HEIGHT)
		return ;
	*(unsigned int *)(d->addr + y * d->size_len + x * bytes) = color;
}

#define PI acos(-1)

typedef struct s_coo
{
	int	cx;
	int	cy;
} t_coo;

int	render_circle(t_idata idata, unsigned int color)
{
	char	*pnt;
	t_coo	c;
	double	r;
	double	t;
	int		x;
	int		y;

	c.cx = WIDTH / 2;
	c.cy = HEIGHT / 2;
	r = HEIGHT / 4;
	t = 0;
	while (t < 2 * PI)
	{
		x = c.cx + (int)lround(r * cos(t)); 
		y = c.cy + (int)lround(r * sin(t));
		put_pixel(&idata, x, y, color);
		t += 1.0 / r;
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

int	main(void)
{
	t_vars	vars;
	t_idata	idata;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "keitotak's screen");
	idata.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	idata.addr = mlx_get_data_addr(idata.img, &idata.bpp,
			&idata.size_len, &idata.endian);
	printf("bpp=%d, size_len=%d, endian=%d\n", idata.bpp,
			idata.size_len, idata.endian);
	clear_with_color(idata, 0x00FFFFFF);
	render_circle(idata, 0x000000FF);
	mlx_put_image_to_window(vars.mlx, vars.win, idata.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, window_close, &vars);
	mlx_loop(vars.mlx);
	return 0;
}
