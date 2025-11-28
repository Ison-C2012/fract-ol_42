/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:37:23 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/28 15:00:03 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

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

void	zoom(t_ctx *ctx, int x, int y, int inout);
int		render(t_ctx *ctx);
int		clear_with_color(t_ctx *ctx, unsigned int color);
void	put_pixel(t_ctx *ctx, int x, int y, unsigned int color);
int		virtual_to_screen_x(t_camera c, double vx);
int		virtual_to_screen_y(t_camera c, double vy);
void	draw_grid(t_ctx *ctx);
void	draw_circle(t_ctx *ctx);

#endif
