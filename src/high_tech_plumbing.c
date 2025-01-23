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
	pipeline_sd(
int arg,
char **argv
)
{
	pid_t	id;
	int		in;
	int		pipefd[2];
	char	**arguments;

	if (arg == 1)
		return (open(argv[1], O_RDONLY));
	in = pipeline_sd(arg - 1, argv);
	if (in < 0)
		return (-1);
	arguments = ft_split(argv[arg], ' ');
	if (!arguments)
		return (close(in), -1);
	if (pipe(pipefd))
		return (close(in), -1);
	id = fork();
	if (id < 0)
		return (close(in), close(pipefd[1]), close(pipefd[0]), -1);
	if (!id)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		dup2(in, 0);
		execve(arguments[0], arguments, NULL);
	}
	close(pipefd[1]);
	close(in);
	return (pipefd[0]);
}

static int
	pipeline_hd(
int arg,
char **argv
)
{
	pid_t	id;
	int		in;
	int		pipefd[2];
	char	**arguments;

	if (arg == 2)
		return (heredoc(argv[2]));
	in = pipeline_hd(arg - 1, argv);
	if (in < 0)
		return (-1);
	arguments = ft_split(argv[arg], ' ');
	if (!arguments)
		return (close(in), -1);
	if (pipe(pipefd))
		return (close(in), -1);
	id = fork();
	if (id < 0)
		return (close(in), close(pipefd[1]), close(pipefd[0]), -1);
	if (!id)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		dup2(in, 0);
		execve(arguments[0], arguments, NULL);
	}
	close(pipefd[1]);
	close(in);
	return (pipefd[0]);
}

int
	pipex_sd(
int argc,
char **argv
)
{
	const int		outfile = open(argv[argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	int				in;
	int				i;
	pid_t			id;
	char			**arguments;

	i = 1;
	while (++i < argc - 1)
		if (access(argv[i], F_OK))
			return (ft_dprintf(2, "command(s) invalid: %s\n", argv[i]));
	in = pipeline_sd(argc - 3, argv);
	if (in < 0)
		return (close(outfile), ft_dprintf(2, "pipeline failed\n"), 1);
	arguments = ft_split(argv[argc - 2], ' ');
	if (!arguments)
		return (ft_close((int[]){in, outfile, -1}),
				ft_dprintf(2, "argument splitting failed\n"), 1);
	id = fork();
	if (id < 0)
		return (close(outfile), close(in), ft_dprintf(2, "fork failure\n"), 1);
	if (!id)
	{
		dup2(in, 0);
		dup2(outfile, 1);
		execve(arguments[0], arguments, NULL);
	}
	while (errno != ECHILD)
		waitpid(0, NULL, 0);
	close(outfile);
	close(in);
	return (0);
}

int
	pipex_hd(
int argc,
char **argv
)
{
	const int		outfile = open(argv[argc - 1],	
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	int				in;
	int				i;
	pid_t			id;
	char	**arguments;

	i = 2;
	while (++i < argc - 1)
		if (access(argv[i], F_OK))
			return (ft_dprintf(2, "command(s) invalid: %s\n", argv[i]), 1);
	in = pipeline_hd(argc - 3, argv);
	if (in < 0)
		return (close(outfile), ft_dprintf(2, "pipeline failed\n"), 1);
	arguments = ft_split(argv[argc - 2], ' ');
	if (!arguments)
		return (ft_close((int[]){in, outfile, -1}),
				ft_dprintf(2, "argument splitting failed\n"), 1);
	id = fork();
	if (id < 0)
		return (close(outfile), close(in), ft_dprintf(2, "fork failure\n"), 1);
	if (!id)
	{
		dup2(in, 0);
		dup2(outfile, 1);
		execve(arguments[0], arguments, NULL); // TODO refactor into a function
	}
	while (errno != ECHILD)
		waitpid(0, NULL, 0);
	close(outfile);
	close(in);
	return (1);
}
