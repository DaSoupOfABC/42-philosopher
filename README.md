# 42-philosopher
*This project has been created as part of the 42 curriculum by jenlee*

## Description
Philosopher is a computer science project that involves a table with spaghetti in the centre. Philosophers each have one single fork, and must share forks with their neighbours, requiring 2 forks to eat. When a Philosopher finishes eating, they place the fork back and go to sleep. Once awake, they start thinking until they need to eat again. 

Every Philosopher needs to eat and shouldn't starve
Philosophers have no contact with each other
Philosophers will have no way to know if another Philosopher is going to die

Our goal is to make an "algorithm" that allows all of them to go through this cycle without dying.

## Instructions
### Compilation
To use the program, first run the following command in the directory with the Makefile.
```
make
```
If a version of Philo already exists, update it to  the latest version via
```
make re
```
### Usage
To run the Philo program, run the following
```
./philo #Number_Of_Philo #Time_To_Die #Time_To_Eat #Time_To_Sleep #Number_Of_Times_To_Eat
```
Where
1. #Number_Of_Philo -> Number of Philo desired (Preferrably lower than 200)
2. #Time_To_Die -> Amount of Time to eat before dying
3. #Time_To_Eat -> Amount of Time required to finish eating
4. #Time_To_Sleep -> Amount of time required to sleep after eating
5. #Number_Of_Times_To_Eat(Optional) -> Optional setting to limit how many times a Philosopher can eat.

## Resources
1. Testing: https://github.com/dantonik/42-philosophers-tester
2. AI Usage: Extra test edge cases, as well as basic Threads knowledge and theory
3. Google (No specific website, though can primarily attribute to Stack Overflow and Wikipedia)




