/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:10:42 by keitotak          #+#    #+#             */
/*   Updated: 2025/10/27 16:18:06 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_len(size_t s_len, unsigned int start, size_t len)
{
	if (len == 0)
		return (0);
	else if (start > s_len)
		return (0);
	else if (start + len > s_len)
		return (s_len - start);
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sb;
	size_t	sb_len;

	sb_len = get_len(ft_strlen(s), start, len);
	if (sb_len == 0)
		return (ft_calloc(1, sizeof(char)));
	sb = (char *)malloc((sb_len + 1) * sizeof(char));
	if (sb == NULL)
		return (NULL);
	ft_strlcpy(sb, s + start, sb_len + 1);
	return (sb);
}
