/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:13:25 by algasnie          #+#    #+#             */
/*   Updated: 2025/11/05 13:16:09 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_list	**list;	
	t_list			*adr_node;

	if (fd < 0)
		return (NULL);
	
	if (!list) //create list if doesn't exist
	{
		list = malloc(sizeof(t_list *));
		if (!list)
			return (NULL);
	}

	adr_node = ft_lst_shr(list, fd); //search if this fd is already in
	if (adr_node == NULL)
		adr_node = ft_createlst_add_back(list, fd); //create node @fd and add back of the list

	int		sz;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	sz = read(fd, buffer, BUFFER_SIZE);

	//char	*tmp;
	
	
	
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