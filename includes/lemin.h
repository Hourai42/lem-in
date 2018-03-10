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
# define INVALID_ORDER -3
# define INVALID_LINKS -4

# define START 1
# define END 2

typedef struct s_ant
{
	struct t_graph *in_here;
	int ant_nbr;
}				t_ant;

typedef struct s_graph
{
	struct s_graph *links;
	struct s_graph *next_room;
	char *room_name;
}				t_graph;

/*
** Holds the ant array and the graph, including control structures.
** Hmm, next time, you can simply put line into your super structure
** so you can free all at once easier. But, oh well.
*/

typedef struct s_super
{
	t_ant *group;
	t_graph *graph;
	int end_counter;
	int start_counter;
}			t_super;

#endif

