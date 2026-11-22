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

static void	drop_fd(t_fds **head, int fd)
{
	t_fds	**node;
	t_fds	*tmp;

	node = head;
	while (*node && (*node)->fd != fd)
		node = &(*node)->next;
	if (!(*node))
		return ;
	tmp = *node;
	*node = (*node)->next;
	free(tmp->cache);
	free(tmp);
}
static char	*read_and_save(int fd, char *cache)
{
	char	*buff;
	int		b_read;
	char	*temp;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (free(cache), NULL);
	b_read = 1;
	while (b_read > 0 && !ft_strchr(cache, '\n'))
	{
		b_read = read(fd, buff, BUFFER_SIZE);
		if (b_read == -1)
			return (free(buff), free(cache), NULL);
		buff[b_read] = '\0';
		temp = ft_strjoin(cache, buff);
		if (!temp)
			return (free(buff), free(cache), NULL);
		free(cache);
		cache = temp;
	}
	free(buff);
	return (cache);
}

static char	*extract_line(char *cache)
{
	char	*line;
	int		i;

	if (!cache || !cache[0])
		return (NULL);
	i = 0;
	while (cache[i] && cache[i] != '\n')
		i++;
	if (cache[i] == '\n')
		i++;
	line = ft_substr(cache, 0, i);
	return (line);
}

static char	*trim(char *cache, size_t len)
{
	char	*new_cache;
	size_t	cache_len;

	if (!cache)
		return (NULL);
	cache_len = ft_strlen(cache);
	if (len >= cache_len)
		return (free(cache), NULL);
	new_cache = ft_substr(cache, len, cache_len - len);
	free(cache);
	return (new_cache);
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
		return (drop_fd(&head, fd), NULL);
	line = extract_line(node->cache);
	if (!line)
		return (drop_fd(&head, fd), NULL);
	node->cache = trim(node->cache, ft_strlen(node->cache));
	if (!node->cache)
		drop_fd(&head, fd);
	return (line);
}
