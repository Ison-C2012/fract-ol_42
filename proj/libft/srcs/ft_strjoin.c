/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:19:19 by keitotak          #+#    #+#             */
/*   Updated: 2025/10/27 16:19:07 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*j;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	j = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (j == NULL)
		return (NULL);
	ft_strlcpy(j, s1, s1_len + 1);
	ft_strlcat(j, s2, s1_len + s2_len + 1);
	return (j);
}
