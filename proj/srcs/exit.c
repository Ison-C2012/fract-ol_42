/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:23:15 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/30 21:52:45 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//#define MSG_INVARGS "invalid arguments."
#define MSG_FAILMLC "failed memory allocation."

/* print_fractal_options:
*	Prints an explanation of the fractal options that can be specified
*	at program launch.
*/
void	print_fractal_options(void)
{
	ft_putendl_fd("+=================  Available Fractals  =================+", 1);
	ft_putendl_fd("Select fractal you want to view.", 1);
	ft_putendl_fd("\tM - Mandelbrot", 1);
	ft_putendl_fd("\tJ - Julia", 1);
	ft_putendl_fd("\e[32mUsage example:\t./fractol <type>\n\t\t./fractol M\e[0m", 1);
	ft_putstr_fd("\nFor Julia, you may specify starting values for the ini-\n", 1);
	ft_putstr_fd("tial fractal shape. Values must be between -2.0 and 2.0.\n", 1);
	ft_putendl_fd("", 1);
	ft_putendl_fd("\e[32mUsage example:\t./fractol J\n\t\t./fractol J 0.285 0.01\e[0m\n", 1);
}

void	invalid_args(void)
{
	ft_putendl_fd("\n+========================================================+", 1);
	ft_putendl_fd("|                       FRACT'OL                         |", 1);
	ft_putendl_fd("+========================================================+\n", 1);
	print_fractal_options();
	exit(1);
}

void	failed_malloc(void)
{
	ft_putendl_fd(MSG_FAILMLC, 2);
	exit(1);
}

