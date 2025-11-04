/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:13:25 by algasnie          #+#    #+#             */
/*   Updated: 2025/11/04 16:17:30 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	**list;	
	int		num_node;
	t_list	*new_node;

	//verifier si le fd est ok
	if (fd < 0)
		return (NULL);
	
	// creer la list si elle n'existe pas && la remplir
	if (!list)
		list = malloc(sizeof(t_list *));

	//fonction qui cherche si le fd est deja gerer
	num_node = ft_lst_shr(list, fd);
	printf("num_node %d\n", num_node);
	if (num_node > 0)
		printf("ret %d\n", list[num_node]->fd);
	printf("\n");

	//si num_node = -1 ---> add_back
	
	if (num_node < 0)
	{
		new_node = malloc(sizeof(t_list));
		if (!new_node)
			return (NULL);
		new_node->fd = fd;
		ft_lstadd_back(list, new_node);
	}
	
	//fonction qui cherche le fd pour test
	num_node = ft_lst_shr(list, fd);
	printf("num_node %d\n", num_node);
	if (num_node > 0)
		printf("ret %d\n", list[num_node]->fd);
	printf("\n");
	
	//fonction qui ecrit dans un buffer @ buffer size
	//si \n ou \0 ou buffer size --> strjoin(data->line, buffer)
	char	*buffer;
	int		len_buffer;
	int		sz;

	len_buffer = 1;
	buffer = malloc(sizeof(char) * (len_buffer + 1));
	
	
	
	/*if (sz < 0)
		return (NULL);*/
	sz = read(fd, buffer, len_buffer);
	printf("buf: %s\n", buffer);
	list[num_node]->line = buffer;
	printf("l[]%s\n", list[num_node]->line);
	
	
	
	while(sz)
	{
		sz = read(fd, buffer, len_buffer);
		printf("\nsz :%d\n", sz);
		printf("buf: %s\n", buffer);
		ft_strjoin(list[num_node]->line, buffer);
		printf("l[]: %s\n", list[num_node]->line);
	}

	
	
	return (list[num_node]->line);




}


int	main(void)
{
	int	fd;
	fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));

	return (0);
}