# Pacman-Game

![gamelook](https://raw.githubusercontent.com/ngnw/Pacman-Game/main/gamelook.PNG)

## Installation

Follow Makefile compiler guidelines to get your machine ready to run program.

```bash
make main
./main
```

## Game Play

In main.cpp you can fill in the player name you desire and increment the number of enemies and decide there starting positions. Once the game starts you will be prompted to enter in a position you'd like your pacman to assume. The rules of the game are as follows:

- Collect all the yellow squares 🟨 to win the game
- The green cross squares ❎ are walls
- If you run into an enemy 👻 you will lose a life
- If you aquire a powerup 🎁 you can destroy an enemy and respawn them elsewhere
- If the enemy aquires a powerup 🍒 they gain immunity from destruction
- If you run into the fire 🔥 you lose a life

Player Looks: 
😁 No powerup;
😇 Aquired powerup;
👻 No powerup;
💀 Aquired powerup
