/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 19:40:02 by ttran             #+#    #+#             */
/*   Updated: 2018/03/09 19:40:08 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"



/*
** Just make sure the coordinate are numbers.
** Then use ft_strcmp to ensure that there are no duplicate room names.
** ft_strsplit by space and make sure n = 3 is the '\0', otherwise it's an error.
** If 0 == keep reading, if -2 == error, if 1 == move onto set_links.
** Send in address of line so it can be freed inside of set_links.  
*/

int	set_room_links(t_super *hold)
{
	char *line;

	while (42)
	{
		get_next_line(STDIN_FILENO, &line);
		if (line[0] == '\0')
			return (INVALID_ROOM);
		if (validate_room(hold) < 0)
			return (INVALID_ROOM);
		else if (validate_room(hold) == 1)
			break;
	}
	return(set_links(hold, &line));
}
