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

#include <libft.h>
#include <unistd.h>
#include <fcntl.h>

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
