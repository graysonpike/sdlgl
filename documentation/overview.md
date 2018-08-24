
# Overview
Documentation for Version 1.0


### Structure of a SDLGL Game
* SDLGL games are C++ programs which execute **Scenes**.
* Scenes contain zero or more **Entities**, which are updated and rendered each frame.
* Entities are things in the game world, such as players, props, NPC’s, particles, physics objects, etc.
* Each scene has a reference to the **Graphics** and **Inputs**.
* Graphics is a class controlling **Resources**, the **Rendering Context**, the **Font Renderer**, an **FPS Counter**, and the **Window Reference**.
* In an SDLGL game, most of the game logic is contained in classes which extend Entity.
* Each entity has a reference to its Scene. The entity can interact with Graphics, Inputs, and other Entities via its parent Scene.
