/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:38:23 by mgarouj           #+#    #+#             */
/*   Updated: 2024/11/30 14:24:33 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

static char	*join_str(char *str, char const *s1, char const *s2)
{
	size_t	x;
	size_t	y;
	size_t	len_1;
	size_t	len_2;

	x = 0;
	y = 0;
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	while (x < len_1)
	{
		str[x] = s1[x];
		x++;
	}
	while (y < len_2)
	{
		str[x + y] = s2[y];
		y++;
	}
	str[x + y] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_1;
	size_t	len_2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	str = (char *)malloc(len_1 + len_2 + 1);
	if (!str)
		return (NULL);
	return (join_str(str, s1, s2));
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dst;
	size_t	i;

	len = ft_strlen(s1);
	dst = malloc(len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
