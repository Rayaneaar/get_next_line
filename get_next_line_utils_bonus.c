/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaribou <raaribou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/21 18:29:47 by raaribou          #+#    #+#             */
/*   Updated: 2026/11/21 18:38:37 by raaribou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*haystack;

	if (!s)
		return (NULL);
	i = 0;
	haystack = (char *)s;
	while (haystack[i])
	{
		if (haystack[i] == c)
			return (&haystack[i]);
		i++;
	}
	if (c == '\0')
		return (&haystack[i]);
	return (NULL);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new_s;
	size_t	i;
	size_t	j;
	size_t	len1;

	if (!s2)
		return (NULL);
	len1 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	new_s = malloc(len1 + ft_strlen(s2) + 1);
	if (!new_s)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		new_s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		new_s[i++] = s2[j++];
	new_s[i] = '\0';
	return (new_s);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substring;

	if (!s)
		return (NULL);
	i = 0;
	if (start >= ft_strlen(s))
		len = 0;
	substring = malloc(len + 1);
	if (!substring)
		return (NULL);
	while (i < len && s[start])
	{
		substring[i] = s[start];
		i++;
		start++;
	}
	substring[i] = '\0';
	return (substring);
}

t_fds	*find_fd(t_fds **head, int fd)
{
	t_fds	*node;

	node = *head;
	while (node && node->fd != fd)
		node = node->next;
	if (node)
		return (node);
	node = malloc(sizeof(t_fds));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->cache = NULL;
	node->next = *head;
	*head = node;
	return (node);
}
