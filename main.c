/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:53:42 by algasnie          #+#    #+#             */
/*   Updated: 2025/11/05 14:53:58 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	printf("1: %s\n\n", get_next_line(fd));
	printf("2: %s\n\n", get_next_line(fd));
	printf("3: %s\n\n", get_next_line(fd));
	printf("4: %s\n\n", get_next_line(fd));
	printf("5: %s\n\n", get_next_line(fd));
	printf("6: %s\n\n", get_next_line(fd));
	return (0);
}
