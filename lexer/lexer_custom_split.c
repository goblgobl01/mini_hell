/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_custom_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:45:13 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/07/14 17:02:14 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	inside_charset(char c)
{
	char	*charset;
	int		i;

	charset = "|><";
	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int	count_words(const char *str)
{
	int	i;
	int	count;
	int	single_qoute;
	int	double_qoute;

	single_qoute = ((i = 0, 0), (double_qoute = 0, 0), (count = 0, 0), 0);
	while (str[i])
	{
		if ((!single_qoute && !double_qoute) && inside_charset(str[i]))
		{
			if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
				i++;
			i++;
			count++;
			continue ;
		}
		while (str[i])
		{
			if (str[i] == '\'' && !double_qoute)
				single_qoute = !single_qoute;
			else if (str[i] == '\"' && !single_qoute)
				double_qoute = !double_qoute;
			if ((!single_qoute && !double_qoute) && inside_charset(str[i]))
				break ;
			i++;
		}
		count++;
	}
	return (count);
}

static void	*free_all(char **strs, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static void	*allocate_duplicate(const char *str, int count, char **strs)
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	single_qoute;
	int	double_qoute;

	single_qoute = ((i = 0, 0), (l = 0, 0), 
			(k = 0, 0), (double_qoute = 0, 0), 0);
	while (k < count)
	{
		if ((!single_qoute && !double_qoute) && inside_charset(str[i]))
		{
			if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
			{
				if (str[i] == '>')
					strs[k] = ft_strdup(">>");
				if (str[i] == '<')
					strs[k] = ft_strdup("<<");
				i += 2;
				k++;
				continue ;
			}
			if (str[i] == '|')
				strs[k] = ft_strdup("|");
			if (str[i] == '>')
				strs[k] = ft_strdup(">");
			if (str[i] == '<')
				strs[k] = ft_strdup("<");
			i++;
			k++;
			continue ;
		}
		j = i;
		while (str[i])
		{
			if (str[i] == '\'' && !double_qoute)
				single_qoute = !single_qoute;
			else if (str[i] == '\"' && !single_qoute)
				double_qoute = !double_qoute;
			if ((!single_qoute && !double_qoute) && inside_charset(str[i]))
				break ;
			i++;
		}
		strs[k] = malloc((i - j) + 1);
		if (strs[k] == NULL)
			return (free_all(strs, k));
		while (j < i)
			strs[k][l++] = str[j++];
		strs[k++][l] = 0;
		l = 0;
	}
	strs[k] = NULL;
	return ((void *)1);
}

char	**lexer_custom_split(char const *s)
{
	char	**strs;
	int		count;

	if (!s)
		return (NULL);
	count = count_words(s);
	strs = malloc(sizeof(char *) * (count + 1));
	if (strs == NULL)
		return (NULL);
	if (!allocate_duplicate(s, count, strs))
		return (NULL);
	return (strs);
}
