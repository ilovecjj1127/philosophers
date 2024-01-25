/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessie <jessie@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 15:59:11 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/15 09:59:18 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

u_int64_t	get_time(void)
{
	struct timeval	tp;
	u_int64_t		milliseconds;

	if (gettimeofday(&tp, NULL))
		return (error("gettime failed"));
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

void	ft_usleep(u_int64_t time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(500);
}

int	ft_atoi(const char *nptr)
{
	int		flag;
	int		num;
	char	*p;

	flag = 1;
	num = 0;
	p = (char *)nptr;
	while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r' \
		|| *p == '\f' || *p == '\v')
		p++;
	if (*p == '-')
		flag = -1;
	if (*p == '+' || *p == '-')
		p++;
	while (*p <= '9' && *p >= '0')
	{
		num = num * 10 + (*p - '0');
		p++;
	}
	return (flag * num);
}
