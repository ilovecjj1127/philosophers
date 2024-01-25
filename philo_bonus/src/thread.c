/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessie <jessie@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 12:18:42 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/25 11:48:18 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

/**
 * loop be interrupted by 1 the death of one of the philos or reach the time
 * philos disposed clockwise - lock the right fork before the left one
*/

int	print_msg(t_philo *philo, char *str)
{
	sem_wait(philo->table->print);
	printf("%lu %d %s\n", get_time() - philo->table->start_time, \
		philo->id, str);
	sem_post(philo->table->print);
	return (0);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->table->forks);
	sem_wait(philo->table->forks);
	print_msg(philo, FORK);
	print_msg(philo, FORK);
	print_msg(philo, EAT);
	sem_wait(philo->table->dead);
	philo->last_eat = get_time();
	sem_post(philo->table->dead);
	ft_usleep(philo->table->time_to_eat);
	sem_wait(philo->table->dead);
	philo->meal_num++;
	sem_post(philo->table->dead);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->table->num == 1 || philo->table->max_eat == 0)
		return (NULL);
	philo->last_eat = philo->table->start_time;
	pthread_create(&philo->monitor, NULL, monitor, philo);
	pthread_detach(philo->monitor);
	if (philo->id % 2 == 1)
	{
		print_msg(philo, THINK);
		ft_usleep(philo->table->time_to_eat / 2);
	}
	while (1)
	{
		if (philo->meal_num != -1 && philo->meal_num < philo->table->max_eat)
			eat(philo);
		print_msg(philo, SLEEP);
		ft_usleep(philo->table->time_to_sleep);
		print_msg(philo, THINK);
	}
	return (NULL);
}

void	*monitor(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (1)
	{
		sem_wait(philo->table->dead);
		if (get_time() - philo->last_eat > philo->table->time_to_die)
		{
			sem_wait(philo->table->print);
			printf("%lu %d %s\n", get_time() - philo->table->start_time, \
				philo->id, DIE);
			exit(0);
		}
		else if (philo->meal_num == philo->table->max_eat)
		{
			sem_post(philo->table->dead);
			ft_usleep(philo->table->time_to_eat * (philo->table->num / 2));
			exit(0);
		}
		sem_post(philo->table->dead);
	}
	return (NULL);
}
