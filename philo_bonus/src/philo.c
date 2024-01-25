/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessie <jessie@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 14:18:28 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/18 10:57:38 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
// even: time_to_die = time_to_eat + time_to_sleep +10
// odd: time_to_die = time_to_eat * 2 + time_to_sleep + 10

/* join all the thread before destroy all the mutex!!! */
void	end_table(t_table *table)
{
	int		i;
	pid_t	pid;

	i = -1;
	pid = waitpid(-1, NULL, 0);
	while (++i < table->num)
	{
		if (table->philos[i].pid != pid)
			kill(table->philos[i].pid, SIGKILL);
	}
	sem_close(table->forks);
	sem_close(table->print);
	sem_close(table->dead);
	free(table->philos);
}

int	start_table(t_table *table)
{
	int	i;

	i = -1;
	table->start_time = get_time();
	while (++i < table->num)
	{
		table->philos[i].pid = fork();
		if (table->philos[i].pid == -1)
		{
			while (--i >= 0)
				kill(table->philos[i].pid, SIGKILL);
			return (free(table->philos), error("fork failed"));
		}
		if (table->philos[i].pid == 0)
		{
			routine((void *)&table->philos[i]);
			exit(0);
		}
	}
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
