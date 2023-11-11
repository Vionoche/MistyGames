# About

While I was learning the Entity Component System (ECS) pattern I heard about Godot Engine (https://godotengine.org/), I tried it and I like it and its node system.
So, this project is my experimenting with the node system from the Godot. That is why all fundamental clasess and objects have the same names as in the Godot.

First time it was a little bit difficult to start with it if we are comparing with the ECS pattern. And initial infrastructure code is more bigger then the ECS one, especially, when I had to build the signals system with observer pattern.

Then I got my fisrt fruits of using the node system. The code has become more clearer and there is no mess anymore. Every node has relations with its own compoments.
It is easy to manage nodes as a tree - you can build a monster, and put it into a level, and then put the level into the game node. The game node can manipulate all these level nodes to allow change them. The level node can manage monster and player nodes and so on.

Also, it should be a good idea to mix the both ECS and nodes patterns together. For instance, the level node may be like the world class from ECS pattern and it can store an array of components.
The other nodes inside the level node are entites and systems which can use the common array of components (which stores into the level node).
