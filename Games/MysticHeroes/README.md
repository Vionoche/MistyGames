# About

The project is for learning the Entity Component System (ECS) pattern. This is just a simple console application, when player can type ID of a monster to hit. Monsters can attack the player too. There are not any balance in the game.

To sum up, ECS quite interesting pattern, and it was easy to start with ECS for me. There is a little the infrastructure code in the project, and there was easy to add new systems as well.
For instance, I like how monster entities are created by code - just adding all necessary components and it works.

The ECS requires a fast data storage mechanism, because every system has to look for the components every processing time. Additionaly, there are many insert/delete operations for the components when an attack occurs or a monster dies. This technique is not implemented in the project right now.
The debug has a difficulty too, because the component arrays seem very messy.
