# Foreword

I previously thought I'd leave this idea for a project behind and move on to something else, but having recently invested most of my time in cooking and really pushing my skills I've come to realize the utility of building out this software to a state that makes it realistically usable as a reliable way to store recipes. I'd like to say that this is my last time revisiting this type of software, but I feel as though I'll come back to it at some point to make some aspect of it better as I further grow my understanding of good design practices and patters. I'll do my best to document my code as well as illustrate the general idea of how each part of this software work together to make it easier to fix in the future without a full rewrite of the code.

# Recipe Book

This software is meant to be a way of storing and reading your recipes. The core concept behind this software is that each recipe is made up of ingredients (duh), and that each recipe is an ingredient in itself. Of course, there are some raw ingredients that aren't recipes, but instead are harvested as is from the earth, but that is accounted for and denoted in the software.

This implementation is built using the GTK library as well as the GTKmm library.

To get a better overview of the projects structure, goals and implementation details, see [`/docs/README.md`](./docs/README.md) for more info.

# Directory structure

## Subdirectories
[`/src`](./src) -> Application source code

[`/docs`](./docs) -> Software documentation as well as developer documentation

## Files
[`run_clang_tidy.sh`](./run_clang_tidy.sh) -> A helper script that runs clang-tidy on all the code in the source directory.

[`.clang_format`](./.clang_format) -> The config file for clang-format. This config is project-wide.

[`.clang_tidy`](./.clang_tidy) -> The config file for clang-tidy. This config is project-wide.

[`Doxyfile`](./Doxyfile) -> Doxygen configuration file.
