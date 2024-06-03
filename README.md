# Philosopher's Dining Problem

## Problem Statement

The Dining Philosophers problem is a classic synchronization problem that involves philosophers who do nothing but think, eat, and sleep. They sit around a circular table with a bowl of spaghetti in the center and n (number of philosophers) forks placed between them. To eat, a philosopher needs to pick up both the fork on their left and the fork on their right. However, each fork can only be held by one philosopher at a time, leading to potential deadlocks and resource starvation.

## Solution Overview

To address the potential deadlock scenario, my solution implements an offset mechanism. Specifically, philosophers with odd IDs are delayed at the beginning, allowing even-ID philosophers to pick up forks first. This staggering of start times helps prevent a scenario where all philosophers simultaneously pick up the fork on their right and wait indefinitely for the fork on their left.

### Key Components

1. **Mutexes for Forks:** Each fork is protected by a mutex to ensure that only one philosopher can hold it at a time.
2. **Mutexes for Shared Resources:**
   - **Printing:** A mutex to ensure that console outputs (e.g., status updates) do not get garbled when multiple threads attempt to print simultaneously.
   - **Meal Count:** A mutex to safely update and check the number of meals each philosopher has eaten.
   - **Death Flag:** A mutex to safely check if any philosopher has died, ensuring the termination of the simulation.
3. **Staggered Start for Philosophers:** Philosophers with odd IDs start with a delay, preventing them from picking up their forks immediately. This avoids the deadlock condition where all philosophers pick up their left fork and wait for the right fork.

### Threading in the Simulation

#### What are Threads?

Threads are the smallest unit of execution within a process. They allow multiple operations to be performed concurrently within a single process. In the context of the Dining Philosophers problem, each philosopher is represented as a separate thread. This allows each philosopher to think, eat, and sleep independently and concurrently with the others.

#### Why Use Threads?

Using threads in this simulation enables parallelism, which is crucial for modeling real-world concurrent systems. Each philosopher (thread) can perform actions simultaneously, which more accurately represents the problem scenario where philosophers independently think, eat, and sleep.

### Detailed Implementation

#### Initialization
1. Create and initialize mutexes for each fork.
2. Create mutexes for shared resources (printing, meal count, death flag).
3. Initialize philosopher threads, assigning an ID to each.

#### Philosopher Behavior
1. **Thinking:** Each philosopher (thread) spends a random amount of time thinking.
2. **Eating:** 
   - Philosophers with odd IDs wait for an initial delay.
   - Pick up the left fork (acquire the left fork mutex).
   - Pick up the right fork (acquire the right fork mutex).
   - Eat for a random amount of time.
   - Release the left fork (release the left fork mutex).
   - Release the right fork (release the right fork mutex).
3. **Printing Status:** Use the print mutex to safely print the philosopher's status.
4. **Meal Count:** Use the meal count mutex to safely update and check the meal count.
5. **Death Check:** Use the death flag mutex to safely check if any philosopher has died.

### Advantages of the Solution

- **Deadlock Avoidance:** By staggering the start times of odd-ID philosophers, we avoid the deadlock scenario where all philosophers are waiting for the fork on their left.
- **Data Race Prevention:** The use of mutexes for forks and shared resources ensures that there are no data races, leading to a correct and safe execution of the program.
- **Efficient Resource Utilization:** Threads allow for efficient use of system resources by enabling parallel execution of tasks.

## Usage

To run the simulation, use the following command:

```sh
./philo philo_count time_to_die time_to_eat time_to_sleep[number_of_times_each_philosopher_must_eat]
```

- **`philo_count`**: The number of philosophers (and forks).
- **`time_to_die`**: The maximum time (in milliseconds) a philosopher can go without eating before dying.
- **`time_to_eat`**: The time (in milliseconds) it takes for a philosopher to eat.
- **`time_to_sleep`**: The time (in milliseconds) a philosopher spends sleeping after eating.
- **`number_times_each_philosopher_must_eat`**: (optional argument) If all philos have at least eaten number_of_times_each_philosopher_must_eat the simulation stop. If not specified the simulation stops when a philosopher dies.

### Example

```sh
./philo 5 800 200 200 7
```

This command starts a simulation with 5 philosophers, where each philosopher will die if they do not eat within 800 milliseconds, takes 200 milliseconds to eat, and sleeps for 200 milliseconds after eating. If every philo has at least eaten 7 times or if a philo dies before that the simulation stops.

## Conclusion

This solution effectively handles the classic Dining Philosophers problem by introducing an offset to avoid deadlocks and employing mutexes to prevent data races. The staggered start time for philosophers with odd IDs ensures that resource acquisition is more orderly, thereby preventing the simultaneous grabbing of forks and the resultant deadlocks. By leveraging threading, the simulation accurately models the concurrent behavior of philosophers, demonstrating efficient synchronization and resource management techniques.
