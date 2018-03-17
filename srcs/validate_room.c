/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_room.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 01:15:00 by ttran             #+#    #+#             */
/*   Updated: 2018/03/17 01:15:07 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** A major change. Push ptr until it's the last room.
** Create a new function called "add_graph".
*/

static int	setup_room(t_super *hold, int room_type, char *line)
{
	t_graph	*ptr;

	if (ft_strchr(line, '-') != NULL)
		return (LINK);
	ptr = hold->graph;
	if (ptr == NULL)
	{
		if (init_graph(&ptr, room_type, line, hold) < 0)
			return (INVALID_ROOM);
	}
	else
	{
		while (ptr->next_room != NULL)
			ptr = ptr->next_room;
		if (init_graph(&ptr, room_type, line, hold) < 0)
			return (INVALID_ROOM);
	}
	return (0);
}

/*
** 1 for start, 2 for end, -1 for invalid.
*/

static int	err_end_start(t_super *hold, char *line)
{
	int		flag;

	flag = -1;
	if (ft_strcmp("##end", line) == 0)
	{
		hold->end_counter++;
		return (END);
	}
	else if (ft_strcmp("##start", line) == 0)
	{
		hold->start_counter++;
		return (START);
	}
	return (flag);
}

static int	setup_end_start(t_super *hold, char *line)
{
	int		determine;

	if ((determine = err_end_start(hold, line)) < 0)
		return (0);
	get_next_line(STDIN_FILENO, &line);
	while (line[0] != '\0' && line[0] == '#' && line[1] != '#')
		get_next_line(STDIN_FILENO, &line);
	if (line[0] == 'L' || line[0] == '\0' || (line[0] == '#' &&
	line[1] == '#') || ft_strchr(line, '-') != NULL)
		return (INVALID_ROOM);
	return (setup_room(hold, determine, line));
}

/*
** If it's a start/end, it'll read another line and see if its' a valid room.
** Start/End cannot be same room!
*/

static int	validate_room(t_super *hold, char *line)
{
	if (line[0] == '#' && line[1] != '#')
		return (0);
	else if (line[0] == '#' && line[1] == '#')
		return (setup_end_start(hold, line));
	else if (line[0] == 'L')
		return (INVALID_ROOM);
	else
		return (setup_room(hold, 0, line));
}

/*
** Just make sure the coordinate are numbers.
** Then use ft_strcmp to ensure that there are no duplicate room names.
** ft_strsplit by space and make sure n = 3 is the '\0', otherwise it's
** an error.
** If 0 == keep reading, if -2 == error, if 1 == move onto set_links.
** Send in address of line so it can be freed inside of set_links.
** Room name will never start with L or #
** # is comment, ## is command for the next room
*/

int			set_room_links(t_super *hold)
{
	char	*line;
	int		flag;

	flag = 0;
	while (42)
	{
		get_next_line(STDIN_FILENO, &line);
		if (line[0] == '\0' || (flag = validate_room(hold, line)) < 0)
		{
			free(line);
			return (INVALID_ROOM);
		}
		else if (flag == LINK)
			break ;
	}
	if (hold->end_counter != 1 && hold->start_counter != 1)
	{
		free(line);
		return (INVALID_ROOM);
	}
	return (set_links(hold, &line));
}
