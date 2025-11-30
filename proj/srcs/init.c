/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:58:11 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/30 21:29:16 by keitotak         ###   ########.fr       */
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
	ctx->c.zx = 0.0;
	ctx->c.zy = 0.0;
	ctx->c.scale = 4.0 / SIZE;
	ctx->f.iter = 40;
}
