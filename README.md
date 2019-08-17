# 42sh

Objectives:

Lecture et édition de ligne avancée avec Termcaps 
Analyse lexicale ("Lexing") 
Analyse syntaxique ("Parsing") 
Analyse sémantique 
Génération d'un Arbre de Syntaxe Abstraite (Abstract Syntax Tree, AST) 
Evaluation d'un AST 

Il s’agit ici d’écrire un shell UNIX le plus stable et le plus complet possible.

◦ Affichage d’un prompt.

  ◦ Exécution de commandes avec leurs paramètres et gestion du PATH.

◦ Gestion des erreurs, sans utiliser errno, et de la valeur de retour des commandes

◦ Gestion correcte des espaces et des tabulations.

• Les pré-requis du 21sh.

◦ Édition complète de la ligne de commande

◦ Les opérateurs de redirection et d’aggrégation :
    — >
    — >>
    — <
    — <<
    — >&
    — <&


◦ Les pipes |

◦ Les séparateurs ;

• Les built-ins suivants :

  ◦ cd
  ◦ echo
  ◦ exit
  ◦ type

• Les opérateurs logiques && et ||

• La gestion des variables internes au shell (Ne vous occupez pas des variables en
lecture-seule).

◦ La création de variable interne selon la syntaxe : name=value.

◦ L’exportation des variables internes vers l’environnement, via le built-in export.

◦ La possibilité de lister les variables internes du shell via le built-in set (pas
d’option requises).

◦ Le retrait des variables internes et d’environnement, via le built-in unset (pas
d’option requises).

◦ La création de variable d’environnement pour une commande unique, exemple :
HOME=/tmp cd.

◦ L’expansion simple des paramètres selon la syntaxe ${} (pas de format supplémentaire requis).

◦ La gestion des parametres speciaux, comme ? pour le code de sortie de la
commande precedente.

• Gestion du job control, avec les built-ins jobs, fg, bg et l’opérateur &

• Une gestion correcte de tous les signaux.

• Chaque built-in doit avoir au minimum les options dictées par le standard POSIX,
sauf cas explicite comme set ou unset.

Les features modulaires :

• Les inhibiteurs ” (double quote), ’ (simple quote) et \ (backslash)

• Le pattern matching (globing) : *, ?, [], ! et les intervals de caractères avec -

• Les commandes groupées et sous-shell : (), {};

• La substitution de commande : $()

• L’expansion arithmétique : $(())

Seulement ces opérateurs :

◦ Incrémentation, Décrémentation ++ --

◦ Addition, Soustraction + -

◦ Multiplication, Division, Modulo * / %

◦ Comparaison <= >= < >

◦ Égalité, Différence == !=

◦ ET/OU logique && ||
