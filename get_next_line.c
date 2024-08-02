/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpierre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:41:35 by lpierre-          #+#    #+#             */
/*   Updated: 2024/06/14 13:41:38 by lpierre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*stash;
	char		*buf;
	char		*line;
	int			bytes_read;
	int			nl;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (free_str(&stash));
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free_str(&stash));
	nl = -1;
	while (nl == -1)
	{
		if (!read_fd(fd, buf, stash, &bytes_read))
			return (free_str(&buf), free_str(&stash));
		stash = ft_strjoin_mod(stash, buf);
		if (!stash)
			return (free_str(&buf), free_str(&stash));
		nl = seek_line(stash);
		if (!bytes_read && nl == -1)
			break ;
	}
	line = fill_line(&stash, nl, bytes_read);
	return (free_str(&buf), line);
}

void __attribute__((destructor))	clean(void)
{
	get_next_line(-42);
}
