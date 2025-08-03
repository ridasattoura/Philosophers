#include <philo_bonus.h>

static int	display_error(void)
{
	write(2, "Error! invalid arguments\n", 26);
	return (1);
}

int	main(int argc, char *argv[])
{
	int			i;
	t_dining_table	table;

	if ((argc < 5 || argc > 6) || validate_arguments(argc, argv, &table))
		return (display_error());
	table.start_time = get_current_time();
	i = -1;
	while (++i < table.philo_count)
	{
		table.philosophers[i].process_id = fork();
		if (table.philosophers[i].process_id == -1)
		{
			write(2, "Error! fork failed\n", 19);
			exit(1);
		}
		if (table.philosophers[i].process_id == 0)
			philosopher_routine((void *)&table.philosophers[i]);
	}
	cleanup_and_exit(&table);
	return (0);
}
