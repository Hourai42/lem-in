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

int	validate_room_name(char **fuck)
{
	if (fuck[0] == 0 || fuck[1] == 0 || fuck[2] == 0)
		return (0);
	if (validate_nbr_ants(fuck[1]) < 0 || validate_nbr_ants(fuck[2]) < 0)
		return (0);
	return (1);
}

void	free_fuck(char **fuck)
{
	int i;

	i = -1;
	while (fuck[++i])
		free(fuck[i]);
}

/*
** Due to the way the program is structured , I need to check if it's a single room
** or not first. If it's a single room, don't bother checking. Otherwise, check until
** it's NULL, since new rooms aren't connected to the old graph until after it's initialized.
*/

int	room_name_repeats(t_super *hold, t_graph *ptr)
{
	int count;
	t_graph *checker;

	count = 0;
	checker = hold->graph;
	if (checker->next_room != NULL)
	{
		while (checker != NULL)
		{
			if (ft_strcmp(ptr->room_name, checker->room_name) == 0)
				count++;
			checker = checker->next_room;
		}
	}
	if (count > 0)
		return (1);
	return (0);
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
	if (room_name_repeats(hold, ptr) == 1)
		flag = INVALID_ROOM;
	free_fuck(fuck);
	free(fuck);
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

/*
** The reason for ptr->next_room = ptr2 in the case of an error is to prevent mem. leaks.
** In the case of an error you still want the graph to be connected so you can free it.
*/

int	setup_room(t_super *hold, int room_type, char *line)
{
	t_graph *ptr;
	t_graph *ptr2;
	
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
		ptr2 = ptr->next_room;
		if (init_graph(&ptr2, room_type, line, hold) < 0)
		{
			ptr->next_room = ptr2;
			return (INVALID_ROOM);
		}
		ptr->next_room = ptr2;
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
	ft_putstr("WASSUP DAWGGG\n");
	return (0);
	//return(set_links(hold, &line));
}
