/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:13:25 by algasnie          #+#    #+#             */
/*   Updated: 2025/11/05 14:53:32 by algasnie         ###   ########.fr       */
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

void	ft_read(t_list *adr_node, int fd)
{
	int		sz;
	char	*buffer;
	char	*tmp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return ;
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
}

void	ft_result(t_list *adr_node, char *result)
{
	char	*tmp;
	int		i;

	i = 0;
	result = NULL;
	while (adr_node->line[i])
	{
		if (adr_node->line[i] == '\n' || adr_node->line[i] == '\0')
		{
			result = ft_substr(adr_node->line, 0, i);
			break ;
		}
		i++;
	}
	tmp = ft_substr(adr_node->line, i + 1, ft_strlen(adr_node->line));
	adr_node->line = tmp;
}

char	*get_next_line(int fd)
{
	static t_list	**list;	
	t_list			*adr_node;
	char			*result;

	result = NULL;
	if (fd < 0)
		return (NULL);
	if (!list)
	{
		list = malloc(sizeof(t_list *));
		if (!list)
			return (NULL);
	}
	adr_node = ft_lst_shr(list, fd);
	if (adr_node == NULL)
		adr_node = ft_createlst_add_back(list, fd);
	ft_read(adr_node, fd);
	ft_result(adr_node, result);
	return (result);
}
