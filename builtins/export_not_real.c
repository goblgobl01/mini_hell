/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_not_real.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 04:05:39 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/15 04:12:46 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_export(t_command **cmd, t_env_copy *env)
{
	int		j;
	int		x;
	char	*value;

	value = NULL;
	x = 1;
	j = 0;
	if (!cmd[0]->args[1])
		print_export(env);
	while (cmd[0]->args[x])
	{
		export_args(env, value, j, cmd[0]->args[x]);
		x++;
	}
}
//////////////export ///$lvhjgb345dg important!