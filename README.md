# Plox
An implementation of the `lox` learning language from the [Crafting Interpreters Handbook](https://www.craftinginterpreters.com).
This is meant to be a C++ implementation of `jlox` from Part I of the book.

## Building
* Install `meson` (version 0.50.0 or higher)
* Run `meson builddir` in the project root directory. This creates a new directory named `builddir`.
* Run `meson compile -C builddir`. 

## Running
After following the build instructions above, simply run `./builddir/plox`. If you do not 
provide any arguments then `plox` enters REPL mode. If you provide the name of a script
file then it will be loaded and run.

## Test Files
The directory named `test-inputs` is for input files that test various aspects of the interpreter. 
