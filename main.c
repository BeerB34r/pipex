/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/21 06:50:24 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/21 07:12:14 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int
	main(
int argc,
char **argv
)
{
	char	*err;

	if (argc < 5)
		return (usage());
	return (pipex(argc, argv));
}
