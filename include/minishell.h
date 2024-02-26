/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachh <nachh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:09:52 by danimart          #+#    #+#             */
/*   Updated: 2024/01/02 11:35:54 by nachh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <fcntl.h>
# include "libft.h"
# include "builtins.h"
# include "ast.h"
# include "dfa.h"

typedef struct s_sh {
    char		*cmd;
    t_DFA       lexer;
	t_sym	    *sym;	
} t_sh;

t_sh g_sh = (t_sh){
    .cmd = NULL,
    .sym = NULL
};

#endif
