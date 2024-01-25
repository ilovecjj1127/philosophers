/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessie <jessie@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 12:18:42 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/17 11:27:07 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/**
 * loop be interrupted by 1 the death of one of the philos or reach the time
 * philos disposed clockwise - lock the right fork before the left one
*/

int	print_msg(t_philo *philo, char *str)
{
	if (is_stop(philo->table))
		return (1);
	pthread_mutex_lock(&philo->table->print);
	printf("%lu %d %s\n", get_time() - philo->table->start_time, \
		philo->id, str);
	pthread_mutex_unlock(&philo->table->print);
	return (0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(philo->l_fork);
	print_msg(philo, FORK);
	print_msg(philo, FORK);
	if (!print_msg(philo, EAT))
	{
		pthread_mutex_lock(&philo->lock);
		philo->last_eat = get_time();
		pthread_mutex_unlock(&philo->lock);
		ft_usleep(philo->table->time_to_eat);
		pthread_mutex_lock(&philo->lock);
		philo->meal_num++;
		pthread_mutex_unlock(&philo->lock);
	}
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->table->num == 1 || philo->table->max_eat == 0)
		return (NULL);
	pthread_mutex_lock(&philo->table->lock);
	pthread_mutex_unlock(&philo->table->lock);
	if (philo->id % 2)
	{
		print_msg(philo, THINK);
		ft_usleep(philo->table->time_to_eat / 2);
	}
	while (!is_stop(philo->table))
	{
		eat(philo);
		if (print_msg(philo, SLEEP))
			break ;
		ft_usleep(philo->table->time_to_sleep);
		if (print_msg(philo, THINK))
			break ;
	}
	return (NULL);
}

void	*monitor(void *param)
{
	t_table	*table;
	int		i;
	int		full;

	table = (t_table *)param;
	i = 0;
	full = 0;
	while (!is_stop(table))
	{
		if (check_die(&table->philos[i]))
			break ;
		if (check_full(&table->philos[i]))
			full++;
		else
			full = 0;
		if (full == table->num)
			stop_table(table);
		if (++i == table->num)
			i = 0;
	}
	return (NULL);
}
