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

/*
** In your future projects, define 1/0 as "pass" or "fail" so you can have consistent error messages.
*/

# define START 1
# define END 2
# define LINK 3

typedef struct s_ant
{
	struct s_graph *in_here;
}				t_ant;

/*
** Well, a huge memory waste, but simple enough.... A ptr to what it's connected to, then a next.
*/

typedef struct s_link
{
	struct s_graph *connected_to;
	struct s_link *next;
}				t_link;

/*
** Well, putting "links" in your graph is a mistake. At least you know why now...
** Unless.. a link data structure that holds the graph and a pointer forward lmao.
*/

typedef struct s_graph
{
	t_link *link;
	struct s_graph *next_room;
	bool end;
	bool start;
	int x;
	int y;
	char *room_name;
}				t_graph;

/*
** Holds the ant array and the graph, including control structures.
** Hmm, next time, you can simply put line into your super structure
** so you can free all at once easier. But, oh well.
*/

typedef struct s_super
{
	t_ant *farm;
	t_graph *graph;
	int end_counter;
	int start_counter;
	int ant_total;
}			t_super;

int main(void);
int		nbr_ants(void);
int	validate_nbr_ants(char *line);
void	error_messages(int flag);
void	init_super(t_super **hold);
int	set_room_links(t_super *hold);
int	set_links(t_super *hold, char **line);
void	free_fuck(char **fuck);
void	create_antfarm(t_super *hold);
int	set_map(t_super *hold);

#endif

