# Définition de Recipe-Store

L'objectif de cette application est d'offrir un moyen simple et sans fioritures de stocker localement vos recettes et de les retrouver facilement.

## Fonctionnalités principales

- [`Stocker des recettes`](#recettes)
- [`Mémoriser les ingrédients`](#incredients)
- [`Permettre aux recettes d'être utilisées comme ingrédients dans d'autres recettes`](#recursion)
- [`Fournir une fonctionnalité de recherche pour trouver des recettes`](#recherche)
- [`Permettre aux utilisateurs de partager des recettes (fonctionnalité optionnelle)`](#partage)
- [`Permettre aux utilisateurs de rechercher des recettes partagées (fonctionnalité optionnelle)`](#recherche-partagee)

<a id="recettes"></a>
### Stocker des Recettes

Un utilisateur stocke une recette en lui donnant un nom, en y ajoutant des ingrédients et leurs quantités, et c'est terminé. Optionnellement, il peut ajouter les véritables étapes de préparation, indiquer le matériel nécessaire et ajouter un joli paragraphe de notes ou une anecdote personnelle superflue, comme on en trouve dans n'importe quelle recette en ligne.
L'idée supplémentaire est que les recettes elles-mêmes deviennent des ingrédients pour d'autres recettes, et qu'il devient possible de naviguer facilement d'une recette à une recette précurseur dans l'application.

Sauvegarder les recettes avec :
- Nom, ingrédients (avec quantités) et étapes
- Optionnel : Matériel, notes ou descriptions
- Navigation imbriquée (ex : cliquer sur "Pâte à pizza" dans la recette "Pizza")

<a id="ingredients"></a>
### Mémoriser les Ingrédients

Les ingrédients ne doivent pas être de simples champs de texte saisis puis oubliés, utilisés exclusivement pour une recette. Ils doivent être des structures de données concrètes qui sont stockées et réutilisées dans plusieurs recettes. Les utilisateurs doivent avoir la possibilité d'ajouter et de gérer leurs listes d'ingrédients, et lors de la saisie d'une recette, doivent être incités à utiliser des ingrédients préexistants. Si un ingrédient n'est pas dans la liste de l'utilisateur, il doit pouvoir créer l'ingrédient avec les détails pertinents.

- Les ingrédients sont des objets réutilisables (pas du texte libre)
- Suggère automatiquement les ingrédients existants lors de la frappe
- Ajouter de nouveaux ingrédients directement depuis l'éditeur de recette

Sauvegarder un nouvel ingrédient avec :
- Nom
- Optionnel : Prix, notes ou descriptions

<a id="recursion"></a>
### Réutiliser les Recettes

Une fois qu'un utilisateur a créé une recette, il doit pouvoir utiliser cette recette dans une autre recette, comme s'il s'agissait d'un ingrédient.
- Utiliser n'importe quelle recette comme ingrédient dans une autre recette
- Les recettes utilisées comme ingrédients doivent apparaître de manière à permettre à l'utilisateur de naviguer facilement vers elles (lien vers elles)

<a id="recherche"></a>
### Recettes Interrogeables

Les recettes doivent pouvoir être recherchées par leur nom ou par leurs ingrédients. Saisir une combinaison d'ingrédients doit donner à l'utilisateur la recette qu'il cherche.
- Par nom ("Pâtes")
- Par ingrédients ("Tomates, Basilic")
- Par matériel ("Blender")

<a id="partage"></a>
### Partager les Recettes (fonctionnalité optionnelle)

Les utilisateurs doivent pouvoir exporter leurs recettes vers une sorte de "marché" en ligne, sauf qu'il n'y a pas d'argent impliqué et que les utilisateurs peuvent retirer ce qu'ils partagent. Un système de "j'aime" devrait aider à donner de la visibilité aux recettes les plus populaires.
Cette fonctionnalité est cependant optionnelle à implémenter et ne doit pas prendre le pas sur les fonctionnalités principales précédentes.
- Publier des recettes dans un hub communautaire
- Système de "j'aime"/visibilité (pas de paiements)
- Contrôle total sur les recettes partagées

<a id="recherche-partagee"></a>
### Rechercher les Recettes Partagées

Les utilisateurs doivent pouvoir parcourir le "marché" des recettes pour trouver des recettes qui les intéressent. Un système de "j'aime" peut permettre aux recettes populaires d'être affichées sur une page d'accueil pour l'utilisateur. Les utilisateurs doivent pouvoir ajouter une recette trouvée à leur propre liste de recettes, en créditant l'auteur s'il a choisi de partager son nom.
Cette fonctionnalité est cependant optionnelle à implémenter et ne doit pas prendre le pas sur les fonctionnalités principales précédentes.
- Parcourir les recettes communautaires populaires/tendances
- Importation en un clic vers la collection locale

## Tech Stack

L'application principale sera écrite en C++ en utilisant le framework GTK. Le but du backend et du frontend de l'application est d'être simple et réactif. La base de données utilisée pour stocker les données utilisateur est SQLite, en raison de sa facilité de mise en œuvre et du faible trafic attendu vers la base de données. Un seul utilisateur interagit avec la base de données, donc il n'y a pas d'intérêt à utiliser quelque chose de plus robuste.

**Langage** : C++
- Pourquoi : Performance + compatibilité avec le framework Qt

**Framework UI** : GTK
- Pourquoi : Implémentation d'interface utilisateur plus simple et meilleure intégration avec GNOME

**Base de données** : SQLite
- Pourquoi : Monoutilisateur, configuration zéro, aucun serveur nécessaire


