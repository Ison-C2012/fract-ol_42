/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:36:44 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/27 23:37:08 by keitotak         ###   ########.fr       */
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

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		size_len;
	int		endian;
	int		x;
	int		y;
	double	cx;
	double	cy;
	double	scale;
} t_vars;

void	put_pixel(t_vars *vars, int x, int y, unsigned int color)
{
	char	*p;

	if (x < 0 || x >= WIDTH || y < 0 || y >=HEIGHT)
		return ;
	p = vars->addr + y * vars->size_len + x * vars->bpp / 8;
	*(unsigned int *)p = color;
}

int	clear_with_color(t_vars vars, unsigned int color)
{
	char	*pnt;
	int		x;
	int		y;

	y = 0;
	while (y < HEIGHT)
	{
		pnt = vars.addr + y++ * vars.size_len;
		x = 0;
		while (x < WIDTH)
			*(unsigned int *)(pnt + x++ * vars.bpp / 8) = color;
	}
	return (0);
}

int	vertical_line(t_vars vars, int x, unsigned int color)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
		put_pixel(&vars, x, y++, color);
	return (0);
}

int	horizontal_line(t_vars vars, int y, unsigned int color)
{
	int		x;

	x = 0;
	while (x < WIDTH)
		put_pixel(&vars, x++, y, color);
	return (0);
}

int	render(t_vars vars)
{
	clear_with_color(vars, 0x00ffffff);
	vertical_line(vars, vars.x, 0x00000000);
	horizontal_line(vars, vars.y, 0x00000000);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
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

int	mouse_hook(int button,int x,int y,void *param)
{
	if (!(button == 4 || button == 5))
		return (1);
	printf("button:%d\tx:%d\ty:%d\t\n", button, x, y);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "keitotak's screen");
	vars.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bpp, &vars.size_len,
			&vars.endian);
	vars.x = WIDTH / 2;
	vars.y = HEIGHT / 2;
	vars.cx = 0.0;
	vars.cy = 0.0;
	vars.scale = 0.01;
	render(vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, window_close, &vars);
	mlx_loop(vars.mlx);
	return 0;
}
