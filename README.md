# Recipe-Book

This is my third and final implementation of this application built to keep track of recipes. My goal is to have a well implemented and user friendly application, built to be easily maintainable and extensible.

The application is written in C++ built using the Qt framework. Although there is an abstraction layer for the database, leaving space for many different database implementations, I plan on writing an Sqlite3 implementation and no others.

When planning and writing the application, I will be following the architecture principles of Model-View-Controller, using the built-in solutions of the Qt framework (Views-Models-Delegates).

## Documentation

To get a better overview of the projects structure, goals and implementation details, see [`/docs/README.md`](./docs/README.md) for more info.

## Post-Mortem

I'm calling this phase of the project to be complete. The software wasn't fully implemented (there was a lot of work left to be done on everything Recipe related, such as editing and deleting recipes), but the general gist of the software was implemented. I've learned plenty from this phase and feel like there was some good, some bad, and some ugly code that was written.

### The Good

I'm really particularly with the implementation of the backend. The database layer was obviously going to be a lot of work given the fact that I decided to hard code SQL queries, but it felt fast and responsive. Implementing a visitor pattern made using the database layer a breeze as well, since I wasn't worried about communicating the objects type along with its data. In future projects, I think I'll settle for writing SQL by hand again, as well as use the same visitor pattern given how it might be a lot of work to implement, but it really cuts down on complexity down the line. It also makes it really easy to implement more models in the overall application design.

The cache layer was also well implemented. It's quite simple and there isn't much to be said about it, but it was well executed and I feel that it fulfilled its role while requiring little effort to implement.

There isn't much to say about the factory layer other than it works. There's nothing fancy about it, and using the signal/slot class and deriving a templated class was the correct implementation to simplify the implementations down the line.

### The Bad

I should have had the UI implementation work in such a way that signals would be emitted from the individual elements and make their way up to the relevant layers; slots should pretty much only be implemented in the MainWindow class, which would call the actual functions of child elements (this doesn't apply to indivdual ui elements and their respective private slots like on_clicked()). What instead ended up happening is that I'd have way too many slots connected all over the place, which made it unclear if MainWindow should be calling a function to have some data handled, or if it should be re-emitting some signal since I already had a handler slot connected.

Another glaring (and rookie) mistake I've commited in this project is to not comment my code. This makes it ridiculously more difficult to remember how to use different portions/layers further down the line, and it becomes a costly exercise of trying to remember how I felt on a given day to remember how to use a particular function I wrote previously. From now on, I'm using Doxygen.

### The Ugly

I'd say that given my lack of experience with the Qt framework, the order in which I implemented a lot of things slowed down development drastically. Instead of writing individual delegates for every single object imaginable, it would have been wiser to just come up with a default delegate to speed up development. Using DisplayRole would have also saved me from painstakingly having to rewrite how I want data to be displayed for every single different model in its own class. Overall, although I'm sure there are some horrid portions of code I've written, the biggest crime I've commited in this project is in the various steps I took to implement each portion.
