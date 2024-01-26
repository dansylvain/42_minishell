# minishell

https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf# minis


Things to check:
- unset first and last env variable (segfault?)
- builtins/commands with extra chars: (pwdxxx, cdxxx, lsxxx, ...)
- use of non authorized funcitons (setenv, putenv, ...)

TODOS
- in function exec_echo: handle single/double quotes


WORKING WITH GIT
git restore --staged nom_de_fichier : 	enlève de la zone staged vers la zone working directory
git restore : 				supprime les modifs NON STAGED de la zone working directory

