/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:36:39 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/30 21:30:06 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_ctx	ctx;

	if (argc < 2 || argc > 4)
		invalid_args();
	check_args(&ctx, &argv[1], argc - 1);
	init(&ctx);
	render(&ctx);
	mlx_mouse_hook(ctx.win, mouse_hook, &ctx);
	mlx_key_hook(ctx.win, key_hook, &ctx);
	mlx_hook(ctx.win, DestroyNotify, StructureNotifyMask, window_close, &ctx);
	mlx_loop(ctx.mlx);
	return (0);
}
