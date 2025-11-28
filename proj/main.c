/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:36:39 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/28 23:32:14 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init(t_ctx *ctx)
{
	ctx->mlx = mlx_init();
	ctx->win = mlx_new_window(ctx->mlx, SIZE, SIZE, "keitotak's screen");
	ctx->i.img = mlx_new_image(ctx->mlx, SIZE, SIZE);
	ctx->i.addr = mlx_get_data_addr(ctx->i.img, &ctx->i.bpp, &ctx->i.size_len,
			&ctx->i.endian);
	ctx->c.cx = 0.0;
	ctx->c.cy = 0.0;
	ctx->c.scale = 0.01;
}

void	err_input(void)
{
	ft_printf("Invalid Input.\n");
	ft_printf("Usage\t\t: ./fractol <fractal's code>\n");
	ft_printf("\nfractal name\t: code\n");
	ft_printf("mandelbrot\t: 0\n");
	ft_printf("julia\t\t: 1 <value> <value>\n");
	ft_printf("sthelse\t\t: 2\n");
	ft_printf("\nExample:\n");
	ft_printf(" ./fractol 0\n");
	ft_printf(" ./fractol 1 -0.3 -0.63\n\n");
	exit(1);
}

#define FALSE 0

void	check_arg(int ac, char *av[])
{
	int	code;

	if (ac != 2 && ac != 4)
		err_input();
	/*if (ft_isnumber(av[1]) == FALSE)
		err_input();
	code = ft_atoi(av[1]);
	if (code < 0 || code > 2)
		err_input();
	if (ac == 2)
	{
		if (code == 1)
			err_input();
	}
	else
	{
		if (code != 1)
			err_input();
		get_value_for_julia();
	}
*/
}

int	main(int argc, char *argv[])
{
	t_ctx	ctx;

	check_arg(argc, argv);
	init(&ctx);
	render(&ctx);
	mlx_mouse_hook(ctx.win, mouse_hook, &ctx);
	mlx_key_hook(ctx.win, key_hook, &ctx);
	mlx_hook(ctx.win, DestroyNotify, StructureNotifyMask, window_close, &ctx);
	mlx_loop(ctx.mlx);
	return 0;
}
