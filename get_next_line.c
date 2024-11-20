#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static void	take_the_rest(char **pre_line, char **line)
{
	char	*temp;
	int		i;

	i = 0;
	while (pre_line[0][i] != '\0' && pre_line[0][i] != '\n')
		i++;
	if (pre_line[0][i])
		i++;
	*line = ft_substr(*pre_line, 0, i);
	if (pre_line[0][i])
	{
		temp = ft_substr(*pre_line, i, (ft_strlen(*pre_line) - i));
		free(*pre_line);
		*pre_line = temp;
	}
	else
	{
		free(*pre_line);
		*pre_line = NULL;
	}
}

static char	*make_line(char *pre_line, int fd)
{
	char	*buffer;
	int		bts_read;

	bts_read = 1;
	//para asegurar que entra en el bucle
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(pre_line, '\n') && bts_read != 0)
	{
		bts_read = read(fd, buffer, BUFFER_SIZE);
		//buffer puntero al área de memoria donde se almacenan los datos
		//BUFFER_SIZE el número máx de bytes que se desean leer, en la función real variable de tipo size_t
		if (bts_read == 0)
			break ;
			//si no se leen bytes se llega al final del archivo se sale del bucle
		if (bts_read == -1)
		{
			free(buffer);
			free(pre_line);
			return (NULL);
		}
		//Si ocurre un error durante la lectura se liberan recursos buffer y pre_line
		buffer[bts_read] = '\0';
		//la cadena buffer al final de la cadena tiene que tener el carácter nulo y bts_read son los bytes leídos, que es la función read
		pre_line = ft_strjoin(pre_line, buffer);
		if (!pre_line)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (pre_line);
}

char	*get_next_line(int fd)
{
	static char	*pre_line = NULL;
	char		*line;

	line = NULL;
	if (fd == -1)
		return (NULL);
	pre_line = make_line(pre_line, fd);
	if (pre_line == NULL)
		return (NULL);
	take_the_rest(&pre_line, &line);
	return (line);
}



int	main()
{
	int fd = open("testing.txt", O_RDONLY);
	char	*line;

	while((line = get_next_line(fd)) != NULL)
	{
		printf(line);
	}
	close(fd);
	return(0);
}