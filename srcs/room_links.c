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

void	decide_roomtype(t_graph *ptr, int room_type)
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

int	validate_room_name(char **fuck)
{

}

void	free_fuck(char **fuck)
{
	int i;

	i = -1;
	while (fuck[++i])
		free(fuck[i]);
}

int	set_roomname(t_graph *ptr, char *line, t_super *hold)
{
	char **fuck;
	int flag;

	flag = 0;
	fuck = ft_strsplit(line, ' ');
	if (validate_room_name(fuck) == 0)
		flag = INVALID_ROOM;
	else
		ptr->room_name = ft_strdup(fuck[0]);
	// Check for repeats here, ya lazy bum.
	free(fuck);
	free_fuck(fuck);
	return (flag);
}

int	init_graph(t_graph **ptr, int room_type, char *line, t_super *hold)
{
	*ptr = malloc(sizeof(t_graph));
	if (hold->graph == NULL)
		hold->graph = *ptr;
	(*ptr)->links = NULL;
	(*ptr)->next_room = NULL;
	(*ptr)->room_name = NULL;
	decide_roomtype(*ptr, room_type);
	return (set_roomname(*ptr, line, hold));
}

int	setup_room(t_super *hold, int room_type, char *line)
{
	t_graph *ptr;
	t_graph *ptr2;
	
	if (ft_strchr(line, '-') != NULL)
		return (LINK);
	ptr = hold->graph;
	if (ptr == NULL)
		init_graph(&ptr, room_type, line, hold);
	else
	{
		while (ptr->next_room != NULL)
			ptr = ptr->next_room;
		ptr2 = ptr->next_room;
		init_graph(ptr2, room_type, line, hold);
		ptr->next_room = ptr2;
	}
}

/*
** 1 for start, 2 for end, -1 for invalid.
*/

int	err_end_start(t_super *hold, char *line)
{
	int flag;
	char end[] = "##end";
	char start[] = "##start";

	flag = -1;
	if (ft_strcmp(end, line) == 0)
	{
		hold->end++;
		return (END);
	}
	else if (ft_strcmp(start, line) == 0)
	{
		hold->start++;
		return (START);
	}
	return (flag);
}

int	setup_end_start(t_super *hold, char *line)
{
	int determine;

	if ((determine = err_end_start(hold, line)) < 0)
		return (INVALID_ROOM); 
	get_next_line(STDIN_FILENO, &line);
	while (line[0] != '\0' && line[0] == '#' && line[1] != '#')
		get_next_line(STDIN_FILENO, &line);
	if (line[0] == 'L' || line[0] == '\0' || (line[0] == '#' && line[1] == '#') || ft_strchr(line, '-') != NULL)
		return(INVALID_ROOM);
	return (setup_room(hold, determine, line));
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
	else
		return(setup_room(hold, 0, line));
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
		else if (flag == LINK)
			break;
	}
	if (hold->end != 1 && hold->start != 1)
	{
		free(line);
		return (INVALID_ROOM);
	}
	return(set_links(hold, &line));
}
