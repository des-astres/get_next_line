/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpierre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:07:11 by lpierre-          #+#    #+#             */
/*   Updated: 2024/07/08 14:07:13 by lpierre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

// copies new line from stash and removes it from stash

char	*fill_line(char **stash, int index, int bytes_read)
{
	char	*line;

	if (!bytes_read && index == -1)
	{
		line = ft_strndup(*stash, -1);
		free_str(stash);
		return (line);
	}
	line = ft_strndup(*stash, index + 1);
	if (!line)
		return (free_str(stash));
	*stash = update_stash(*stash, index + 1);
	if (!*stash)
		return (free_str(&line));
	return (line);
}

// frees string if it exists

char	*free_str(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

// returns number of bytes_read, 0 on error or if nothing left to read

int	read_fd(int fd, char *buf, char *stash, int *bytes_read)
{
	*bytes_read = read(fd, buf, BUFFER_SIZE);
	if (*bytes_read == -1 || (!*bytes_read && (!stash || !stash[0])))
		return (0);
	buf[*bytes_read] = '\0';
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*stash[FD_MAX];
	char		*buf;
	int			bytes_read;
	int			nl;

	if (fd < 0)
		return (NULL);
	if (BUFFER_SIZE < 1)
		return (free_str(&stash[fd]));
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free_str(&stash[fd]));
	nl = -1;
	while (nl == -1)
	{
		if (!read_fd(fd, buf, stash[fd], &bytes_read))
			return (free_str(&buf), free_str(&stash[fd]));
		stash[fd] = ft_strjoin_mod(stash[fd], buf);
		if (!stash[fd])
			return (free_str(&buf), free_str(&stash[fd]));
		nl = seek_line(stash[fd]);
		if (!bytes_read && nl == -1)
			break ;
	}
	return (free_str(&buf), fill_line(&stash[fd], nl, bytes_read));
}

void __attribute__((destructor))	clean(void)
{
	get_next_line(-42);
}
