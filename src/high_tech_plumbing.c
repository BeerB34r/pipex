/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   high_tech_plumbing.c                              :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/21 08:38:00 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/21 12:40:42 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <pipex.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

static int
	heredoc(
const char *delimit
)
{
	char	*line;
	int		pipefd[2];
	pid_t	id;

	if (pipe(pipefd))
		return (-1);
	id = fork();
	if (id < 0)
		return (close(pipefd[1]), close(pipefd[0]), -1);
	if (id)
		return (close(pipefd[1]), pipefd[0]);
	close(pipefd[0]);
	line = get_next_line(0);
	while (line && \
			(ft_strncmp(line, delimit, ft_strlen(delimit))
			|| line[ft_strlen(delimit)] != '\n'))
	{
		ft_dprintf(pipefd[1], "%s", line);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(pipefd[1]);
	exit(0);
}

static int
	pipeline(
int cmds,
char ***arguments,
char *infile,
bool hd
)
{
	int	in;
	int	pfd[2];

	if (cmds == -1)
	{
		if (hd)
			return (heredoc(infile));
		return (open(infile, O_RDONLY));
	}
	in = pipeline(cmds - 1, arguments, infile, hd);
	if (in < 0)
		return (-1);
	if (pipe(pfd))
		return (close(in), -1);
	if (boss_baby((int [3]){in, pfd[1], 2}, arguments[cmds], NULL, pfd[0]))
		return (ft_close((int []){in, pfd[0], pfd[1], -1}), -1);
	ft_close((int []){in, pfd[1], -1});
	return (pfd[0]);
}

static int
	split_cmds(
int start,
int argc,
char **argv,
char ****arguments
)
{
	char ***const	out = ft_calloc(argc - start - 1, sizeof(char **));
	int				i;
	bool			fail;

	i = -1;
	fail = false;
	*arguments = NULL;
	while (++i < argc - start - 1)
	{
		out[i] = ft_split(argv[i + start], ' ');
		if (!out[i])
			fail = ft_dprintf(2, "malloc failure in splitting phase\n");
		else if (access(out[i][0], F_OK))
			fail = ft_dprintf(2, "file %s does not exist\n", out[i][0]);
		else if (access(out[i][0], X_OK))
			fail = ft_dprintf(2, "file %s is not executable\n", out[i][0]);
		if (fail)
			return (free_matrix(out), 1);
	}
	*arguments = out;
	return (0);
}

int
	pipex_driver(
int argc,
char **argv,
bool heredoc
)
{
	const int		outfile = open_out(argv[argc - 1], true);
	const int		cmds = argc - 3 - heredoc;
	int				in; 
	char			***arguments;

	if (split_cmds(2 + heredoc, argc, argv, &arguments))
		return (close(outfile), 1);
	in = pipeline(cmds, arguments, argv[2 + heredoc], heredoc);
	if (in < 0)
		return (close(outfile), ft_dprintf(2, "pipeline failed\n"), 1);
	if (boss_baby((int[3]){in, outfile, 2}, arguments[argc - 5], NULL, -1))
		return (close(outfile), close(in), ft_dprintf(2, "fork failure\n"), 1);
	while (errno != ECHILD)
		waitpid(0, NULL, 0);
	close(outfile);
	close(in);
	free_matrix(arguments);
	return (0);
}
