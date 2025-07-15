/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:42:39 by codespace         #+#    #+#             */
/*   Updated: 2025/07/15 02:22:28 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_env(t_env_copy *env)
{
	t_env_copy	*ptr;

	ptr = env;
	while (ptr != NULL)
	{
		if (ft_strcmp(ptr->name, "?") == 0)
		{
			ptr = ptr->next;
			continue ;
		}
		if (!(ptr->value))
			ptr = ptr->next;
		else
			printf("%s=%s\n", ptr->name, ptr->value);
		if (ptr)
			ptr = ptr->next;
	}
}

// void free_env(t_env_copy *env)
// {
// 	t_env_copy *temp;

// 	while (env)
// 	{
// 		temp = env;
// 		env = env->next;
// 		free(temp->name);
// 		free(temp->value);
// 		free(temp);
// 	}
// }
