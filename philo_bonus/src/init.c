/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessie <jessie@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 20:10:43 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/25 11:48:00 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	error(char *str)
{
	printf("%s\n", str);
	return (1);
}

void	close_sems(t_table *table)
{
	if (table->dead)
		sem_close(table->dead);
	if (table->forks)
		sem_close(table->forks);
	if (table->print)
		sem_close(table->print);
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
	}
	return (0);
}

int	init_sems(t_table *table)
{
	sem_unlink("dead");
	sem_unlink("print");
	sem_unlink("forks");
	table->dead = sem_open("dead", O_CREAT, 0644, 1);
	table->print = sem_open("print", O_CREAT, 0644, 1);
	table->forks = sem_open("forks", O_CREAT, 0644, table->num);
	if (table->dead == SEM_FAILED || table->print == SEM_FAILED
		|| table->forks == SEM_FAILED)
		return (close_sems(table), error("semaphores failed"));
	sem_unlink("dead");
	sem_unlink("print");
	sem_unlink("forks");
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
	if (argv[5])
		table->max_eat = ft_atoi(argv[5]);
	else
		table->max_eat = -1;
	if (init_sems(table) || init_philos(table))
		return (1);
	return (0);
}
