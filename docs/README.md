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

# ==================
valgrind --trace-children=yes --leak-check=full --show-leak-kinds=all --suppressions=valgrind.supp ./minishell

# TO DELETE
I silenced the pipex warning with a flag in file src/pipex/pipex.c
because it sucks. Let us not forget to remove it by the end of the project!

git add . && git commit -m "first endversion to be tested" && git push && git status

env -i ./minishell !!!--
