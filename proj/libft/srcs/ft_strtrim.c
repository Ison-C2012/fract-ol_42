/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:43:16 by keitotak          #+#    #+#             */
/*   Updated: 2025/10/26 19:37:09 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	bgn;
	size_t	end;

	bgn = 0;
	while (s1[bgn] && ft_strchr(set, s1[bgn]))
		bgn++;
	end = ft_strlen(s1);
	while (end > bgn && ft_strchr(set, s1[end]))
		end--;
	return (ft_substr(s1, bgn, end - bgn + 1));
}
