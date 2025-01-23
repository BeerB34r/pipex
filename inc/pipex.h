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

int	
	pipex(
		int argc,
		char **argv
		);	// FILE: pipex.c
int	
	pipex_sd(
		int argc,
		char **argv
		);	// FILE: high_tech_plumbing.c
int	
	pipex_hd(
		int argc,
		char **argv
		);	// FILE: high_tech_plumbing.c
int	
	usage(
		char *bin
		);	// FILE: toolbox.c
void
	ft_close(
		int *fds
		);	// FILE: toolbox.c
#endif
