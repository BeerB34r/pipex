/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   pipex.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/21 07:13:14 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/23 18:01:10 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>
#include <libft.h>
#include <fcntl.h>
#include <unistd.h>

int
	pipex(
int argc,
char **argv
)
{
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1]) + 1))
		return (pipex_sd(argc, argv));
	else if (argc < 6)
		return (usage(argv[0]));
	return (pipex_hd(argc, argv));
}
