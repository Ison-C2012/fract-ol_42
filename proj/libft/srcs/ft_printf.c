/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:25:41 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/10 17:56:04 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	putconv(va_list *ptr_ap, char c)
{
	if (c == '%')
		return (putconv_char('%'));
	if (c == 'c')
		return (putconv_char(va_arg(*ptr_ap, int)));
	if (c == 's')
		return (putconv_str(va_arg(*ptr_ap, char *)));
	if (c == 'p')
		return (putconv_ptr(va_arg(*ptr_ap, uintptr_t)));
	if (c == 'd' || c == 'i')
		return (putconv_int(va_arg(*ptr_ap, int)));
	if (c == 'u')
		return (putconv_uint(va_arg(*ptr_ap, unsigned int)));
	if (c == 'x')
		return (putconv_uint_hex(va_arg(*ptr_ap, unsigned int), lower));
	if (c == 'X')
		return (putconv_uint_hex(va_arg(*ptr_ap, unsigned int), upper));
	return (0);
}

int	convert_print(va_list *ptr_ap, char *fmt)
{
	int		len;
	size_t	i;

	len = 0;
	i = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%' && fmt[i + 1] && ft_strchr(CONV, fmt[i + 1]))
		{
			len += putconv(ptr_ap, fmt[i + 1]);
			i += 2;
		}
		else if (fmt[i] == '%' && fmt[i + 1] == '\0')
			return (-1);
		else
		{
			ft_putchar_fd(fmt[i], STDOUT);
			len += 1;
			i += 1;
		}
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	char	*fmt;
	va_list	ap;
	int		len;

	if (format == NULL)
		return (-1);
	fmt = (char *)format;
	if (ft_strchr(format, '%') == NULL)
	{
		ft_putstr_fd(fmt, STDOUT);
		return (ft_strlen(fmt));
	}
	va_start(ap, format);
	len = convert_print(&ap, fmt);
	va_end(ap);
	return (len);
}
