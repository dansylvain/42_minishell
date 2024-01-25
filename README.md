# minishell

https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf# minis


Things to check:
- unset first and last env variable (segfault?)
- builtins/commands with extra chars: (pwdxxx, cdxxx, lsxxx, ...)
- use of non authorized funcitons (setenv, putenv, ...)

TODOS
- in function exec_echo: handle single/double quotes