# Philosophers - My Threading Simulation
<img width="1544" height="793" alt="Philosophers" src="https://github.com/user-attachments/assets/32a6ba51-ee7b-4439-b33c-c0e0d9e62d75" />

*My multithreading and synchronization project*
---
## What is this?
**Philosophers** is a simulation of the dining philosophers problem that I wrote myself. It's a school project that helps me learn how threads work, how to prevent deadlocks, and how to manage shared resources safely. I'll use these threading skills in other projects later.

---

## What I Built

### Threading Components
- **Philosophers**: Each philosopher runs as a separate thread
- **Forks**: Mutexes that prevent race conditions
- **Actions**: Eating, thinking, sleeping with proper timing

### Synchronization Features
- **Deadlock Prevention**: Smart fork picking strategies
- **Race Condition Control**: Mutex protection for shared data
- **Timing Management**: Precise timing for all actions

### Simulation Features
- `Multiple philosophers`: Handle 1-200 philosophers at once
- `Death detection`: Monitor if philosophers starve
- `Meal counting`: Track how many times each philosopher eats

---

## Usage  

1. **Clone the repository**:  
   ```bash  
   git clone https://github.com/mkatfi/philosophers.git  
   cd philosophers/philo
   ```  

2. **Compile the program**:  
   ```bash  
   make  
   ```  

3. **Run the simulation**:  
   ```bash  
   ./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat (optional)]  
   ```  

   - `number_of_philosophers`: Number of philosophers at the table.  
   - `time_to_die`: Time (in ms) before a philosopher dies if they don’t start eating.  
   - `time_to_eat`: Time (in ms) it takes for a philosopher to eat.  
   - `time_to_sleep`: Time (in ms) a philosopher spends sleeping.  
   - `number_of_times_each_philosopher_must_eat`: Optional parameter to stop the simulation when each philosopher has eaten this many times.  

4. **Example**:  
   ```bash  
   ./philosophers 5 800 200 200  
   ```  

### Usage Example
Run with: `./philosophers [num_philos] [time_to_die] [time_to_eat] [time_to_sleep] [optional_meal_count]`

Example: `./philosophers 5 800 200 200` - 5 philosophers, die in 800ms, eat for 200ms, sleep for 200ms

---

## Who made this
Made by **mouadisfree** as a student at **1337 School** (part of the 42 coding schools).

---

## Thanks
Thanks to 1337 School and all my peers who helped me learn!
