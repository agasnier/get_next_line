/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:14:10 by algasnie          #+#    #+#             */
/*   Updated: 2025/11/05 11:30:49 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_list
{
	int				fd;
	char			*line;
	struct s_list	*next;
}	t_list;



//get_next_line.c
char	*get_next_line(int fd);


//get_next_line_utils.c
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lst_shr(t_list **lst, int fd);
t_list	*ft_lstnew(int	fd);


#endif

