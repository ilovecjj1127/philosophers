/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessie <jessie@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 14:18:28 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/12 10:56:42 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
// even: time_to_die = time_to_eat + time_to_sleep +10
// odd: time_to_die = time_to_eat * 2 + time_to_sleep + 10

/* join all the thread before destroy all the mutex!!! */
void	end_table(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].lock);
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->lock);
	free(table->forks);
	free(table->philos);
}

int	start_table(t_table *table)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&table->lock);
	while (++i < table->num)
		pthread_create(&(table->philos[i].thread), NULL, &routine, \
			(void *)&table->philos[i]);
	table->start_time = get_time();
	i = -1;
	while (++i < table->num)
		table->philos[i].last_eat = table->start_time;
	pthread_mutex_unlock(&table->lock);
	pthread_create(&(table->monitor), NULL, &monitor, (void *)table);
	i = -1;
	pthread_join(table->monitor, NULL);
	while (++i < table->num)
		pthread_join(table->philos[i].thread, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table		table;

	if (argc < 5 || argc > 6)
		return (error("Incorrect arguments number!"));
	if (init_table(&table, argv))
		return (1);
	if (start_table(&table))
		return (1);
	end_table(&table);
	return (0);
}
