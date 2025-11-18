# Avant-propos

J'avais précédemment pensé abandonner cette idée de projet et passer à autre chose, mais après avoir récemment consacré la plupart de mon temps à la cuisine et avoir vraiment développé mes compétences, j'ai réalisé l'utilité de développer ce logiciel jusqu'à un état qui le rendrait réellement utilisable comme moyen fiable de stocker des recettes. J'aimerais dire que c'est la dernière fois que je reviens sur ce type de logiciel, mais j'ai le sentiment d'y revenir un jour pour en améliorer certains aspects au fur et à mesure que j'approfondis ma compréhension des bonnes pratiques et modèles de conception. Je ferai de mon mieux pour documenter mon code ainsi qu'illustrer l'idée générale du fonctionnement de chaque partie de ce logiciel pour faciliter les corrections futures sans avoir à réécrire complètement le code.

# Recipe Book

Ce logiciel est conçu pour être un moyen de stocker et de lire vos recettes. Le concept central de ce logiciel est que chaque recette est composée d'ingrédients (évidemment), et que chaque recette est elle-même un ingrédient. Bien sûr, il existe des ingrédients bruts qui ne sont pas des recettes, mais qui sont plutôt récoltés tels quels de la terre, mais cela est pris en compte et indiqué dans le logiciel.

Cette implémentation est construite en utilisant la bibliothèque GTK ainsi que la bibliothèque GTKmm.

Pour avoir une meilleure vue d'ensemble de la structure du projet, des objectifs et des détails d'implémentation, voir [`/docs/README.md`](./docs/README.md) pour plus d'informations.

# Structure des répertoires

## Sous-répertoires
[`/src`](./src) -> Code source de l'application

[`/docs`](./docs) -> Documentation du logiciel ainsi que documentation pour les développeurs

## Fichiers
[`run_clang_tidy.sh`](./run_clang_tidy.sh) -> Un script d'aide qui exécute clang-tidy sur tout le code du répertoire source.

[`.clang_format`](./.clang_format) -> Le fichier de configuration pour clang-format. Cette configuration s'applique à l'ensemble du projet.

[`.clang_tidy`](./.clang_tidy) -> Le fichier de configuration pour clang-tidy. Cette configuration s'applique à l'ensemble du projet.

[`Doxyfile`](./Doxyfile) -> Fichier de configuration Doxygen.
