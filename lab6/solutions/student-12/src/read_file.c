#include "txtfile.h"

#define BUFFER_SIZE 1024

static int	count_file_lines(const char *filename)
{
	char	buffer[BUFFER_SIZE];
	int		fd;
	int		bytes;
	int		count;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	bytes = read(fd, buffer, BUFFER_SIZE);
	while (bytes > 0)
	{
		i = 0;
		while (i < bytes)
		{
			if (buffer[i] == '\n')
				count++;
			i++;
		}
		bytes = read(fd, buffer, BUFFER_SIZE);
	}
	close(fd);
	if (bytes < 0)
		return (-1);
	return (count + 1);
}
static void	free_partial(char **lines, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

static char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}
static char	*read_one_line(int fd)
{
	char	buffer[2];
	char	*line;
	char	*temp;
	int		bytes;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	bytes = read(fd, buffer, 1);
	while (bytes > 0)
	{
		buffer[1] = '\0';
		temp = join_and_free(line, buffer);
		if (!temp)
			return (NULL);
		line = temp;
		if (buffer[0] == '\n')
			break ;
		bytes = read(fd, buffer, 1);
	}
	if (bytes < 0 || (bytes == 0 && ft_strlen(line) == 0))
	{
		free(line);
		return (NULL);
	}
	return (line);
}
char	**read_file(const char *filename)
{
	char	**lines;
	int		fd;
	int		line_count;
	int		i;

	if (!filename)
		return (NULL);
	line_count = count_file_lines(filename);
	if (line_count <= 0)
		return (NULL);
	lines = ft_calloc(line_count + 1, sizeof(char *));
	if (!lines)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free(lines), NULL);
	i = 0;
	while (i < line_count)
	{
		lines[i] = read_one_line(fd);
		if (!lines[i])
			return (close(fd), free_partial(lines, i), NULL);
		i++;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}