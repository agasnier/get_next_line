/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:13:25 by algasnie          #+#    #+#             */
/*   Updated: 2025/11/05 14:21:42 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*ft_lst_shr(t_list **lst, int fd)
{
	t_list	*current;

	if (!lst || !*lst)
		return (NULL);
	current = *lst;
	while (current->next)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	if (current->fd == fd)
			return (current);
	return (NULL);
}

t_list	*ft_createlst_add_back(t_list **lst, int fd)
{
	t_list	*new_node;
	t_list	*last;

	if (!lst)
		return (NULL);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->line = NULL;
	new_node->next = NULL;
	if (*lst == NULL)
	{
		*lst = new_node;
		return (new_node);
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	return (new_node);
}

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
	char	*tmp;
	char	*result;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	
	sz = 1;
	while (sz && !ft_strchr(adr_node->line, '\n'))
	{
		sz = read(fd, buffer, BUFFER_SIZE);
		if (!adr_node->line)
			adr_node->line = ft_strjoin("", buffer);
		else
		{
			tmp = adr_node->line;
			adr_node->line = ft_strjoin(tmp, buffer);
			free(tmp);
		}
	}

	//print jusquau \n ou \0
	//char	*ft_substr(char const *s, unsigned int start, size_t len);
	int	i;
	i = 0;
	
	while (adr_node->line[i])
	{
		if (adr_node->line[i] == '\n' || adr_node->line[i] == '\0')
			result = ft_substr(adr_node->line, 0, i);
		i++;
	}
	
	//sub
	tmp = ft_substr(adr_node->line, i + 1, ft_strlen(adr_node->line));
	adr_node->line = tmp;
	free(tmp);

	return (result);
}


int	main(void)
{
	int	fd;
	fd = open("test.txt", O_RDONLY);
	printf("1: %s\n\n", get_next_line(fd));
	printf("2: %s\n\n", get_next_line(fd));

	return (0);
}