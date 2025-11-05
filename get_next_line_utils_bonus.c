/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:13:54 by algasnie          #+#    #+#             */
/*   Updated: 2025/11/05 13:11:48 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*t;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	t = malloc(sizeof(char) * (len + 1));
	if (!t)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		t[i++] = s1[j++];
	j = 0;
	while (s2[j])
		t[i++] = s2[j++];
	t[i] = '\0';
	return (t);
}



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