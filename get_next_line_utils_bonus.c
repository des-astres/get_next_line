/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpierre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:07:29 by lpierre-          #+#    #+#             */
/*   Updated: 2024/07/08 14:07:32 by lpierre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

// returns index of first '\n' found, -1 if no line break found

int	seek_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\n' && s[i] != 0)
		i++;
	if (s[i] == '\n')
		return (i);
	return (-1);
}

// replaces current stash with substring starting after first '\n' is found

char	*update_stash(char *stash, unsigned int start)
{
	char	*substr;
	int		i;
	int		len;

	len = ft_strlen(stash) - start + 1;
	substr = malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (free_str(&stash));
	i = 0;
	while (stash[start + i] != 0)
	{
		substr[i] = stash[start + i];
		i++;
	}
	substr[i] = 0;
	free_str(&stash);
	return (substr);
}

// concatenates current stash with read buffer, creating a new stash

char	*ft_strjoin_mod(char *stash, char *buf)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*new;

	if (!stash)
		return (ft_strndup(buf, -1));
	len = ft_strlen(stash) + ft_strlen(buf);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (stash[i] != 0)
	{
		new[i] = stash[i];
		i++;
	}
	j = 0;
	while (buf[j] != 0)
		new[i++] = buf[j++];
	new[i] = 0;
	free_str(&stash);
	return (new);
}

// allocates and duplicates up to n characters of a string

char	*ft_strndup(char *s, int n)
{
	char	*dup;
	int		i;

	if (n < 0)
		n = ft_strlen(s);
	dup = malloc(sizeof(char) * (n + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}
