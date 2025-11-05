/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:13:25 by algasnie          #+#    #+#             */
/*   Updated: 2025/11/05 10:26:07 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	**list;	
	t_list	*adr_node;

	//verifier si le fd est ok
	if (fd < 0)
		return (NULL);
	
	// creer la list si elle n'existe pas && la remplir
	if (!list)
	{
		list = malloc(sizeof(t_list *));
		if (!list)
			return (NULL);
		*list = ft_lstnew(fd);;
	}

	//fonction qui cherche si le fd est deja gerer
	adr_node = NULL;
	if (*list)
		adr_node = ft_lst_shr(list, fd);
	
	printf("Pas trouve 1 %i \n", *(list)->fd);

	if (adr_node == NULL)
		printf("Pas trouve 1 %p \n", *list);
	else
		printf("adr_node : %p	%p \n", adr_node, *list);
	printf("\n");


	
	printf("%p\n\n", adr_node);
	//fonction qui cherche le fd pour test
	adr_node = ft_lst_shr(list, fd);
	printf("%p\n\n", adr_node);

	if (adr_node == NULL)
		printf("Pas trouve 2 (fonction add pas fonct)\n");
	else
		printf("adr_node : %p \n", adr_node);
	printf("\n");
	
	//fonction qui ecrit dans un buffer @ buffer size
	//si \n ou \0 ou buffer size --> strjoin(data->line, buffer)
	char	*buffer;
	int		len_buffer;
	int		sz;
	char	*tmp;

	len_buffer = 1;
	buffer = malloc(sizeof(char) * (len_buffer + 1));
	

	
	adr_node->line = ft_strjoin("","");
	sz = 1;
	while(sz)
	{
		sz = read(fd, buffer, len_buffer);
		printf("\nsz :%d\n", sz);
		printf("buf: %s\n", buffer);
		tmp = adr_node->line;
		adr_node->line = ft_strjoin(tmp, buffer);
		printf("l[]: %s\n", adr_node->line);
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