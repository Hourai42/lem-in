/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 20:13:31 by ttran             #+#    #+#             */
/*   Updated: 2018/03/10 20:13:38 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_graph *link_name(t_super *hold, char *room_name)
{
	t_graph *checker;

	checker = hold->graph;
	while (checker != NULL)
	{
		if (ft_strcmp(checker->room_name, room_name) == 0)
			return(checker);
		checker = checker->next_room;
	}
	return (NULL);
}

/*
** You made a mistake here where you forgot to connect vertice->link to anything.
** When it started with NULL, at least.
*/

void	create_link(t_graph *vertice, t_graph *edge)
{
	t_link *ptr;

	ptr = vertice->link;
	if (ptr == NULL)
	{
		ptr = malloc(sizeof(t_link));
		ptr->next = NULL;
		ptr->connected_to = edge;
		vertice->link = ptr;
	}
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = malloc(sizeof(t_link));
		ptr = ptr->next;
		ptr->next = NULL;
		ptr->connected_to = edge;
	}
}

/*
** Having create_link twice turns it into an undirected graph.
** It can go both ways!
*/

int	validate_link_specs(char **fuck, t_super *hold)
{
	t_graph *vertice;
	t_graph *edge;

	if (fuck[0] == 0 || fuck[1] == 0 || fuck[2] != 0)
		return (INVALID_LINKS);
	if ((vertice = link_name(hold, fuck[0])) == NULL ||
	(edge = link_name(hold, fuck[1])) == NULL ||
	ft_strcmp(vertice->room_name, edge->room_name) == 0)
		return (INVALID_LINKS);
	create_link(vertice, edge);
	create_link(edge, vertice);
	return (1);
}

int	setup_link(t_super *hold, char *line)
{
	char **fuck;
	int flag;

	flag = 0;
	fuck = ft_strsplit(line, '-');
	if (validate_link_specs(fuck, hold) < 0)
		flag = INVALID_LINKS;
	free_fuck(fuck);
	free(fuck);
	return (flag);
}

int	validate_link(t_super *hold, char *line)
{
	if (line[0] == '#' && line[1] != '#')
		return (0);
	if (line[0] == '#' && line[1] == '#')
		return (INVALID_LINKS);
	return (setup_link(hold, line));

}

int	set_links(t_super *hold, char **line)
{
	while (42)
	{
		if ((*line)[0] == '\0')
			break;
		if (validate_link(hold, *line) < 0)
		{
			free(*line);
			return (INVALID_LINKS);
		}
		get_next_line(STDIN_FILENO, line);
	}
	free(*line);
	return (0);
}
