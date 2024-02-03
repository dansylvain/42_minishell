#include "../includes/parsing/parsing_utils.h"
#include "../includes/minishell.h"

/**========================================================================
//? function NOT tested
//? used new func ft_strndup, NOT tested either...
//? check wether or not to add +1 when creating string with ft_strndup
 *========================================================================**/
char	**create_command_tab(t_ast_nde *node)
{
	int tree_length;
	char **commands_tab;
	int i;

	tree_length = 0;
	while (node)
	{
		node = node->sibling;
		tree_length++;
	}
	commands_tab = (char **)malloc(sizeof(char *) * tree_length + 1);
	if (commands_tab == 0)
		return (NULL);
	i = 0;
	while (i < tree_length)
	{
		commands_tab[i] = ft_strndup(node->start, node->end - node->start);
		if (commands_tab[i] == NULL)
			return (NULL);
		i++;
	}
	commands_tab[i] = NULL;
	return (commands_tab);
}
