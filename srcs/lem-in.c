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
	int flag;

	flag = 0;
	if ((hold->ant_total = nbr_ants()) < 0)
		return (INVALID_ANT);
	if ((flag = set_room_links(hold)) < 0)
		return (flag);
	create_antfarm(hold);
	return (0);
}

int main(void)
{
	t_super *hold;
	int flag;

	flag = 0;
	init_super(&hold);
	if ((flag = parse_info(hold)) == 0)
		if (flag = set_map(hold) == 0)
		//	move_ants(hold);
		ft_printf("%s\n", "FUKKEN SUP");
	if (flag < 0)
		error_messages(flag);
	//free everything in hold and hold itself. Remember to free room_name as well. Always check NULL b4 free!
	// Eh. You gotta free links now as well.... There's a LOT of shit to free lmao. Links, ants... as well. JEEZ.
	return (0);
}
