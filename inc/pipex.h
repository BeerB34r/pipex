/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   pipex.h                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/21 12:35:43 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/23 17:59:35 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>	// prototyping

int	
	pipex(
		int argc,
		char **argv
		);	// FILE: pipex.c
int	
	pipex_driver(
		int argc,
		char **argv,
		bool heredoc
		);	// FILE: high_tech_plumbing.c
int	
	usage(
		char *bin
		);	// FILE: toolbox.c
void
	ft_close(
		int *fds
		);	// FILE: toolbox.c
void
	free_matrix(
		char ***matrix
		);	// FILE: toolbox.c
int	
	open_out(
		char *path,
		bool append
		);	// FILE: toolbox.c
int	
	boss_baby(
		int fd[3],
		char **argv,
		char **envp,
		int close_in_child
		);	// FILE: toolbox.c
#endif
