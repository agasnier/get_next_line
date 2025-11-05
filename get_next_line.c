/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:13:25 by algasnie          #+#    #+#             */
/*   Updated: 2025/11/05 11:15:09 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	char	*tmp;

	len_buffer = 1;
	buffer = malloc(sizeof(char) * (len_buffer + 1));
	

	
	sz = read(fd, buffer, len_buffer);
	while(sz)
	{
		tmp = adr_node->line;
		adr_node->line = ft_strjoin(tmp, buffer);
		sz = read(fd, buffer, len_buffer);
	}

	
	
	return (adr_node->line);




}


int	main(void)
{
	int	fd;
	fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));

	return (0);
}