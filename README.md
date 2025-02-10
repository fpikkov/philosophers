#PHILOSOPHERS

##<ins>OVERVIEW</ins>
This project tackles the classical Dining Philosopher's Problem utilizing threads and mutexes (mutual exclusions) written in the C programming language.
The project attempts to avoid common pitfalls such as deadlocks and race condiitons. The goal is to simulate a scneario where a given number of philosophers sit around a table and alternate between eating, sleeping and thinking.
Each philosopher will attempt to pick up forks (mutexes) and eat their meal for a given amount of time in milliseconds before continuing with their cycles.

##<ins>USAGE</ins>
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
