/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <cagomez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:15:37 by cagomez-          #+#    #+#             */
/*   Updated: 2024/11/27 19:39:32 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	take_the_rest(char **storage, char **line)
{
	char	*temp;
	int		i;

	i = 0;
	while (storage[0][i] != '\0' && storage[0][i] != '\n')
		i++;
	if (storage[0][i])
		i++;
	*line = ft_substr(*storage, 0, i);
	if (storage[0][i])
	{
		temp = ft_substr(*storage, i, (ft_strlen(*storage) - i));
		free(*storage);
		*storage = temp;
	}
	else
	{
		free(*storage);
		*storage = NULL;
	}
}

static char	*make_line(char *storage, int fd)
{
	char	*buffer;
	int		bts_read;

	bts_read = 1;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(storage, '\n') && bts_read != 0)
	{
		bts_read = read(fd, buffer, BUFFER_SIZE);
		if (bts_read == 0)
			break ;
		if (bts_read == -1)
		{
			free(buffer);
			free(storage);
			return (NULL);
		}
		buffer[bts_read] = '\0';
		storage = ft_strjoin(storage, buffer);
		if (!storage)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[MAX_FD];
	char		*line;

	line = NULL;
	if (fd < 0 || fd >= MAX_FD)
		return (NULL);
	storage[fd] = make_line(storage[fd], fd);
	if (storage[fd] == NULL)
		return (NULL);
	take_the_rest(&storage[fd], &line);
	return (line);
}
/*int	main(void)
{
	int	fd1 = open("archivo1.txt", O_RDONLY);
	int	fd2 = open("archivo2.txt", O_RDONLY);
	int	fd3 = open("archivo3.txt", O_RDONLY);

	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
	{
		printf("Error al abrir uno de los archivos.\n");
		return (1);
	}
	char	*line1;
	char	*line2;
	char	*line3;
	int		line_number = 1;

	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		line3 = get_next_line(fd3);

		if (!line1 && !line2 && !line3)
			break;
		if (line1)
		{
			printf("Archivo 1, línea %d: %s", line_number, line1);
			free(line1);
		}
		if (line2)
		{
			printf("Archivo 2, línea %d: %s", line_number, line2);
			free(line2);
		}
		if (line3)
		{
			printf("Archivo 3, línea %d: %s", line_number, line3);
			free(line3);
		}

		line_number++;  
	}

	close(fd1);
	close(fd2);
	close(fd3);

	return (0);
}*/