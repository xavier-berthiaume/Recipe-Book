# Foreword

I previously thought I'd leave this idea for a project behind and move on to something else, but having recently invested most of my time in cooking and really pushing my skills I've come to realize the utility of building out this software to a state that makes it realistically usable as a reliable way to store recipes. I'd like to say that this is my last time revisiting this type of software, but I feel as though I'll come back to it at some point to make some aspect of it better as I further grow my understanding of good design practices and patters. I'll do my best to document my code as well as illustrate the general idea of how each part of this software work together to make it easier to fix in the future without a full rewrite of the code.

# Recipe Book

This software is meant to be a way of storing and reading your recipes. The core concept behind this software is that each recipe is made up of ingredients (duh), and that each ingredient is a recipe in itself. Of course, there are some raw ingredients that aren't recipes, but instead are harvested as is from the earth, but that is accounted for and denoted in the software.

To get a better overview of the projects structure, goals and implementation details, see [`/docs/README.md`](./docs/README.md) for more info.
