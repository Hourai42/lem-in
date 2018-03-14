/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 22:47:48 by ttran             #+#    #+#             */
/*   Updated: 2018/03/13 22:47:53 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	end_movement(t_ant ant, t_graph *ptr, int ant_nbr)
{
	if (ptr != NULL)
	{
		ant.in_here = ptr;
		if (ptr->end == 1)
			ant.end = 1;
		else
			ptr->occupied = 1;
		ft_printf("L%d-%s ", ant_nbr, ptr->room_name);
	}
}

/*
** Steps is the only changing criteria.
*/

int		choose_movement(t_ant ant, int ant_nbr)
{
	t_graph *ptr;
	int steps;
	t_link *mover;

	mover = ant.in_here->link;
	steps = ant.in_here->steps;
	ptr = NULL;
	while (mover != NULL)
	{
		if (mover->connected_to->steps <= steps && 
		mover->connected_to->occupied == 0 && 
		mover->connected_to->successful_path == 1)
		{
			ptr = mover->connected_to;
			steps = mover->connected_to->steps;
		}
		mover = mover->next;
	}	
	if (ptr == NULL)
		return (0);
	end_movement(ant, ptr, ant_nbr);
	return (1);
}

void	move(t_ant ant, int ant_nbr)
{
	t_graph *ptr;

	ptr = ant.in_here;
	if (choose_movement(ant, ant_nbr) == 1)
		ptr->occupied = 0;
}

void	one_turn(t_super *hold)
{
	int i;

	i = -1;
	while (++i < hold->ant_total)
	{
		if (hold->farm[i].end != 1)
			move(hold->farm[i], i + 1);
	}
}

int	ants_in_end(t_super *hold)
{
	int i;
	int ants_end;

	ants_end = 0;
	i = -1;
	while (++i < hold->ant_total)
	{
		if (hold->farm[i].end == 1)
			ants_end++;
	}
	return (ants_end);
}

/*
** This function moves the ants until they are all in end.
** 1 movement per ant per turn.
** Add the waiting heuristic w/ steps later.
*/

void	move_ants(t_super *hold)
{
	while (42)
	{
		one_turn(hold);
		if (ants_in_end(hold) == hold->ant_total)
			break;
		//ft_printf("\n");
	}
}
