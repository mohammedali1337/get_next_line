/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:14:12 by mgarouj           #+#    #+#             */
/*   Updated: 2024/11/30 12:36:18 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read_to_str(int fd, char *str)
{
	ssize_t	bytes_read;
	char	*buff;
	char	*tmp;

	buff = malloc((size_t)BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (bytes_read != 0 && !ft_strchr(str, '\n'))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buff), free(str), NULL);
		buff[bytes_read] = '\0';
		tmp = ft_strjoin(str, buff);
		free(str);
		str = tmp;
	}
	free(buff);
	return (str);
}

static char	*ft_extract_line(char *str)
{
	size_t	i;
	char	*line;

	if (!*str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*ft_remove_line(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	new_str = malloc(ft_strlen(str) - i);
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	i++;
	j = 0;
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*static_str[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	static_str[fd] = ft_read_to_str(fd, static_str[fd]);
	if (!static_str[fd])
		return (NULL);
	line = ft_extract_line(static_str[fd]);
	static_str[fd] = ft_remove_line(static_str[fd]);
	return (line);
}
