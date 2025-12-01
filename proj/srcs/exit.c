/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:23:15 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/01 13:38:41 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	error_exit(void)
{
	ft_putendl_fd("\e[31m+===============  ERROR OCCURED  ===============+", 2);
	ft_putendl_fd("Exited program.\e[0m", 2);
	exit(EXIT_FAILURE);
}

void	print_fractal_options(void)
{
	ft_putendl_fd("+==============  Available Fractals  ==============+", 1);
	ft_putendl_fd("Select fractal you want to view.", 1);
	ft_putendl_fd("\tM - Mandelbrot", 1);
	ft_putendl_fd("\tJ - Julia", 1);
	ft_putendl_fd("\e[32mUsage example:\t./fractol <type>", 1);
	ft_putendl_fd("\t\t./fractol M\e[0m", 1);
	ft_putstr_fd("\nFor Julia, you may specify starting values for the\n", 1);
	ft_putstr_fd("initial fractal shape. Values must be between\n", 1);
	ft_putstr_fd("-2.0 and 2.0.\n", 1);
	ft_putendl_fd("", 1);
	ft_putendl_fd("\e[32mUsage example:\t./fractol J <value> <value>", 1);
	ft_putendl_fd("\t\t./fractol J 0.285 0.01\e[0m\n", 1);
}

void	print_fractal_for_julia(void)
{
	ft_putendl_fd("+================= Julia Fractal  =================+", 1);
	ft_putstr_fd("\nFor Julia, you may specify starting values for the\n", 1);
	ft_putstr_fd("initial fractal shape. Values must be between\n", 1);
	ft_putstr_fd("-2.0 and 2.0.\n", 1);
	ft_putstr_fd("\nHowever, there are some invalid values even though \n", 1);
	ft_putstr_fd("they're between -2.0 and 2.0.\n", 1);
	ft_putstr_fd("Let's try to search valid values for julia!\n", 1);
	ft_putendl_fd("", 1);
	ft_putendl_fd("\e[32mUsage example:\t./fractol J <value> <value>", 1);
	ft_putendl_fd("\t\t./fractol J -0.54 0.54", 1);
	ft_putendl_fd("\t\t./fractol J 0.355 0.355", 1);
	ft_putendl_fd("\t\t./fractol J -0.4 -0.59", 1);
	ft_putendl_fd("\t\t./fractol J 0.34 -0.05", 1);
	ft_putendl_fd("\t\t./fractol J 0.355534 -0.337292\e[0m\n", 1);
}

void	invalid_args(int type)
{
	ft_putendl_fd("\n+==================================================+", 1);
	ft_putendl_fd("|                    FRACT'OL                      |", 1);
	ft_putendl_fd("+==================================================+\n", 1);
	if (type == INVALID_ARGS)
		print_fractal_options();
	if (type == INVALID_ARGS_FOR_JULIA)
		print_fractal_for_julia();
	exit(EXIT_SUCCESS);
}
