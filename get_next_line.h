/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: lpierre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:25:04 by lpierre-          #+#    #+#             */
/*   Updated: 2024/06/14 17:25:06 by lpierre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include<fcntl.h>
# include<stdlib.h>
# include<unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	ft_strlen(char *s);
int		seek_line(char *s);
char	*update_stash(char *stash, unsigned int start);
char	*ft_strjoin_mod(char *stash, char *buf);
char	*ft_strndup(char *s, int n);
char	*fill_line(char **stash, int index, int bytes_read);
int		read_fd(int fd, char *buf, char *stash, int *bytes_read);
char	*free_str(char **str);
char	*get_next_line(int fd);
void	clean(void) __attribute__((destructor));

#endif
