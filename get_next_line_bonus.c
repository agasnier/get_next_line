/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:13:25 by algasnie          #+#    #+#             */
/*   Updated: 2025/11/05 16:41:21 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*ft_lst_shr(t_list *lst, int fd)
{
	t_list	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_list	*ft_createlst_add_back(t_list **lst, int fd)
{
	t_list	*new_node;
	t_list	*last;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->line = NULL;
	new_node->next = NULL;
	if (!lst || *lst == NULL)
	{
		if (lst)
			*lst = new_node;
		return (new_node);
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	return (new_node);
}

void	ft_read(t_list *adr_node, int fd)
{
	int		sz;
	char	*buffer;
	char	*tmp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return ;
	sz = 1;
	while (sz > 0 && !ft_strchr(adr_node->line, '\n'))
	{
		sz = read(fd, buffer, BUFFER_SIZE);
		if (sz <= 0)
			break ;
		buffer[sz] = '\0';
		tmp = adr_node->line;
		if (!tmp)
			adr_node->line = ft_strdup(buffer);
		else
			adr_node->line = ft_strjoin(tmp, buffer);
		free(tmp);
		if (!adr_node->line)
			break ;
	}
	free(buffer);
}

char	*ft_result(t_list *adr_node)
{
	char	*tmp;
	char	*result;
	int		i;

	if (!adr_node->line || !adr_node->line[0])
		return (NULL);
	i = 0;
	result = NULL;
	while (adr_node->line[i])
	{
		if (adr_node->line[i] == '\n')
		{
			result = ft_substr(adr_node->line, 0, i + 1);
			break ;
		}
		i++;
	}
	if (result == NULL && i > 0)
		result = ft_substr(adr_node->line, 0, i);
	tmp = ft_substr(adr_node->line, i + 1, ft_strlen(adr_node->line));
	free(adr_node->line);
	adr_node->line = tmp;
	return (result);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			*adr_node;
	char			*result;

	result = NULL;
	if (fd < 0)
		return (NULL);
	adr_node = ft_lst_shr(list, fd);
	if (adr_node == NULL)
		adr_node = ft_createlst_add_back(&list, fd);
	ft_read(adr_node, fd);
	if (!adr_node->line || adr_node->line[0] == '\0')
		return (NULL);
	result = ft_result(adr_node);
	return (result);
}
