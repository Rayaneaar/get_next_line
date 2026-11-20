/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaribou <raaribou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 08:45:49 by raaribou          #+#    #+#             */
/*   Updated: 2026/11/20 16:20:20 by raaribou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>


char *read_and_save(int fd , char *cache)
{
  char *buff;
  int b_read;
  char *temp;

  buff = malloc(BUFFER_SIZE + 1);
  if (!buff)
    return (free(cache), NULL);
  b_read = 1;
  while (b_read > 0 && !ft_strchr(cache, '\n'))
  {
    b_read = read(fd , buff ,BUFFER_SIZE);
    if (b_read == -1)
      return (free(buff) ,free(cache) , NULL);
    buff[b_read] = '\0';
    temp = ft_strjoin(cache, buff);
    if (!temp)
      return (free(buff) ,free(cache), NULL);
    free(cache);
    cache = temp;
  }
  free(buff);
  return (cache);
}

char *extract_line(char *cache)
{
  char *line;
  int i;

	if (!cache || !cache[0])
    return (NULL);
  i = 0;
  while (cache[i] && cache[i] !='\n')
    i++;
  if (cache[i] == '\n')
    i++;
  line = ft_substr(cache, 0,i);
  return(line);
}
char *trim(char *cache , size_t len)
{
  char *new_cache;
  size_t cache_len;

  if (!cache)
    return (NULL);
  cache_len = ft_strlen(cache);
  if (len >= cache_len)
    return(free(cache) , NULL);
  new_cache = ft_substr(cache,len, cache_len - len);
  free(cache);
  return(new_cache);
}
char *get_next_line(int fd)
{
  static char *cache;
  char *line;

  if (fd < 0 || BUFFER_SIZE <= 0)
    return (NULL);
  if (!cache)
    cache = ft_strdup("");
  cache = read_and_save(fd , cache);
  if (!cache)
    return (NULL);
  line = extract_line(cache);
  if (!line)
    return(free(cache),cache = NULL , NULL);
  cache = trim(cache, ft_strlen(line));
  return(line);
}
