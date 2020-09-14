#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "proba_gnl.h"

#define BUF_SIZE 10

void	ft_putchar(char	c)
{
	write(1, &c, 1);
}

void	ft_putstr(char  *str)
{
	while (*str)
		write(1, &(*str++), 1);
}

size_t	ft_strlen(const char	*str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return(0);
	while(str[i])
	{
		i++;
	}
	return(i);
}

int		ft_getchar(T_gnl	*obj)
{
	if (obj->ret == 0)
	{
		obj->ret = read(obj->fd, obj->buf, BUF_SIZE);
		obj->bufl = obj->buf;
	}
	return ((--(obj->ret) >= 0) ? (unsigned char)*(obj->bufl)++ : EOF);
}

char	*ft_strnew(int size)
{
	char	*new;
	int		i;

	i = 0;
	new = (char*)malloc(sizeof(char) * (size + 1));
	if (new)
	{
		while (i < size)
			new[i++] = '\0';
		new[i] = '\0';
		return (new);
	}
	return (NULL);
}

char	*ft_resize(char	*str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strnew (2 * strlen(str));
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	free(str);
	str = tmp;
	return (str);
}

int		get_line(T_gnl	*obj, char	**line)
{
	char		c;
	int			i;
	int			n;
	
	n = BUF_SIZE;
	i = 0;
	*line = ft_strnew(BUF_SIZE);
	while ((c = ft_getchar(obj)) != EOF && c != '\n')
	{
		(*line)[i] = c;
		++i;
		if (i == n)
		{
			*line = ft_resize(*line);
			n = 2 * n;
		}
	}
	return(ft_strlen(*line) > 0);
}

T_gnl	*ft_cr_n_elem(int fd)
{
	T_gnl	*new;

	new = (T_gnl*)malloc(sizeof(T_gnl));
	new->fd = fd;
	new->next = NULL;
	new->ret = 0;
	new->buf = ft_strnew(BUF_SIZE);
	new->bufl = new->buf;
	return (new);
}

int		get_next_line(int fd, char	**line)
{
	static	T_gnl	*head;
	T_gnl	*tmp;

	if (head == NULL)
		head = ft_cr_n_elem(fd);
	tmp = head;
	while (tmp->fd != fd)
	{
		if(tmp->next == NULL)
			tmp->next = ft_cr_n_elem(fd);
		tmp = tmp->next;
	}
	return (get_line(tmp, line));
}

int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line;

	fd1 = open("sudoku.txt", O_RDONLY);
	fd2 = open("text.txt", O_RDONLY);
	get_next_line(fd1, &line);
	ft_putstr(line);
	ft_putstr("\n\n");
	get_next_line(fd2, &line);
	ft_putstr(line);
	ft_putstr("\n\n");
	get_next_line(fd1, &line);
	ft_putstr(line);
	ft_putstr("\n\n");
	return(0);
}