/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:39:37 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/29 21:30:16 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom(t_ctx *ctx, int x, int y, int inout)
{
	double	vx;
	double	vy;
	double	zoom;

	vx = ctx->c.cx + (x - 0.5 * WIDTH) * ctx->c.scale;
	vy = ctx->c.cy + (y - 0.5 * HEIGHT) * ctx->c.scale;
	zoom = 0.9;
	if (inout)
		ctx->c.scale *= zoom;
	else
		ctx->c.scale /= zoom;
	ctx->c.cx = vx - ((double)x - 0.5 * WIDTH) * ctx->c.scale;
	ctx->c.cy = vy - ((double)y - 0.5 * HEIGHT) * ctx->c.scale;
}

