/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:09:52 by danimart          #+#    #+#             */
/*   Updated: 2024/03/06 20:37:46 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <fcntl.h>
# include "libft.h"
# include "builtins.h"
# include "dfa.h"

typedef struct s_sh
{
	char		**env;
	char		*cmd;
}	t_sh;

#endif
