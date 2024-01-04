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

# Uno Architecture
In this project, all classes are derived from `Entity` and they have the lifecycle handled by the Core library.

Some guides for the classes used in this project:

## License
- GNU GENERAL PUBLIC LICENSE for this repository (see `LICENSE.txt` for more details)
- Premake is licensed under BSD 3-Clause (see included `LICENSE.txt` file in `Vendor` directory for more details)