/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 00:24:29 by ttran             #+#    #+#             */
/*   Updated: 2018/03/17 00:24:34 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	free_link_and_name(t_graph *graph)
{
	t_link *ptr;

	if (graph->room_name != NULL)
		free(graph->room_name);
	ptr = graph->link;
	while (ptr != NULL)
	{
		graph->link = graph->link->next;
		free(ptr);
		ptr = graph->link;
	}
}

static void	free_graph(t_super *hold)
{
	t_graph *ptr;

	ptr = hold->graph;
	while (hold->graph != NULL)
	{
		hold->graph = hold->graph->next_room;
		free_link_and_name(ptr);
		free(ptr);
		ptr = hold->graph;
	}
}

static void	free_farm(t_super *hold)
{
	int i;

	i = -1;
	if (hold->farm != NULL)
	{
		while (++i < hold->ant_total)
			free(hold->farm[i]);
		free(hold->farm);
	}
}

void		superfree(t_super **hold)
{
	free_farm(*hold);
	free_graph(*hold);
	free(*hold);
}

void		free_fuck(char **fuck)
{
	int i;

	i = -1;
	while (fuck[++i])
		free(fuck[i]);
}
