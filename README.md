# Plox
An implementation of the `lox` learning language from the [Crafting Interpreters Handbook](https://www.craftinginterpreters.com).
This is meant to be a C++ implementation of `jlox` from Part I of the book.

## Building
* Install `meson` (version 0.50.0 or higher)
* Run `meson build` in the project root directory. This creates a new directory named `build`.
* Run `meson compile -C build`. 

## Running
After following the build instructions above, simply run `./build/plox`. If you do not 
provide any arguments then `plox` enters REPL mode. If you provide the name of a script
file then it will be loaded and run.
