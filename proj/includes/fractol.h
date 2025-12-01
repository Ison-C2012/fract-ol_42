/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:37:23 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/01 13:24:11 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <X11/X.h>
# include <mlx.h>

# include "../libft/includes/libft.h"
# include "../libft/includes/libft_bonus.h"
# include "../libft/includes/ft_printf.h"

# define MANDELBROT 0
# define JULIA 1
# define SIZE 700
# define ESC 0xff1b
# define INVALID_ARGS 0
# define INVALID_ARGS_FOR_JULIA 1

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_len;
	int		endian;
}	t_image;

typedef struct s_camera
{
	double	zx;
	double	zy;
	double	scale;
}	t_camera;

typedef struct s_screen
{
	int	x_min;
	int	x_max;
	int	y_min;
	int	y_max;
	int	x;
	int	y;
}	t_screen;

typedef struct s_gauss
{
	double	x_min;
	double	y_min;
	double	x_max;
	double	y_max;
	double	x;
	double	y;
	double	a;
	double	b;
	double	tmp;
}	t_gauss;

typedef struct s_fractal
{
	int		type;
	int		flag;
	int		iter_cnt;
	int		iter_max;
	double	ja;
	double	jb;
}	t_fractal;

typedef struct s_ctx
{
	void		*mlx;
	void		*win;
	t_image		i;
	t_camera	c;
	t_screen	s;
	t_gauss		z;
	t_fractal	f;
}	t_ctx;

void			check_args(t_ctx *ctx, char **args, int count);
void			invalid_args(int type);
void			error_exit(void);
void			init(t_ctx *ctx);
int				render(t_ctx *ctx);
int				draw_fractal(t_ctx *ctx, int (*f)(t_ctx *));
int				calc_mandelbrot(t_ctx *ctx);
int				calc_julia(t_ctx *ctx);
unsigned int	select_color(t_ctx *ctx);
void			put_pixel(t_ctx *ctx, unsigned int color);
int				mouse_hook(int button, int sx, int sy, void *param);
void			zoom(t_ctx *ctx, int sx, int sy, int inout);
int				key_hook(int keycode, t_ctx *ctx);
int				window_close(t_ctx *ctx);

#endif
