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

#include <unistd.h>
#include <libft.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

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

	if (arg == 1)
		return (open(argv[1], O_RDONLY));
	in = pipeline_sd(arg - 1, argv);
	if (in < 0)
		return (-1);
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
		execve(argv[arg], NULL, NULL);
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

	if (arg == 2)
		return (heredoc(argv[2]));
	in = pipeline_hd(arg - 1, argv);
	if (in < 0)
		return (-1);
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
		execve(argv[arg], NULL, NULL);
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
	const int		outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
			S_IRWXU | S_IRWXG | S_IRWXO);
	int				in;
	int				i;
	pid_t			id;

	i = 1;
	while (++i < argc - 1)
		if (access(argv[i], F_OK))
			return (ft_dprintf(2, "command(s) invalid: %s\n", argv[i]));
	in = pipeline_sd(argc - 3, argv);
	id = fork();
	if (!id)
	{
		dup2(in, 0);
		dup2(outfile, 1);
		execve(argv[3], NULL, NULL);
	}
	waitpid(id, NULL, 0);
	close(outfile);
	close(in);
}

int
	pipex_hd(
int argc,
char **argv
)
{
	const int		outfile = open(argv[argc - 1],	
			O_WRONLY | O_CREAT | O_APPEND,
			S_IRWXU | S_IRWXG | S_IRWXO);
	int				in;
	int				i;
	pid_t			id;

	i = 2;
	while (++i < argc - 1)
		if (access(argv[i], F_OK))
			return (ft_dprintf(2, "command(s) invalid: %s\n", argv[i]));
	in = pipeline_hd(argc - 3, argv);
	id = fork();
	if (!id)
	{
		dup2(in, 0);
		dup2(outfile, 1);
		execve(argv[3], NULL, NULL);
	}
	waitpid(id, NULL, 0);
	close(outfile);
	close(in);
}
