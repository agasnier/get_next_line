/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:00:00 by algasnie          #+#    #+#             */
/*   Updated: 2025/11/05 16:50:30 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

void	test_single_file(char *filename)
{
	int		fd;
	char	*line;
	int		line_count;

	printf("\n========== TEST: %s ==========\n", filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Erreur: impossible d'ouvrir %s\n", filename);
		return ;
	}
	line_count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		line_count++;
		printf("Ligne %d: %s", line_count, line);
		if (line[ft_strlen(line) - 1] != '\n')
			printf(" (pas de \\n)\n");
		free(line);
	}
	printf("Total: %d lignes lues\n", line_count);
	close(fd);
}

void	test_multiple_fds(void)
{
	int		fd1;
	int		fd2;
	char	*line1;
	char	*line2;
	int		i;

	printf("\n========== TEST: MULTIPLE FDs ==========\n");
	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);

	if (fd1 == -1 || fd2 == -1)
	{
		printf("Erreur: impossible d'ouvrir les fichiers\n");
		return ;
	}

	i = 0;
	while (i < 3)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);

		printf("\n--- Tour %d ---\n", i + 1);
		if (line1)
		{
			printf("FD1: %s", line1);
			free(line1);
		}
		else
			printf("FD1: (NULL)\n");

		if (line2)
		{
			printf("FD2: %s", line2);
			free(line2);
		}
		else
			printf("FD2: (NULL)\n");

		i++;
	}

	close(fd1);
	close(fd2);
}

void	test_invalid_fd(void)
{
	char	*line;

	printf("\n========== TEST: FD INVALIDE ==========\n");
	line = get_next_line(-1);
	if (line == NULL)
		printf("OK: get_next_line(-1) retourne NULL\n");
	else
	{
		printf("ERREUR: get_next_line(-1) devrait retourner NULL\n");
		free(line);
	}
}

int	main(void)
{
	printf("====================================\n");
	printf("   TESTS GET_NEXT_LINE (BONUS)\n");
	printf("   BUFFER_SIZE = %d\n", BUFFER_SIZE);
	printf("====================================\n");

	test_single_file("test1.txt");
	test_single_file("test2.txt");
	test_single_file("test3.txt");
	test_invalid_fd();
	test_multiple_fds();

	printf("\n====================================\n");
	printf("   FIN DES TESTS\n");
	printf("====================================\n");

	return (0);
}
