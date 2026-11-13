/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaribou <raaribou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 04:34:20 by raaribou          #+#    #+#             */
/*   Updated: 2026/11/13 04:59:29 by raaribou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

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

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(s);
	dest = malloc(sizeof(char) * (src_len + 1));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new_s;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	new_s = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
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

  i = 0;
  if (!s)
    return (NULL);
  if (start >= ft_strlen(s))
    return (ft_strdup(""));
  substring = malloc(len * sizeof(char) + 1);
  if (!substring)
    return (NULL);
  while (s[start] && i < len)
  {
    substring[i] = s[start];
    i++;
    start++;
  }
  substring[i] = '\0';
  return (substring);
}
