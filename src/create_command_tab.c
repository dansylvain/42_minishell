#include "../includes/minishell.h"
#include "parsing_utils.h"

char		**parse_cmd(char **command, char **env);
void		tmp_main();
t_ast_nde	*parse(char *str);
int			pipex(char *argv[], char *envp[]);
char	**create_command_tab(t_ast_nde *node, char *envp[]);
void	display_command_tab(char **command_tab);

void	display_command_tab(char **command_tab)
{
	int i;

	i = 0;
	ft_printf("command_tab: \n");
	while (command_tab[i])
	{
		ft_printf("commands_tab[%i]: >%s<\n", i,  command_tab[i]);
		i++;
	}
}

void	get_command_nbr(t_ast_nde **current, int *tree_length)
{
	(*tree_length) = 0;
	while (*current)
	{
		if ((*current)->token == AND || (*current)->token == OR)
			break;
		if ((*current)->token != PIPE && (*current)->end - (*current)->start + 1)
			(*tree_length)++;
		*current = (*current)->sibling;
	}
	ft_printf("tree_length: %i\n", (*tree_length));
}

char	**fill_command_tab(char ***commands_tab, t_ast_nde **node, int return_pipex)
{
	int i;

	i = 0;
	if (return_pipex && (*node)->sibling->sibling)
		(*node) = (*node)->sibling->sibling;
	while (*node)
	{
		if ((*node)->token == AND || (*node)->token == OR)
			break;
		if ((*node)->token != PIPE && (*node)->end - (*node)->start + 1)
		{
			(*commands_tab)[i] = ft_strndup((*node)->start, (*node)->end - (*node)->start + 1);
			if ((*commands_tab)[i] == NULL)
				return (NULL);
			i++;
		}
		(*node) = (*node)->sibling;
	}
	(*commands_tab)[i] = NULL;
	return (*commands_tab);
}

char	**create_command_tab(t_ast_nde *node, char *envp[])
{
	char **commands_tab;
	int	return_pipex;
	int tree_length;

	
	// initialize vars
	t_ast_nde *current;
	return_pipex = 0;
	while (node)
	{
		current = node;
		ft_printf("start THE loop\n");
		// count commands to malloc char **
		get_command_nbr(&current, &tree_length);
			
		// allocate memo for char **
		commands_tab = (char **)malloc(sizeof(char *) * tree_length + 1);
		if (commands_tab == 0)
			return (NULL);
			
		// fill char **
		commands_tab = fill_command_tab(&commands_tab, &node, return_pipex);
		display_command_tab(commands_tab);
		
		// pass char ** to PIPEX 
		return_pipex = pipex(commands_tab, envp);
		ft_printf("return_pipex: %i\n", return_pipex);
		if (node == NULL)
			break ;
		if (node->token == OR && return_pipex == 0)
			return_pipex = 1;
		if (node->token == OR && return_pipex == 1)
			return_pipex = 0;
		node = node->sibling;
		continue ;
	}
}
