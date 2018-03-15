/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 21:07:14 by ttran             #+#    #+#             */
/*   Updated: 2018/03/12 21:07:20 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_graph *find_end(t_super *hold)
{
	t_graph *ptr;

	ptr = hold->graph;
	while (ptr != NULL)
	{
		if (ptr->end == 1)
			return (ptr);
		ptr = ptr->next_room;
	}
	return (NULL);
}

/*
** The "start" node steps is always 999999, never changed.
** Thank god for that flash of insight and realization.
** As long as a single "link" leads to the end, the node is valid.
*/

int	leminparty(int *flag, t_graph *traversal, int steps, int win)
{
	t_link *ptr;

	if (traversal == NULL || (traversal->visited == 1 && traversal->steps <= steps))
		return (0);
	if (traversal->start == 1)
	{
		*flag = SUCCESS;
		return (1);
	}
	traversal->visited = 1;
	if (traversal->steps > steps)
		traversal->steps = steps;
	ptr = traversal->link;
	while (ptr != NULL)
	{
		if (leminparty(flag, ptr->connected_to, steps + 1, 0) == 1)
			win = 1;
		ptr = ptr->next;
	}
	if (win == 1)
		traversal->successful_path = 1;
	return (win);
}

void	go_thru_map(t_super *hold)
{
	t_graph *ptr;

	ptr = hold->graph;
	while (ptr != NULL)
	{
		ft_printf("end:%d start:%d room name:%s steps:%d successful_path:%d\n",
		ptr->end, ptr->start, ptr->room_name, ptr->steps, ptr->successful_path);
		ptr = ptr->next_room;
	}
}

/*
** Directed vs Undirected graph
** Steps taken as heuristic, so you don't step backwards
** End to Beginning to create steps taken!
** Flag is either SUCCESS or INVALID_PATH.
** Start high, only replace step number if it's lower in case of double pathing.
*/

int	set_map(t_super *hold)
{
	t_graph *end;
	int flag;
	
	flag = INVALID_PATH;	
	end = find_end(hold);
	leminparty(&flag, end, 0, 0);
	go_thru_map(hold);
	return (flag);
}
