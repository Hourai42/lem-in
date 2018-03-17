/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 01:22:52 by ttran             #+#    #+#             */
/*   Updated: 2018/03/17 01:22:57 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	decide_roomtype(t_graph *ptr, int room_type)
{
	ptr->start = 0;
	ptr->end = 0;
	if (room_type == START)
		ptr->start = 1;
	else if (room_type == END)
		ptr->end = 1;
}

/*
** 1 for successful validation, 0 for failed.
*/

static int	validate_room_specs(char **fuck, t_super *hold, t_graph *ptr)
{
	t_graph *checker;

	checker = hold->graph;
	if (fuck[0] == 0 || fuck[1] == 0 || fuck[2] == 0 || fuck[3] != 0)
		return (0);
	if ((ptr->x = validate_nbr_ants(fuck[1])) < 0 ||
	(ptr->y = validate_nbr_ants(fuck[2])) < 0)
		return (0);
	while (checker->next_room != NULL)
	{
		if (checker->x == ptr->x && checker->y == ptr->y)
			return (0);
		checker = checker->next_room;
	}
	return (1);
}

static int	room_name_repeats(t_super *hold, t_graph *ptr)
{
	t_graph *checker;

	checker = hold->graph;
	while (checker->next_room != NULL)
	{
		if (ft_strcmp(ptr->room_name, checker->room_name) == 0)
			return (1);
		checker = checker->next_room;
	}
	return (0);
}

static int	set_roomname(t_graph *ptr, char *line, t_super *hold)
{
	char	**fuck;
	int		flag;

	flag = 0;
	fuck = ft_strsplit(line, ' ');
	if (validate_room_specs(fuck, hold, ptr) == 0)
		flag = INVALID_ROOM;
	else
		ptr->room_name = ft_strdup(fuck[0]);
	if (flag == 0 && room_name_repeats(hold, ptr) == 1)
		flag = INVALID_ROOM;
	free_fuck(fuck);
	free(fuck);
	return (flag);
}

int			init_graph(t_graph **ptr, int room_type, char *line, t_super *hold)
{
	if (*ptr == NULL)
	{
		*ptr = malloc(sizeof(t_graph));
		hold->graph = *ptr;
	}
	else
	{
		(*ptr)->next_room = malloc(sizeof(t_graph));
		*ptr = (*ptr)->next_room;
	}
	(*ptr)->next_room = NULL;
	(*ptr)->room_name = NULL;
	(*ptr)->link = NULL;
	(*ptr)->x = -1;
	(*ptr)->y = -1;
	(*ptr)->steps = 999999;
	(*ptr)->visited = 0;
	(*ptr)->successful_path = 0;
	(*ptr)->occupied = 0;
	decide_roomtype(*ptr, room_type);
	return (set_roomname(*ptr, line, hold));
}
