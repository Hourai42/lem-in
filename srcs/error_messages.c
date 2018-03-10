/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 19:39:07 by ttran             #+#    #+#             */
/*   Updated: 2018/03/09 19:39:12 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	error_messages(int flag)
{
	if (flag == -1)
		ft_printf("%s%s\n", RED, "ERROR : Please enter a valid ant number.");
	else if (flag == -2)
		ft_printf("%s%s\n", RED, "ERROR : Please enter valid rooms.");
}
