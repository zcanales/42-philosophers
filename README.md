# Philosphers 🍝
The aim of this project is to learn about multithreading, multiprocessing, mutex and semaphore.

## Description 📃
Philosophers are sit around a circular table, with a big plate of spaghetti at its center. Each philospher has his own fork, but they need two forks to eat, so they need to borrow their neighbor's fork to eat.
The philosophers alternatively eat, think, or sleep. While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping; and, of course, while sleeping, they are not eating nor thinking.

There are two programs:
- First Program (Mandatory Part):
  - Each philosopher should be a thread.
  - One fork between each philosopher, therefore if they are multiple philosophers, there will be a fork at the right and the left of each philosopher.
  - To prevent philosophers duplicating forks, I should protect the forks state with a mutex for each of them.
- Second Program (Bonus Part):
  - All the forks are put in the middle of the table..
  - They have no states in memory but the number of available forks is represented by a semaphore.
  - Each philosopher should be a process and the main process should not be a philosopher.

## Execution 🕹
The program take the following arguments:
[number_of_philosophers] [time_to_die] [time_to_eat] [time to_sleep]
[number_of_times_each_philosopher_must_eat]
- number_of_philosophers: The number of philosophers and also the number
of forks.
- time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
- time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
- number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

Example:
- Mandatory part directory: ``` philo/ 4 410 200 200 2 ```
- Bonus part directory: ``` philo_bonus/ 4 410 200 200 2 ```
