/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cagomez- <cagomez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:40:26 by cagomez-          #+#    #+#             */
/*   Updated: 2024/11/25 20:16:05 by cagomez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
			break;
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
	static char	*storage = NULL;
	char		*line;

	line = NULL;
	if (fd == -1)
		return (NULL);
	storage = make_line(storage, fd);
	if (storage == NULL)
		return (NULL);
	take_the_rest(&storage, &line);
	return (line);
}

int main()
{
	int fd;
	char *line;

	fd = open("tester.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error abriendo el archivo");
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		printf("%s",line); // Sin "\n".
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}