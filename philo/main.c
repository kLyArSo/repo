#include "header.h"

int	settings(t_philo_data	*philos_data, t_argv	*game_args
, pthread_t	*philosophers, t_checkers	*check)
{
	t_sidestep		*var;

	var = sidestep_managment(NULL, FETCH);
	set_philo_data(philos_data, game_args, forks_init(game_args));
	if (philos_data->forks == NULL)
		return (un_init_forks(philos_data, game_args, philosophers));
	else
		last_three(game_args, philosophers, philos_data, check);
	return (0);
}

size_t	skip(size_t	i, char	*src, int	*s)
{
	while ((src[i] >= 9 && src[i] <= 13) || (src[i] == 32))
		i++;
	if (src[i] == '+')
		i++;
	else if (src[i] == '-')
	{
		*s = -1;
		i++;
	}
	return (i);
}

t_sidestep	*sidestep_managment(t_sidestep *vari, int	action)
{
	static t_sidestep *var;
	if (action == INIT)
	{
		var = vari;
		var->start_time = get_current_time_micro_seconds();
		pthread_mutex_init(&var->lock_1, NULL);
	}
	else if (action == FETCH)
		return ((t_sidestep	*)var);
	else if (action == FREE)
		free(var);
	return (NULL);
}
int	main(int	argc, char	**argv)
{
	t_argv			*game_args;
	pthread_t		*philosophers;
	t_philo_data	*philos_data;
	t_checkers		*check;
	t_sidestep		*var;

	var = malloc(sizeof(t_sidestep));
	if (var == NULL)
		return (ERROR_DETECTED);
	sidestep_managment(var, INIT);
	check = NULL;
	if (argv_error_handling(argc, argv) == ERROR_DETECTED)
		return (ERROR_DETECTED);
	game_args = fetch_args(argc, argv);
	if (game_args == NULL)
		return (game_args_error());
	if (last_check(game_args) == ERROR_DETECTED)
		return (invalid_value_error(game_args));
	philosophers = malloc(game_args->number_of_philosophers
			* sizeof(pthread_t));
	if (philosophers == NULL)
		return (philo_malloc_err(game_args));
	philos_data = malloc(game_args->number_of_philosophers
			* sizeof(t_philo_data));
	if (philos_data == NULL)
		return (philos_data_malloc_err(game_args, philosophers));
	settings(philos_data, game_args, philosophers, check);
	return (0);
}

