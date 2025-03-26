/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzelouan <mzelouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:30:21 by mzelouan          #+#    #+#             */
/*   Updated: 2025/03/26 10:30:22 by mzelouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	append_map_list(char *line, t_map_list **head, t_map_list **tail)
{
	t_map_list	*node;

	node = ft_calloc(sizeof(t_map_list), 1);
	if (node == NULL)
		return ;
	node->str = line;
	if (node->str[ft_strlen(node->str) - 1] == '\n')
		node->str[ft_strlen(node->str) - 1] = 0;
	node->next = NULL;
	if (*head == NULL)
	{
		*head = node;
		*tail = node;
	}
	else
	{
		(*tail)->next = node;
		*tail = node;
	}
}

static int	check_invalid_characters(char *str, int *number_of_players)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '\n')
		return (-1);
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != 'W' && str[i] != 'S'
			&& str[i] != 'E' && str[i] != 'N' && str[i] != ' '
			&& str[i] != '\n')
			return (-1);
		if (str[i] == 'W' || str[i] == 'N' || str[i] == 'E' || str[i] == 'S')
			(*number_of_players)++;
		i++;
	}
	return (0);
}

int	check_map_validity(t_map_list *head)
{
	t_map_list	*tmp;
	int			number_of_players;

	tmp = head;
	number_of_players = 0;
	while (tmp)
	{
		if (check_invalid_characters(tmp->str, &number_of_players) == -1)
			return (ft_putstr_fd("invalid map\n", 2), -1);
		tmp = tmp->next;
	}
	if (number_of_players != 1)
		return (ft_putstr_fd("invalid map\n", 2), -1);
	return (0);
}

int	get_size(t_map_list *node, int *len, int *rows)
{
	int			size;
	int			longest;
	t_map_list	*tmp;

	size = 0;
	longest = 1;
	tmp = node;
	while (tmp)
	{
		size++;
		(*rows)++;
		if (longest < (int)ft_strlen(tmp->str))
			longest = (int)ft_strlen(tmp->str);
		tmp = tmp->next;
	}
	*len = longest;
	return (longest * (size + 1));
}

void	fill_map(t_parsed_data *data, t_map_list *node, int len)
{
	t_map_list	*tmp;
	int			i;
	int			j;

	tmp = node;
	i = 0;
	j = 0;
	while (tmp)
	{
		j = 0;
		write_to_map(data, tmp, i, &j);
		fill(data, j, i, len);
		i++;
		tmp = tmp->next;
	}
}
