/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessie <jessie@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 20:10:43 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/15 11:45:31 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	error(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->num);
	if (!table->philos)
		return (error("malloc failed"));
	i = -1;
	while (++i < table->num)
	{
		table->philos[i].table = table;
		table->philos[i].id = i + 1;
		table->philos[i].meal_num = 0;
		table->philos[i].last_eat = 0;
		table->philos[i].l_fork = &(table->forks[(i + 1) % table->num]);
		table->philos[i].r_fork = &(table->forks[i]);
		pthread_mutex_init(&(table->philos[i].lock), NULL);
	}
	return (0);
}

int	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->num);
	if (!table->forks)
		return (error("malloc failed"));
	i = -1;
	while (++i < table->num)
		pthread_mutex_init(&(table->forks[i]), NULL);
	return (0);
}

/* TODO: Error control of each argument */
int	init_table(t_table *table, char **argv)
{
	table->num = ft_atoi(argv[1]);
	if (table->num <= 0)
		return (error("invite at least one philosopher"));
	table->time_to_die = (u_int64_t) ft_atoi(argv[2]);
	table->time_to_eat = (u_int64_t) ft_atoi(argv[3]);
	table->time_to_sleep = (u_int64_t) ft_atoi(argv[4]);
	table->stop = 0;
	if (argv[5])
		table->max_eat = ft_atoi(argv[5]);
	else
		table->max_eat = -1;
	pthread_mutex_init(&(table->lock), NULL);
	pthread_mutex_init(&(table->print), NULL);
	if (init_forks(table) || init_philos(table))
		return (1);
	return (0);
}
