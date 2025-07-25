/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:10:01 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/07/14 16:40:32 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_env_copy	*environment_copy(char **envp)
{
	int			i;
	t_env_copy	*original_ptr;
	t_env_copy	*ptr;

	i = 0;
	if (!(*envp))
	{
		ptr = lstnew(ft_strdup("?"), ft_strdup("0"));
		return (ptr);
	}
	original_ptr = lstnew(ft_strdup_name(envp[i]), ft_strdup_value(envp[i]));
	i++;
	while (envp[i])
	{
		ptr = lstnew(ft_strdup_name(envp[i]), ft_strdup_value(envp[i]));
		lstadd_back(&original_ptr, ptr);
		i++;
	}
	ptr = lstnew(ft_strdup("?"), ft_strdup("0"));
	lstadd_back(&original_ptr, ptr);
	return (original_ptr);
}

void	signal_handler(int sig)
{
	(void) sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int ac, char **av, char **envp)
{
	char		*str;
	t_env_copy	*ptr;

	(void)av;
	if (ac != 1)
		return (-1);
	ptr = environment_copy(envp);
	rl_catch_signals = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = readline("$> ");
		if (!str)
		{
			printf("exit\n");
			exit(ft_atoi(ft_get_env_value("?", ptr)));
		}
		if (!lexer(str, ptr))
			continue ;
		ft_parser(tokenizer(str), ptr);
		add_history(str);
	}
	return (0);
}
