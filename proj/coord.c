/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:46:18 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/28 14:46:31 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	virtual_to_screen_x(t_camera c, double vx)
{
	return (lround((vx - c.cx) / c.scale) + SIZE / 2);
}

int	virtual_to_screen_y(t_camera c, double vy)
{
	return (lround((vy - c.cy) / c.scale) + SIZE / 2);
}
