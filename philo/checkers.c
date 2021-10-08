#include "header.h"

void	*checker_meal(void	*ptr)
{
	t_philo_data	*data;
	int				i;
	int				nbr_of_philo;
	t_sidestep		*var;

	var = sidestep_managment(NULL, FETCH);
	data = (t_philo_data *)ptr;
	nbr_of_philo = data->game_args->number_of_philosophers;
	while (1)
	{
		i = 0;
		while (i < nbr_of_philo)
		{
			if (data[i].meal_counter
				>= data[i].game_args->number_of_times_each_philosopher_must_eat)
				i++;
			else
				break ;
		}
		if (i == nbr_of_philo)
			break ;
	}
	pthread_mutex_lock(&var->lock_1);
	var->notification = MIN_MEAL_REACHED;
	return (NULL);
}

void	norm_func(int	i, t_sidestep	*var)
{
	print_status("died", i);
	pthread_mutex_lock(&var->lock_1);
	var->notification = PHILO_DEATH;
}

int	check_loop(int	nbr_of_philo, t_philo_data	*data, t_sidestep	*var)
{
	int				current_timestamp;
	int				i;

	while (1)
	{
		i = 0;
		while (i < nbr_of_philo)
		{
			current_timestamp = (get_current_time_micro_seconds()
					- var->start_time) / 1000;
			if (current_timestamp < data[i].next_meal_timestamp)
				i++;
			else
				break ;
		}
		if (i == nbr_of_philo)
			continue ;
		else
			break ;
	}
	return (i);
}

void	*checker_death(void	*ptr)
{
	t_philo_data	*data;
	int				i;
	int				nbr_of_philo;
	t_sidestep		*var;

	var = sidestep_managment(NULL, FETCH);
	data = (t_philo_data *)ptr;
	nbr_of_philo = data->game_args->number_of_philosophers;
	i = check_loop(nbr_of_philo, data, var);
	norm_func(i, var);
	return (NULL);
}

void	checker_wave_deployment(t_philo_data	*data
			, pthread_t	*min_meal, pthread_t	*death)
{
	if (data->game_args->last_arg_presence == 1)
		pthread_create(min_meal, NULL, checker_meal, (void *)data);
	pthread_create(death, NULL, checker_death, (void *)data);
}
