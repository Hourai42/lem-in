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

#include "lemin.h"

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

int	validate_room_specs(char **fuck, t_super *hold, t_graph *ptr)
{
	t_graph *checker;

	checker = hold->graph;
	if (fuck[0] == 0 || fuck[1] == 0 || fuck[2] == 0 || fuck[3] != 0)
		return (0);
	if ((ptr->x = validate_nbr_ants(fuck[1])) < 0 || (ptr->y = validate_nbr_ants(fuck[2])) < 0)
		return (0);
	while (checker->next_room != NULL)
	{
		if (checker->x == ptr->x && checker->y == ptr->y)
			return (0);
		checker = checker->next_room;
	}
	return (1);
}

void	free_fuck(char **fuck)
{
	int i;

	i = -1;
	while (fuck[++i])
		free(fuck[i]);
}

int	room_name_repeats(t_super *hold, t_graph *ptr)
{
	t_graph *checker;

	checker = hold->graph;
	while (checker->next_room != NULL)
	{
		if (ft_strcmp(ptr->room_name, checker->room_name) == 0)
			return (1);
		checker = checker->next_room;
	}
	return (0);
}

int	set_roomname(t_graph *ptr, char *line, t_super *hold)
{
	char **fuck;
	int flag;

	flag = 0;
	fuck = ft_strsplit(line, ' ');
	if (validate_room_specs(fuck, hold, ptr) == 0)
		flag = INVALID_ROOM;
	else
		ptr->room_name = ft_strdup(fuck[0]);
	if (room_name_repeats(hold, ptr) == 1)
		flag = INVALID_ROOM;
	free_fuck(fuck);
	free(fuck);
	return (flag);
}

int	init_graph(t_graph **ptr, int room_type, char *line, t_super *hold)
{
	if (*ptr == NULL)
	{
		*ptr = malloc(sizeof(t_graph));
		hold->graph = *ptr;
	}
	else
	{
		(*ptr)->next_room = malloc(sizeof(t_graph));
		*ptr = (*ptr)->next_room;
	}
	(*ptr)->links = NULL;
	(*ptr)->next_room = NULL;
	(*ptr)->room_name = NULL;
	(*ptr)->link = NULL;
	(*ptr)->x = -1;
	(*ptr)->y = -1;
	decide_roomtype(*ptr, room_type);
	return (set_roomname(*ptr, line, hold));
}

/*
** A major change. Push ptr until it's the last room.
** Create a new function called "add_graph".
*/

int	setup_room(t_super *hold, int room_type, char *line)
{
	t_graph *ptr;
	
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

int	err_end_start(t_super *hold, char *line)
{
	int flag;
	char end[] = "##end";
	char start[] = "##start";

	flag = -1;
	if (ft_strcmp(end, line) == 0)
	{
		hold->end_counter++;
		return (END);
	}
	else if (ft_strcmp(start, line) == 0)
	{
		hold->start_counter++;
		return (START);
	}
	return (flag);
}

int	setup_end_start(t_super *hold, char *line)
{
	int determine;

	if ((determine = err_end_start(hold, line)) < 0)
		return (0); 
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
	if (hold->end_counter != 1 && hold->start_counter != 1)
	{
		free(line);
		return (INVALID_ROOM);
	}
	return(set_links(hold, &line));
}
