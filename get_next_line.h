/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dturella <dturella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:20:33 by dturella          #+#    #+#             */
/*   Updated: 2024/10/09 16:32:39 by dturella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*buffer;
	struct s_list	*next;
}					t_list;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*complete_line(t_list *list);
void	make_node(t_list **list, char *buffer);
void	init_list(t_list **list, int fd);
char	*get_next_line(int fd);
void	fix_list(t_list **list);
t_list	*find_last_node(t_list *list);
int		find_newline(t_list *list);
int		len_to_newline(t_list *list);
void	copy_line(t_list *list, char *line);
void	replace_first_node(t_list **list, t_list *new_node, char *buffer);

#endif