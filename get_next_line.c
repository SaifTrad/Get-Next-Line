/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sturad <sturad@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 19:25:16 by sturad            #+#    #+#             */
/*   Updated: 2026/11/05 20:12:36 by sturad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*read_and_stash(int fd, char *stash)
{
	int		bytes;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
	{
		free(stash);
		return (NULL);
	}
	bytes = 1;
	while (!ft_strchr(stash, '\n') && bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buf);
			free(stash);
			return (NULL);
		}
		buf[bytes] = '\0';
		stash = ft_strjoin(stash, buf);
	}
	free(buf);
	return (stash);
}

char	*find_str(char *stash)
{
	int		i;
	char	*s;

	if (!stash || stash[0] == 0)
		return (NULL);
	s = malloc(ft_strlen(stash) + 2);
	if (!s)
	{
		return (NULL);
	}
	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
	{
		s[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		s[i] = '\n';
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*cut_str(char *stash)
{
	int			i;
	int			j;
	char		*new_str;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	i++;
	new_str = malloc(ft_strlen(stash) - i + 1);
	if (!new_str)
		return (NULL);
	j = 0;
	while (stash[i])
		new_str[j++] = stash[i++];
	new_str[j] = '\0';
	free(stash);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &str, 0) < 0)
		return (NULL);
	stash = read_and_stash(fd, stash);
	if (!stash)
		return (NULL);
	str = find_str(stash);
	stash = cut_str(stash);
	return (str);
}
