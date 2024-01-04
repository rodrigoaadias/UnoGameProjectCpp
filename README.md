# Uno Game

Uno Game is a project developed as part of a **C++ Training** at **Kokku**.

In the following sections you will see how to setup this project in your machine and how the project is working.

# Setup Project in your machine
This project uses a Core/App project architecture template developed by [The Cherno](https://github.com/TheCherno/ProjectTemplate). There are two included projects - one called _Uno-Core_, and one called _Uno-App_. [Premake](https://github.com/premake/premake-core) is used to generate project files.

Uno-Core builds into a static library and is meant to contain common code intended for use in multiple applications. Uno-App builds into an executable and links the Core static library, as well as provides an include path to Core's code.

The `Scripts/` directory contains build scripts for Windows and Linux, and the `Vendor/` directory contains Premake binaries (currently version `5.0-beta2`).

## Getting Started
1. Clone this repository
2. The three included Premake build files are `Build.lua`, `Uno-Core/Build-Core.lua` and `Uno-App/Build-App.lua` - these files were edited to fit the Uno Game project. Please do not change these files.
3. Open the `Scripts/` directory and run the appropriate `Setup` script to generate projects files. Out of the box they are set to Visual Studio 2022 for Windows and gmake2 for Linux.

Note that no macOS setup script is currently provided; you can duplicate the Linux script and adjust accordingly.

# Guidelines
These guidelines will help you to understand how to write new code to this project and how the code is actually being managed.

## Naming Conventions
Some of the most common cases are listed below:

|            **Type**             | **Convention** |
|:-------------------------------:|:--------------:|
|      Classes/Structs names      |   PascalCase   |
|           Enums names           |  EPascalCase   |
|     Methods/Functions names     |   PascalCase   |
|         Private fields          |   PascalCase   |
|        Protected fields         |   PascalCase   |
|       Methods parameters        |   camelCase    |
|         Local variables         |   camelCase    |
|        Global variables         |   UPPER_CASE   |
| Interfaces (Abstracted classes) |  IPascalCase   |
|           Namespaces            |   PascalCase   |

Feel free to suggest a naming convention for any other case not listed above.

## Comments
Avoid comments as much as possible.
Comments, such as code, needs to be maintainable, and can be often forgotten outdated. That's the reason they should be avoided. The code must be clear an self-explained, favouring readability. Clean code practices will help reach this goal.
Acceptable comments are:

* Summaries on public methods that are meant to be used by other developers (such as a plugin or service)
  * Do not use extensively. If the method is self-explanatory, there’s no need for a summary
* Brief explanation of complex algorithms that are very hard to understand

# Project Architecture

## Uno-Core
The Uno-Core library must be used as a tool to help developers to create entities that must have a lifecycle and routines like `Begin()` and `Tick()`.

### Entity
Entity is anything in the game that should be instantiated and receive `Begin` and `Tick` calls.

If your class is an entity that has a Lifetime cycle and can be destroyed anytime in the game, make this class always derive from `Core::Entity`.

### Create entity object
Use the static call `Engine::CreateEntity<TEntityType>()` to create a new object of that class.

Using `Engine::CreateEntity<TEntityType>` will register the entity to receive `Begin()` and `Tick()` calls and it will return a handle class called `EntityPtr<TEntityType>`.

### EntityPtr
The `EntityPtr` is a core functionality of this project. This handle makes all memory allocations easier. It manipulates the object created in a shared pointer, that can be destroyed any time in your code. It also has a `IsValid()` method to check if the object is still alive.

The `EntityPtr` can be copied along the code many times, and when you destroy the `Entity` that the `EntityPtr` handles, all `EntityPtr` objects will know that the `Entity` is destroyed. It is helpful to handle with situations that an object doesn't exist anymore.

If a null ref of your entity is expected to happen in some situation, a good approach is to use `IsValid()` check to ensure that your Entity is still alive and don't get an undesired null pointer exception.

### Destroy entities
Use the static method `Engine::Destroy(EntityPtr<Entity>& entityToRemove)` to destroy an entity. It will erase your entity from memory.

EntityPtr also knows when the Entity is out of scope and automatically deletes it from memory. It has the same functionality as `shared_ptr` that deletes an object from memory when out of scope.

With this in mind, you can safely uses `EntityPtr` across your code and be sure that it will be destroyed at least at the end of the game execution.

## Uno Architecture
In this project, all classes are derived from `Entity` and they have the lifecycle handled by the Core library.
For more information about the project architecture, please check the UML diagram images files inside `Documentation` directory.

### GamelifycycleController
This is the controller responsible for creating a match and handle restart match options

### Match
Creates and manage all classes and objects used in a match, like players, cards and turns.

### Round
This is the class that handle how a round must be played. We have some derived rounds, like `JumpRound` that forces player skip its turn.

### DeckController
It creates all cards that will be used in the game. It manage the deck cards, the discard pile and also shuffle cards when needed.

### Player
This class represents a player in the game. It store the cards player has in hand, how to play a turn, the yell conditions, and the play options.

### Card
It's the base class that represents a card in the game. All cards in this game must be derived from `Card`. It also have some static functions to help draw the card in the Console.

## How-to
### Create a new Card type
If you want to add a new card type to this project, with a specific behavior, you need to do the following steps:
* Make the class derive from `Card`.
* Implement the pure virtual methods.
* If you have any specific rule to check if a card can be tossed on it, you can override the method `CanTossCardOnMe(const EntityPtr<Card>& other)`
* If your card is a special card that change some behavior in the normal round flow, you have two options to implement it, based on what the card will do.
    * **If the card must change a post round behaviour:** make this card also extends from interface `IPostRoundAction` and then implement what kind of action it must do. Examples of this usage: Switch Hand and Reverse cards. Both cards apply an action that must be done immediately after the player toss the card.
    * **If the card must change the round:** make this card also extends from interface `ICustomRoundCard` and then return which round should be run for that turn. Examples of this usage: Jump and +2 cards. These both cards change the behavior of the next round, or in other words, how the round will be executed. Both rounds is not a normal round that a player can select a card to toss.
    * You can implement both interfaces if needed.
* In `DeckController`, add the logic to create the amount of the new cards that should be added in the deck inside the method `CreateCards()`
* That's it, your card is ready to be used in the game.

### Create a custom Round
In some cases, a card can change how the next round will behave. This is very common in a Uno game. Situations that need it is when a player toss a Jump card for example. The next player must skip its turn.

## License
- GNU GENERAL PUBLIC LICENSE for this repository (see `LICENSE.txt` for more details)
- Premake is licensed under BSD 3-Clause (see included `LICENSE.txt` file in `Vendor` directory for more details)