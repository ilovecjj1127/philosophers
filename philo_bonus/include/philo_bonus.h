/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessie <jessie@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 12:19:35 by jiajchen      #+#    #+#                 */
/*   Updated: 2024/01/18 13:35:50 by jiajchen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>		//printf
# include <string.h>	//memset
# include <stdlib.h>	//malloc free
# include <unistd.h>
# include <pthread.h>	//pthread
# include <sys/time.h>	//gettimeofday
# include <sys/types.h> 	//u_int64_t
# include <unistd.h>	//usleep write
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

/* state message */
# define FORK		"has taken a fork"
# define EAT		"is eating"
# define SLEEP		"is sleeping"
# define THINK		"is thinking"
# define DIE		"died"

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

struct s_philo
{
	int				id;
	int				meal_num;
	u_int64_t		last_eat;
	pid_t			pid;
	pthread_t		monitor;
	pthread_mutex_t	lock;
	t_table			*table;
};

struct s_table
{
	int				num;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	int				max_eat;
	u_int64_t		start_time;
	t_philo			*philos;
	sem_t			*dead;
	sem_t			*print;
	sem_t			*forks;
};

int			init_table(t_table *table, char **argv);
int			error(char *str);

void		*routine(void *param);
void		*monitor(void *param);

int			print_msg(t_philo *philo, char *str);
u_int64_t	get_time(void);
void		ft_usleep(u_int64_t time);
int			ft_atoi(const char *nptr);
void		end_table(t_table *table);
void		stop_table(t_table *table);
int			is_stop(t_table *table);
int			check_full(t_philo *philo);
int			check_die(t_philo *philo);

#endif