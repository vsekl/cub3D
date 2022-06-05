/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:43:57 by vjose             #+#    #+#             */
/*   Updated: 2022/05/12 15:43:58 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_findline(char const *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	str_len;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		return (s1);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str_len = s1_len + s2_len;
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!str)
		return (NULL);
	ft_memmove(str, s1, s1_len);
	ft_memmove(str + s1_len, s2, s2_len);
	str[str_len] = '\0';
	free (s1);
	return (str);
}

static char	*ft_make_line(char const *str)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!str || !str[0])
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(*str) * (i + 1));
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

static char	*ft_save_str(char *str)
{
	char	*str_out;
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i] != '\n' && str[i] && str)
		i++;
	if (!str[i] || !str)
	{
		free (str);
		return (NULL);
	}
	str_out = (char *)malloc(sizeof(*str) * (ft_strlen(str) - i));
	if (!str_out)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		str_out[j++] = str[i++];
	str_out[j] = '\0';
	free (str);
	return (str_out);
}

int	get_next_line(int fd, char **line)
{
	static char	*str;
	char		*buffer;
	ssize_t		read_bytes;

	if (fd < 0 || fd > 255 || BUFFER_SIZE < 1)
		return (-1);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	read_bytes = 1;
	while (!ft_findline(str) && read_bytes)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free_buffer(read_bytes, buffer));
		buffer[read_bytes] = '\0';
		str = ft_strjoin_gnl(str, buffer);
	}
	*line = ft_make_line(str);
	str = ft_save_str(str);
	return (free_buffer(read_bytes, buffer));
}
