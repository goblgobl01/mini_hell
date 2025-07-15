/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_herdoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:55:24 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/14 16:30:39 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../header.h"

static char *get_var(char *s)
{
	int i;
	int j;
	int var_len;

	j = 0;
	i = 0;
	while(s[i] && s[i] != ' ' && s[i]!= '$' && (ft_isalnum(s[i]) || s[i] == '_' || s[i] == '?')) // stops at not aphanum or underscore or question mark
	{
		i++;
		if(s[i - 1] == '?')
			break ;
	}
	if( i != 0)
	{
		var_len = i;
		char *str = malloc(i + 1);
		i = 0;
		while(i < var_len)
			str[j++] = s[i++];
		str[j] = '\0';
		return str;
	}
	else
		return NULL;
}

char *ft_expand_herdoc(char *s, t_env_copy *env)
{
	int	i;
	int single_flag;
	int	double_flag;
	char *tmp;
	i = 0;
   
	
	i = 0;
	single_flag = 0;
	double_flag = 0;
   if(!s)
   {
		return NULL;
   }
	// printf("ff|%s|\n\n\n\n\n", s);

	while(s[i])
	{
		char *var_name;
		// if(s[i] == '\'' && !double_flag)
		// {
		// 	single_flag = !single_flag;

		// }
		// else if(s[i] == '\"' && !single_flag)
		// {
		// 	double_flag = !double_flag;

		// }
		if (s[i] == '$' && (ft_isalnum(s[i + 1] )|| s[i + 1] == '_' || s[i + 1] == '?'))
		{
			tmp = ft_substr(s, 0, i);
			var_name = get_var(s + (i + 1));
			if (!ft_get_env_value(var_name, env))
			{
		   		tmp = ft_strjoin(tmp, ft_strdup(""));
				s = ft_strjoin(tmp, ft_substr(s + i + 1 + ft_strlen(var_name) , 0, ft_strlen(s)));
			}
			else
			{
				tmp = ft_strjoin(tmp, ft_get_env_value(var_name, env));
		   		s = ft_strjoin(tmp, ft_substr(s + i + 1+ ft_strlen(var_name), 0, ft_strlen(s)));
			}
		}
			if(s[i])
				i++;
	}
	return s;
}
