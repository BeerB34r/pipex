/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   map.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/24 20:22:02 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/24 20:37:38 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <libft.h>
#include <unistd.h>
#include <stdlib.h>

static char
	**scout(void)
{
	char	*env_paths;
	int		i;

	i = -1;
	while (ft_strncmp(environ[++i], "PATH=", 5))
		;
	env_paths = NULL;
	if (environ[i])
		env_paths = &environ[i][5];
	if (!env_paths)
		return (NULL);
	return (ft_split(env_paths, ':'));
}

int
	expand(
char *unexpanded,
char **expanded
)
{
	char **const	paths = scout();
	char			*temp;
	int				i;

	*expanded = NULL;
	if (*unexpanded == '/')
		*expanded = unexpanded;
	i = -1;
	while (paths[++i] && !*expanded)
	{
		temp = ft_calloc(ft_strlen(paths[i]) + ft_strlen(unexpanded) + 2,
				sizeof(char));
		if (!temp)
			break ;
		ft_sprintf(temp, "%s/%s", paths[i], unexpanded);
		if (access(temp, F_OK) || access(temp, X_OK))
			free(temp);
		else
			*expanded = temp;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (!*expanded);
}
