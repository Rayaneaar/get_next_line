/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaribou <raaribou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 10:24:49 by raaribou          #+#    #+#             */
/*   Updated: 2026/11/13 05:05:32 by raaribou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
char *extract_line(char *buffer , int position)
{
  char *line;
  int j;

  j = 0;
  line = malloc(sizeof(char) * position + 1);
  if (!line)
    return(NULL);
  while (j < position)
  {
    line[j] = buffer[j];
    j++;
  }
  line[j] = '\0';
  return (line);
}
char *get_next_line(int fd)
{
  char buffer[2048];
  int i;
  char *line;
  int bytes_read;
  static char *storage;

  i = 0;

  if (fd == -1)
    return (NULL);
  bytes_read = read(fd , &buffer , BUFFER_SIZE);
  if (bytes_read > 0)
    buffer[bytes_read] = '\0';
  storage = ft_strjoin(storage , buffer);
  while (storage[i])
  {
    if (storage[i] == '\n')
    {
      line = extract_line(storage , i + 1);
      return (line);
    }
    i++;
  }
  return(NULL);
}
