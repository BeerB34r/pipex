/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   toolbox.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/23 17:44:36 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/23 17:57:36 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line_bonus.h>
#include <libft.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pipex.h>

void
	ft_close(
int *fds
)
{
	while (*fds != -1)
		close(*fds++);
}

int
	usage(
char *bin
)
{
	ft_printf("Usage: %s [infile] [cmd0 cmd1 ... cmdn] [outfile]\n", bin);
	ft_printf("\t%s [here_doc] [delimiter] [cmd0 cmd1 ... cmdn] [outfile]\n",
		bin);
	return (1);
}

void
	free_matrix(
char ****input
)
{
	char	***matrix;
	int		i;
	int		j;

	i = -1;
	matrix = *input;
	while (matrix && matrix[++i])
	{
		j = -1;
		while (matrix[i][++j])
			free(matrix[i][j]);
		free(matrix[i]);
	}
	free(matrix);
}

int
	open_out(
char *path,
bool append
)
{
	int	flags;
	int	permissions;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	permissions = 0644;
	return (open(path, flags, permissions));
}

int
	boss_baby(
int fd[3],
char **argv,
char **envp,
int close_in_child
)
{
	pid_t	id;
	char	*path;

	id = fork();
	if (id < 0)
		return (ft_dprintf(2, "fork failure\n"), -1);
	else if (id)
		return (0);
	if (close_in_child != -1)
		close(close_in_child);
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	dup2(fd[2], 2);
	if (expand(argv[0], &path))
	{
		ft_dprintf(2, "command not found\n");
		ft_close((int []){0, 1, 2, fd[0], fd[1], fd[2], -1});
		exit(127);
	}
	exit(execve(path, argv, envp));
}
