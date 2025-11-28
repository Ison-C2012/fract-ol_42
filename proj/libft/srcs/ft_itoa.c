/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 19:46:52 by keitotak          #+#    #+#             */
/*   Updated: 2025/11/09 14:00:04 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	cnt_dgt(long n)
{
	size_t	dgt;

	dgt = 0;
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		dgt++;
		n /= 10;
	}
	return (dgt);
}

static char	*get_str(char *str, long n)
{
	size_t	i;

	i = cnt_dgt(n) + (n < 0);
	str[i--] = '\0';
	if (n < 0)
	{
		n *= -1;
		str[0] = '-';
	}
	while (n > 0)
	{
		str[i--] = '0' + (n % 10);
		n /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;

	if (n == 0)
		return (ft_strdup("0"));
	len = cnt_dgt((long)n) + (n < 0);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str = get_str(str, (long)n);
	return (str);
}
