# OS Assignment

## Cigarette-Smokers-Problem

The task was that there are 3 ingredients:
1. Tobacco
2. Matches
3. Paper

There are 4 threads:
- Agent with all Three
- Smoker with Tobacco
- Smoker with Match
- Smoker with Paper

Agent randomly spawns 2 ingredients and only the smoker who needs both ingredients should pick and smoke

## Producer Consumer Problem

Producer checks if the buffer is not full and produces an item which on the other hand Consumer checks whether there is an item on the buffer for consumption.
I've used semaphores to enforce synchronization on resource sharing.
