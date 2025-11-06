/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 19:58:32 by algasnie          #+#    #+#             */
/*   Updated: 2025/11/06 11:29:44 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_fd(int fd, char *buffer, char *tmp)
{
	int		size_read;
	char	*tmp2;

	size_read = 1;
	while (!ft_strchr(tmp, '\n') && size_read > 0)
	{
		size_read = read(fd, buffer, BUFFER_SIZE);
		if (size_read == -1)
			return (NULL);
		buffer[size_read] = '\0';
		tmp2 = ft_strjoin(tmp, buffer);
		if (!tmp2)
			return (NULL);
	}
	return (tmp2);
}

static char	*ft_extract_line(char *tmp)
{
	char	*line;
	int		i;

	i = 0;
	if (!tmp || !tmp[0])
		return (NULL);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	line = ft_substr(tmp, 0, i + 1);
	return (line);
}

static char	*ft_update_tmp(char *tmp)
{
	char	*tmp2;
	int		i;

	i = 0;
	if (!tmp)
		return (NULL);
	if (!ft_strchr(tmp, '\n'))
	{
		free(tmp);
		return (NULL);
	}
	while (tmp[i] != '\n')
		i++;
	tmp2 = ft_substr(tmp, i + 1, ft_strlen(tmp));
	free(tmp);
	return (tmp2);
}

char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*tmp2;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!tmp)
		tmp = ft_strdup("");
	if (!tmp)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	tmp2 = ft_read_fd(fd, buffer, tmp);
	if (!tmp2)
	{
		free(tmp);
		free(buffer);
		return (NULL);
	}
	tmp = tmp2;
	line = ft_extract_line(tmp);
	tmp = ft_update_tmp(tmp);
	return (line);
}
