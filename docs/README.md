# Defining Recipe-Store

The point of this application is to be a simple, no nonsense way of locally storing your recipes and easily finding them again.

## Core features

- [`Store recipes`](#recipes)
- [`Remember ingredients`](#ingredients)
- [`Allow recipes to be used as ingredients in other recipes`](#recursion)
- [`Provide search functionality to find recipes`](#search)
- [`Allow users to share recipes`](#share) (optional feature)
- [`Allow users to search shared recipes`](#share-search) (optional feature)

---

<a id="recipes"></a>
### Store Recipes

A user stores recipes by giving them a name, adding some ingredients and their quantities to it, and calling it a day. Optionally, they can add actual steps to making the recipe, add what equipment is necessary, and add a nice little paragraph of notes or unnecessary life stories to go with it as you'd find on any online recipe.
The idea is additionally that recipes themselves become ingredients for other recipes, and it becomes possible to navigate from one recipe, to a precursor recipe with ease within the app.

Save recipes with:
- Name, ingredients (with quantities), and steps  
- Optional: Equipment, notes, or descriptions  
- Nested navigation (e.g., click "Pizza Dough" in "Pizza" recipe)

<a id="ingredients"></a>
### Remember Ingredients

Ingredients shouldn't just be text fields that are written in and then forgotten about, exclusively used for one recipe. They should be concrete data structures that are stored and re-used over multiple recipes. Users should have the power to add and curate their ingredients lists, and when writing a recipe should be able and pushed towards using pre-existing ingredients. Should an ingredient not be within the ingredients list for a user, they should be able to create the ingredient along with relevant details.

- Ingredients are reusable objects (not free text)  
- Auto-suggests existing ingredients when typing  
- Add new ingredients directly from recipe editor
Save a new ingredient with:
- Name
- Optional: Price, notes, or descriptions

<a id="recursion"></a>
### Reusing Recipes

Once a user has created a recipe, they need to be able to use that recipe in another recipe, as though it were an ingredient.
- Use any recipe as an ingredient in another recipe  
- Have recipes used as ingredients in other recipes show up in a way that lets the user navigate to them with ease (link to them)

<a id="search"></a>
### Searchable Recipes

Recipes need to be searchable by their name, or from their ingredients. Entering a combination of ingredients should yield the user the recipe they're looking for.
- Name (`"Pasta"`)  
- Ingredients (`"Tomatoes, Basil"`)  
- Equipment (`"Blender"`)

<a id="share"></a>
### Sharing Recipes (optional feature)

Users should be able to export their recipes to an online 'market' of sorts, except there's no money involved, and users can take down what they share. A system of likes should help bring visibility to the most popular recipes.
This feature is an optional one to implement however, and shouldn't take precedence over the previous core features
- Publish recipes to community hub  
- Like/visibility system (no payments)  
- Full control over shared recipes

<a id="share-search"></a>
### Searching Shared Recipes

Users should be able to browse the recipe 'market' to find recipes that interest them. A system of likes can allow popular recipes to be displayed on a greeter page for the user. Users should be able to add a found recipe to their own list of recipes, with credit given to the author if they chose to share their name.
This feature is an optional one to implement however, and shouldn't take precedence over the previous core features
- Browse popular/trending community recipes  
- One-click import to local collection

## Tech Stack

The core application will be written in C++ using the Qt framework. Custom UI elements are used to give a more modern feel to the software, and should provide feedback as to what's going on.
The database used to store user data is SQLite due to its ease of implementation, and how little traffic to the database will exist. A single user is interacting with the database, so there's no point
in using anything more robust.

**Language:** C++  
- Why: Performance + Qt framework compatibility  

**UI Framework:** Qt  
- Why: Cross-platform support + custom modern widgets  

**Database:** SQLite  
- Why: Single-user, zero-configuration, no server needed  
