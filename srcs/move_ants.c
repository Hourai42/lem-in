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

void	one_turn(t_super *hold)
{

}

int	ants_in_end(t_super *hold)
{
	int i;
	int ants_end;

	ants_end = 0;
	i = -1;
	while (++i < ants_end)
	{
		if (hold->farm[i].end == 1)
			ants_end++;
	}
}

/*
** This function moves the ants until they are all in end.
** 1 movement per ant per turn.
** Add the waiting heuristic w/ steps later.
** L(ant-number)-(Room Name)
*/

void	move_ants(t_super *hold)
{
	while (42)
	{
		one_turn(t_super *hold)
		if (ants_in_end(hold) == hold->ant_total)
			break;	
	}
}
