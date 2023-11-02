/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 05:04:13 by danimart          #+#    #+#             */
/*   Updated: 2023/11/02 06:11:27 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	get_exit_code(const char *str)
{
	unsigned long		i;
	unsigned long long	res;

	i = 0;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = (res * 10) + (str[i++] - '0');
		else
			return (255);
	}
	if (res > __LONG_MAX__)
		return (255);
	if (str[i] == '-')
		return (-res);
	return (res);
}

int	bin_exit(char *in, int *exit_code)
{
	int	i;

	i = 0;
	while (in[i] == ' ')
		i++;
	*exit_code = get_exit_code(in + i);
	return (1);
}
