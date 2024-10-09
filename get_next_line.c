/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dturella <dturella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:23:12 by dturella          #+#    #+#             */
/*   Updated: 2024/10/09 16:34:08 by dturella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	fix_list(t_list **list)
{
	t_list	*new_node;
	t_list	*last_node;
	char	*buffer;
	int		i;
	int		j;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	new_node = malloc(sizeof(t_list));
	if (!buffer || !new_node)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	j = 0;
	while (last_node->buffer[i] != '\0' && last_node->buffer[i] != '\n')
		i++;
	while (last_node->buffer[i] != '\0' && last_node->buffer[i + 1] != '\0')
		buffer[j++] = last_node->buffer[i++];
	buffer[j] = '\0';
	new_node->buffer = buffer;
	new_node->next = NULL;
	replace_first_node(list, new_node, buffer);
}

char	*complete_line(t_list *list)
{
	char	*line;
	int		size;

	size = len_to_newline(list);
	line = malloc(sizeof(char) * (size + 1));
	if (!line)
		return (NULL);
	copy_line(list, line);
	return (line);
}

void	make_node(t_list **list, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	last_node = find_last_node(*list);
	new_node->buffer = buffer;
	new_node->next = NULL;
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
}

void	init_list(t_list **list, int fd)
{
	int		byte_read;
	char	*buffer;

	while (find_newline(*list) == 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return ;
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (!byte_read)
		{
			free(buffer);
			return ;
		}
		buffer[byte_read] = '\0';
		make_node(list, buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*line;

	list = NULL;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	init_list(&list, fd);
	if (!list)
		return (NULL);
	line = complete_line(list);
	fix_list(&list);
	return (line);
}

