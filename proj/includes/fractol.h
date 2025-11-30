/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:37:23 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/30 21:29:53 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <X11/X.h>
#include <mlx.h>

#include "../libft/includes/ft_printf.h"
#include "../libft/includes/libft.h"

//#define WIDTH 720
//#define HEIGHT 480

#define MANDELBROT 0
#define JULIA 1
#define SIZE 700
#define ESC 0xff1b
#define COLOR 0x00FFFFFF
#define PI acos(-1)
#define ITER_MAX 100

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
	double	zx;
	double	zy;
	double	scale;
} t_camera;

typedef struct s_screen
{
	int	x;
	int	y;
	int	x_max;
	int	x_min;
	int	y_max;
	int	y_min;
} t_screen;

typedef struct s_gauss
{
	double	x;
	double	y;
	double	x_min;
	double	y_min;
	double	x_max;
	double	y_max;
	double	a;
	double	b;
	double	tmp;
} t_gauss;

typedef struct s_fractal
{
	int		type;
	int		iter;
	double	ja;
	double	jb;
} t_fractal;

typedef struct s_ctx
{
	void		*mlx;
	void		*win;
	t_image		i;
	t_camera	c;
	t_screen	s;
	t_gauss		z;
	t_fractal	f;
} t_ctx;

void	check_args(t_ctx *ctx, char **args, int count);
void	invalid_args(void);
void	failed_malloc(void);
void	init(t_ctx *ctx);
int		render(t_ctx *ctx);
int		clear_with_color(t_ctx *ctx, unsigned int color);
int		draw_fractal(t_ctx *ctx, int (*f)(t_ctx *, int, int));
int		calc_julia(t_ctx *ctx, int x, int y);
int		calc_mandelbrot(t_ctx *ctx, int x, int y);
void	put_pixel(t_ctx *ctx, int x, int y, unsigned int color);
int		mouse_hook(int button,int x,int y,void *param);
void	zoom(t_ctx *ctx, int x, int y, int inout);
int		key_hook(int keycode, t_ctx *ctx);
int		window_close(t_ctx *ctx);

#endif
