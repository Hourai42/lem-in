/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 01:42:55 by ttran             #+#    #+#             */
/*   Updated: 2018/03/17 01:42:59 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Parse_info will hold ant_nbr until the entry room is decided.
*/

int	parse_info(t_super *hold)
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

int	main(void)
{
	t_super	*hold;
	int		flag;

	flag = 0;
	init_super(&hold);
	if ((flag = parse_info(hold)) == 0)
		if ((flag = set_map(hold)) == SUCCESS)
			move_ants(hold);
	if (flag < 0)
		error_messages(flag);
	ft_printf("\n");
	superfree(&hold);
	return (0);
}
