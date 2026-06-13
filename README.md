# Minigin
# GIT Repository
https://github.com/jorritDelanghe/DelangheJorrit-Exam-Project-assignment

# Engine Specifics
GameObject:
I used a GameObject class that all my objects inherit from, and I keep a list of these in my scene that I just loop through. Every object in the game gets the same base, which is very handy since it lets me treat everything in a uniform way without writing separate logic for each object type. I chose to give my gameObject a position in the gameobject class. This means it can move standard in the scene without a transform component.

Observer / Subject:
I used the Observer and Subject pattern to create a system that decouples my code: something signals that an event happened, and then the right observer reacts to it. This way different systems don't need to know about each other directly, they just respond to the events they care about.

Component System:
My component system helps me give functionality to my GameObjects through object composition. It gives me very flexible, reusable building blocks that can be shared between different GameObjects, instead of having to rewrite the same logic for every object type.

Command Pattern:
My Command interface helps me create reusable commands that can be picked up by my InputManager. This way an action isn't tied to a specific key or button, the InputManager just executes whatever command is bound to an input. The Digger game has a gameObjectCommand. This is inherits from my command, and that points safely to the gameObject if needed.

Service Locator:
My ServiceLocator owns my sound system. The main benefit is that it gives global access to the sound system without needing to pass it around everywhere, and it lets me swap out the actual implementation (for example a "null" sound service vs the real one) without changing the code that uses it.

Singleton:
The Singleton pattern was already in my engine, but it's very handy when something needs to be global and there should only ever be one of it. You have to be careful not to overuse it though, since it's global and that can make things harder to manage if too many systems depend on it.

Collision System:
I kept my collision system out of the engine itself, since it relies on a lot of 2D-specific logic. Keeping it in the game project instead means the engine stays generic and reusable for other types of games.

# Starting of Minigin
Minigin is a very small project using [SDL3](https://www.libsdl.org/) and [glm](https://github.com/g-truc/glm) for 2D c++ game projects. It is in no way a game engine, only a barebone start project where everything sdl related has been set up. It contains glm for vector math, to aleviate the need to write custom vector and matrix classes. This was the starting point of my project

[![Build Status](https://github.com/avadae/minigin/actions/workflows/cmake.yml/badge.svg)](https://github.com/avadae/cmake/actions)
[![Build Status](https://github.com/avadae/minigin/actions/workflows/emscripten.yml/badge.svg)](https://github.com/avadae/emscripten/actions)
[![GitHub Release](https://img.shields.io/github/v/release/avadae/minigin?logo=github&sort=semver)](https://github.com/avadae/minigin/releases/latest)

## When building on top of this:
## Emscripten (web) version

### On windows

For installing all of the needed tools on Windows I recommend using [Chocolatey](https://chocolatey.org/). You can then run the following in a terminal to install what is needed:

    choco install -y cmake
    choco install -y emscripten
    choco install -y ninja
    choco install -y python

In a terminal, navigate to the root folder. Run this: 

    mkdir build_web
    cd build_web
    emcmake cmake ..
    emmake ninja

To be able to see the webpage you can start a python webserver in the build_web folder

    python -m http.server

Then browse to http://localhost:8000 and you're good to go.

### On OSX

On Mac you can use homebrew

    brew install cmake
    brew install emscripten
    brew install python

In a terminal on OSX, navigate to the root folder. Run this: 

    mkdir build_web
    cd build_web
    emcmake cmake .. -DCMAKE_OSX_ARCHITECTURES=""
    emmake make

To be able to see the webpage you can start a python webserver in the build_web folder

    python3 -m http.server

Then browse to http://localhost:8000 and you're good to go.

## Github Actions

This project is build with github actions.
- The CMake workflow builds the project in Debug and Release for Windows and serves as a check that the project builds on that platform.
- The Emscripten workflow generates a web version of the project and publishes it as a [github page](https://avadae.github.io/minigin/). 
  - The url of that page will be `https://<username>.github.io/<repository>/`
- You can embed this page with 

```<iframe style="position: absolute; top: 0px; left: 0px; width: 1024px; height: 576px;" src="https://<username>.github.io/<repository>/" loading="lazy"></iframe>```

