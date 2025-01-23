/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: mde-beer <mde-beer@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/01/21 06:50:24 by mde-beer     #+#    #+#                  */
/*   Updated: 2025/01/23 18:21:27 by mde-beer     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int
	main(
int argc,
char **argv
)
{
	if (argc < 5)
		return (usage(argv[0]));
	return (pipex(argc, argv));
}
