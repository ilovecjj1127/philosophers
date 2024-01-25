/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessie <jessie@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 22:37:25 by jessie        #+#    #+#                 */
/*   Updated: 2024/01/12 14:19:41 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	check_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (get_time() - philo->last_eat > philo->table->time_to_die)
	{
		print_msg(philo, DIE);
		stop_table(philo->table);
		pthread_mutex_unlock(&philo->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock);
	return (0);
}

int	check_full(t_philo *philo)
{
	int	check;

	if (philo->table->max_eat == -1)
		return (0);
	pthread_mutex_lock(&philo->lock);
	check = (philo->meal_num >= philo->table->max_eat);
	pthread_mutex_unlock(&philo->lock);
	return (check);
}

int	is_stop(t_table *table)
{
	int	check;

	pthread_mutex_lock(&(table->lock));
	check = table->stop;
	pthread_mutex_unlock(&(table->lock));
	return (check);
}

void	stop_table(t_table *table)
{
	pthread_mutex_lock(&(table->lock));
	table->stop = 1;
	pthread_mutex_unlock(&(table->lock));
}
