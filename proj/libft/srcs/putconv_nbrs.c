/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putconv_nbrs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 13:24:05 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/11 20:39:11 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	putconv_int(int nbr)
{
	int		len;
	long	nb;

	putnbr(nbr);
	nb = (long)nbr;
	if (nb < 0)
		len = (int)count_digit(-nb, DEC);
	else
		len = (int)count_digit(nb, DEC);
	return (len + (nb < 0));
}

int	putconv_uint(unsigned int unbr)
{
	putnbr(unbr);
	return (count_digit(unbr, DEC));
}

int	putconv_uint_hex(unsigned int unbr, t_ccase lu)
{
	putnbr_hex(unbr, lu);
	return (count_digit(unbr, HEX));
}

int	putconv_ptr(uintptr_t ptr)
{
	if (ptr == 0)
	{
		ft_putstr_fd("(nil)", STDOUT);
		return (ft_strlen("(nil)"));
	}
	ft_putstr_fd("0x", STDOUT);
	putnbr_hex(ptr, lower);
	return (count_digit(ptr, HEX) + OX);
}
