/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dturella <dturella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:27 by dturella          #+#    #+#             */
/*   Updated: 2024/10/09 16:33:03 by dturella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*find_last_node(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	find_newline(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list != NULL)
	{
		i = 0;
		while (list->buffer[i] != '\0' && i < BUFFER_SIZE)
		{
			if (list->buffer[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

int	len_to_newline(t_list *list)
{
	int	i;
	int	len;

	len = 0;
	while (list != NULL)
	{
		i = 0;
		while (list->buffer[i] != '\0')
		{
			if (list->buffer[i] == '\n')
				return (len + 1);
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

void	copy_line(t_list *list, char *line)
{
	int	i;
	int	j;

	j = 0;
	while (list != NULL)
	{
		i = 0;
		while (list->buffer[i] != '\0')
		{
			if (list->buffer[i] == '\n')
			{
				line[j] = list->buffer[i];
				j++;
				line[j] = '\0';
				return ;
			}
			line[j] = list->buffer[i];
			i++;
			j++;
		}
		list = list->next;
	}
	line[j] = '\0';
	return ;
}

void	replace_first_node(t_list **list, t_list *new_node, char *buffer)
{
	t_list	*temp;

	if (!*list)
		return ;
	while (*list != NULL)
	{
		temp = (*list)->next;
		free((*list)->buffer);
		free(*list);
		*list = temp;
	}
	*list = NULL;
	if (new_node->buffer[0] != '\0')
		*list = new_node;
	else
	{
		free(buffer);
		free(new_node);
	}
}
