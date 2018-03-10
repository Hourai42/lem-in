/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 12:04:45 by ttran             #+#    #+#             */
/*   Updated: 2018/03/07 12:04:46 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Parse_info will hold ant_nbr until the entry room is decided.
*/

int		parse_info(t_super *hold)
{
	int ant_nbr;
	int flag;

	flag = 0;
	if ((ant_nbr = nbr_ants()) < 0)
		return (INVALID_ANT);
	if ((flag = set_rooms_links(hold)) < 0)
		return (flag);
	// Create the ant struct here and put it inside of hold.
	return (0);
}

int main(void)
{
	t_super *hold;
	int flag;

	flag = 0;
	init_super(&hold);
	if (flag = parse_info(hold) == 0)
		if (flag = set_map(hold) == 0)
			move_ants(hold);
	if (flag < 0)
		error_messages(flag);
	//free everything in hold and hold itself. Remember to free room_name as well. Always check NULL b4 free!
	return (0);
}
