/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:13:25 by algasnie          #+#    #+#             */
/*   Updated: 2025/11/05 11:45:35 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_list	**list;	
	t_list			*adr_node;

	//verifier si le fd est ok
	if (fd < 0)
		return (NULL);
	
	// creer la list si elle n'existe pas && la set NULL
	if (!list)
	{
		list = malloc(sizeof(t_list *));
		if (!list)
			return (NULL);
	}

	//chercher ladresse du node fd && si elle nexiste pas la creer et ajouter a la fin	
	adr_node = ft_lst_shr(list, fd);
	if (adr_node == NULL)
	{
		adr_node = ft_lstnew(fd);
		ft_lstadd_back(list, adr_node);
	}
	
	//fonction qui ecrit dans un buffer @ buffer size
	//si \n ou \0 ou buffer size --> strjoin(data->line, buffer)
	char	*buffer;
	int		len_buffer;
	int		sz;
	char	*line_result;

	len_buffer = 10;
	buffer = malloc(sizeof(char) * (len_buffer + 1));
	buffer[len_buffer] = '\0';
	

	
	sz = read(fd, buffer, len_buffer);
	while(sz)
	{
		adr_node->line = ft_strjoin(adr_node->line, buffer);
		printf("sz:%d	\nbuffer:\n%s	\nline:\n%s\n\n", sz, buffer, adr_node->line);
		sz = read(fd, buffer, len_buffer);
	}

	
	return (adr_node->line);




}


int	main(void)
{
	int	fd;
	fd = open("test.txt", O_RDONLY);
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));

	return (0);
}