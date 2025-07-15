
#include "../header.h"

int is_valid_var_name(char *var)
{
	int i = 0;
	if (!var || (!isalpha(var[0]) && var[0] != '_'))
		return (0);
	i = 1;
	while (var[i])
	{
		if (!(isalpha(var[i]) || var[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void ft_unset(t_env_copy *env, char **var)
{
	int i;
	t_env_copy *node;

	i = 1;
	while (var[i])
	{
		if (!is_valid_var_name(var[i]))
		{
			stder("bash: unset: `", 2);
			stder(var[i], 2);
			stder("': not a valid identifier\n", 2);
			update_environment(env, "?", "1");
			return;
		}
		node = find_key(env, var[i]);
		if (node)
			lst_delete_node(&env, node);
		i++;
	}
	update_environment(env, "?", "0");
}
