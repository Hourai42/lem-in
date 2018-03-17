/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 12:04:37 by ttran             #+#    #+#             */
/*   Updated: 2018/03/07 12:04:38 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <libft.h>
# include "ft_printf.h"

# define INVALID_ANT -1
# define INVALID_ROOM -2
# define INVALID_LINKS -3
# define INVALID_PATH -4

/*
** In your future projects, define 1/0 as "pass" or "fail"
** so you can have consistent error messages.
*/

# define START 1
# define END 2
# define LINK 3
# define SUCCESS 4

typedef struct		s_ant
{
	struct s_graph	*in_here;
	bool			end;
}					t_ant;

/*
** Well, a huge memory waste, but simple enough....
** A ptr to what it's connected to, then a next.
*/

typedef struct		s_link
{
	struct s_graph	*connected_to;
	struct s_link	*next;
}					t_link;

/*
** Well, putting "links" in your graph is a mistake. At least you know
** why now... Unless.. a link data structure that
** holds the graph and a pointer forward lmao. Steps, lower is better!
** Have an "occupied" for any room that isn't end.
*/

typedef struct		s_graph
{
	t_link			*link;
	struct s_graph	*next_room;
	bool			end;
	bool			start;
	int				x;
	int				y;
	char			*room_name;
	int				steps;
	int				visited;
	int				successful_path;
	int				occupied;
}					t_graph;

/*
** Holds the ant array and the graph, including control structures.
** Hmm, next time, you can simply put line into your super structure
** so you can free all at once easier. But, oh well.
*/

typedef struct		s_super
{
	t_ant			**farm;
	t_graph			*graph;
	int				end_counter;
	int				start_counter;
	int				ant_total;
}					t_super;

/*
** Main control structures of the program.
*/

int					main(void);
int					parse_info(t_super *hold);

/*
** Functions to set rooms and validate rooms.
*/

int					set_room_links(t_super *hold);
int					init_graph(t_graph **ptr, int room_type,
					char *line, t_super *hold);

/*
** Functions to set link and validate links.
*/

int					set_links(t_super *hold, char **line);
int					validate_link(t_super *hold, char *line);

/*
** Functions to move ants and check if all ants are at destination.
*/

void				move_ants(t_super *hold);
int					ants_in_end(t_super *hold);

/*
** Function to set map for ant traversal.
*/

int					set_map(t_super *hold);

/*
** Function to validate nbr of ants and create a farm to hold said ants.
*/

int					nbr_ants(void);
void				create_antfarm(t_super *hold);
int					validate_nbr_ants(char *line);

/*
** Handles error messages
*/

void				error_messages(int flag);

/*
** Handles all freeing in program
** Function to set the super struct.
*/

void				superfree(t_super **hold);
void				free_fuck(char **fuck);
void				init_super(t_super **hold);

#endif
