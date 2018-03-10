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

int	setup_end_start(t_super *hold, char *line)
{
	
}

/*
** If it's a start/end, it'll read another line and see if its' a valid room.
** Start/End cannot be same room!
*/

int	validate_room(t_super *hold, char *line)
{
	char **fuck;

	if (line[0] == '#' && line[1] != '#')
		return (0);
	else if (line[0] == '#' && line[1] == '#')
		return (setup_end_start(hold, line));
	else if (line[0] == 'L')
		return (INVALID_ROOM);
}

/*
** Just make sure the coordinate are numbers.
** Then use ft_strcmp to ensure that there are no duplicate room names.
** ft_strsplit by space and make sure n = 3 is the '\0', otherwise it's an error.
** If 0 == keep reading, if -2 == error, if 1 == move onto set_links.
** Send in address of line so it can be freed inside of set_links.  
** Room name will never start with L or #
** # is comment, ## is command for the next room
*/

int	set_room_links(t_super *hold)
{
	char *line;
	int flag;

	flag = 0;
	while (42)
	{
		get_next_line(STDIN_FILENO, &line);
		if (line[0] == '\0' || (flag = validate_room(hold, line)) < 0)
		{
			free(line); 
			return (INVALID_ROOM);
		}
		else if (flag == 1)
			break;
	}
	if (hold->end != 1 && hold->start != 1)
	{
		free(line);
		return (INVALID_ROOM);
	}
	return(set_links(hold, &line));
}
