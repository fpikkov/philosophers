# PHILOSOPHERS

## OVERVIEW

This project tackles the classical Dining Philosopher's Problem utilizing threads and mutexes (mutual exclusions) written in the C programming language.
The project attempts to avoid common pitfalls such as deadlocks and race condiitons. The goal is to simulate a scneario where a given number of philosophers sit around a table and alternate between eating, sleeping and thinking.
Each philosopher will attempt to pick up forks (mutexes) and eat their meal for a given amount of time in milliseconds before continuing with their cycles.

### USAGE

Download the repository to your system:
```
git clone https://github.com/fpikkov/philosophers.git
```
Change to the philo directory and make the project:
```
cd philosophers/philo && make
```
Run the executable with arguments with times given in milliseconds:
```
./build/philo [number of philosophers] [time to die] [time to eat] [time to sleep]
```
Optionally give the amount each philosopher should eat before ending the simulation:
```
./build/philo [number of philosophers] [time to die] [time to eat] [time to sleep] [amount to eat]
```

### EXAMPLES

The following cases should run indefinitely:
```
./build/philo 5 800 200 200
./build/philo 3 800 200 200 7
./build/philo 200 180 60 60
```
The following cases WILL NOT run indefinitely:
```
./build/philo 10 500 500 500
./build/philo 1 600 100 100
./build/philo 10 -2468 0 0
./build/philo 0 3000 500 500
./build/philo abc 3000 500 500
```
