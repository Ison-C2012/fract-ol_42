/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:36:44 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/27 20:16:29 by keitotak         ###   ########.fr       */
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

typedef struct s_cpxnbr
{
	double	x;
	double	y;
} t_cpxnbr;

void	put_pixel(t_idata *d, int x, int y, unsigned int color)
{
	int	bytes;

	bytes = d->bpp / 8;

	if (x < 0 || x >= WIDTH || y < 0 || y >=HEIGHT)
		return ;
	*(unsigned int *)(d->addr + y * d->size_len + x * bytes) = color;
}

int	render_julia(t_idata *d, double a, double b)
{
	t_cpxnbr	z;
	t_cpxnbr	z1;
	t_coo		c;
	int			count;

	z.x = 0;
	z.y = 0;
	c.cx = WIDTH / 2;
	c.cy = HEIGHT / 2;
	count = 0;
	while (1)
	{
		put_pixel(d, c.cx + 100 * z.x, c.cy + 100 * z.y, 0x00ff0000);
		if (count >= 1000000)
			break ;
		if (sqrt(pow(z.x, 2.0) + pow(z.y, 2.0)) > 2)
			break ;
		z1.x = pow(z.x, 2.0) - pow(z.y, 2.0) + a;
		z1.y = 2.0 * z.x * z.y + b;
		if (z1.x == z.x && z1.y == z.y)
			break ;
		z.x = z1.x;
		z.y = z1.y;
		count++;
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

int	main(void)
{
	t_vars	vars;
	t_idata	idata;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "keitotak's screen");
	idata.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	idata.addr = mlx_get_data_addr(idata.img, &idata.bpp,
			&idata.size_len, &idata.endian);
	clear_with_color(idata, 0x00000000);
	render_julia(&idata, -0.3, -0.63);
	mlx_put_image_to_window(vars.mlx, vars.win, idata.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, window_close, &vars);
	mlx_loop(vars.mlx);
	return 0;
}
