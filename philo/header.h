#ifndef HEADER_H
# define HEADER_H
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# define LAST_ARG_PRESENT 1
# define LAST_ARG_MISSING 0
# define NO_ERRORS_DETECTED 1
# define ERROR_DETECTED -1
# define PHILO_DEATH 11
# define MIN_MEAL_REACHED 12
# define GAME_ARGS 0
# define MALLOC_ERROR "no_allocation"

typedef struct s_checkers
{
	pthread_t			min_meal;
	pthread_t			death;
	pthread_mutex_t		lock_1;
	int					notification;
	ssize_t				start_time;
}				t_checkers;

typedef struct s_argv
{
	long	number_of_philosophers;
	long	number_of_forks;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	last_arg_presence;
	long	number_of_times_each_philosopher_must_eat;
}				t_argv;

typedef struct s_philo_data
{
	int				philo_index;
	int				philo_fork_1;
	int				philo_fork_2;
	int				meal_counter;
	int				last_meal_timestamp;
	int				next_meal_timestamp;
	pthread_mutex_t	*forks;
	t_argv			*game_args;
	t_checkers		*checker;
}				t_philo_data;

long			ft_atoi(char	*src);
t_argv			*fetch_args(int	argc, char	**argv);
int				check_ints(char	*str);
int				argv_error_handling(int	argc, char	**argv);
int				last_check(t_argv	*game_args);
int				main(int	argc, char	**argv);
void			set_philo_data(t_philo_data	*data, t_argv	*game_args,
					pthread_mutex_t	*fork, t_checkers		*checker);
pthread_mutex_t	*forks_init(t_argv	*game_args);
void			print_status(char	*str, t_philo_data	*data);
void			deploy_philosophers(t_argv	*game_args,
					pthread_t	*philosophers, t_philo_data	*data);
void			*entry_point(void	*ptr);
ssize_t			get_current_time_micro_seconds(void);
void			checker_wave_deployment(t_philo_data	*data,
					pthread_t	*min_meal, pthread_t	*death);
void			*checker_death(void	*ptr);
void			*checker_meal(void	*ptr);
void			join_the_bunch(pthread_t	*philosophers,
					t_argv	*game_args);
void			my_sleep(long	time);

int				game_args_error(void);
int				invalid_value_error(t_argv	*game_args);
int				philo_malloc_err(t_argv	*game_args);
int				philos_data_malloc_err(t_argv	*game_args,
					pthread_t	*philosophers);
int				un_init_forks(t_philo_data	*philos_data, t_argv	*game_args,
					pthread_t	*philosophers, t_checkers	*check);
void			detach(t_philo_data	*philos_data, pthread_t	*philosophers);
void			destroy(t_philo_data	*philos_data, t_checkers	*check);
int				infinite_loop(t_argv	*game_args, pthread_t	*philosophers,
					t_philo_data	*philos_data, t_checkers	*check);
int				last_three(t_argv	*game_args, pthread_t	*philosophers,
					t_philo_data	*philos_data, t_checkers	*check);
int				settings(t_philo_data	*philos_data, t_argv	*game_args,
					pthread_t	*philosophers, t_checkers	*check);
size_t			skip(size_t	i, char	*src, int	*s);

#endif