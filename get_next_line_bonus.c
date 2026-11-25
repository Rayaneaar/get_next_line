/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaribou <raaribou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 18:30:25 by raaribou          #+#    #+#             */
/*   Updated: 2026/11/21 18:44:00 by raaribou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_free(char *s, char *s2)
{
	free(s);
	free(s2);
	return (NULL);
}

static char	*drop_fd(t_fds **head, int fd)
{
	t_fds	**node;
	t_fds	*tmp;

	node = head;
	while (*node && (*node)->fd != fd)
		node = &(*node)->next;
	if (!(*node))
		return (NULL);
	tmp = *node;
	*node = (*node)->next;
	free(tmp->cache);
	free(tmp);
	return (NULL);
}

static char	*read_and_save(int fd, char *cache)
{
	char	*buff;
	ssize_t	b_read;
	char	*temp;

	buff = malloc((size_t)BUFFER_SIZE + 1);
	if (!buff)
		return (ft_free(cache, NULL));
	b_read = 1;
	while (b_read > 0 && !ft_strchr(cache, '\n'))
	{
		b_read = read(fd, buff, BUFFER_SIZE);
		if (b_read == -1)
			return (ft_free(cache, buff));
		if (b_read == 0)
			break ;
		buff[b_read] = '\0';
		temp = ft_strjoin(cache, buff);
		if (!temp)
			return (ft_free(cache, buff));
		free(cache);
		cache = temp;
	}
	free(buff);
	return (cache);
}

static char	*extract_and_trim(char **cache)
{
	char	*line;
	char	*new_cache;
	size_t	i;
	size_t	len;

	if (!*cache || !**cache)
		return (NULL);
	i = 0;
	while ((*cache)[i] && (*cache)[i] != '\n')
		i++;
	if ((*cache)[i] == '\n')
		i++;
	line = ft_substr(*cache, 0, i);
	if (!line)
		return (NULL);
	len = ft_strlen(*cache);
	new_cache = NULL;
	if (i < len)
		new_cache = ft_substr(*cache, i, len - i);
	if (i < len && !new_cache)
		return (ft_free(line, NULL));
	free(*cache);
	*cache = new_cache;
	return (line);
}

char	*get_next_line(int fd)
{
	static t_fds	*head;
	t_fds			*node;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = find_fd(&head, fd);
	if (!node)
		return (NULL);
	node->cache = read_and_save(fd, node->cache);
	if (!node->cache)
		return (drop_fd(&head, fd));
	line = extract_and_trim(&node->cache);
	if (!line || !node->cache)
	{
		drop_fd(&head, fd);
		return (line);
	}
	return (line);
}
