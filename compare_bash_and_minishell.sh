#!/bin/bash

# Définir le chemin de votre exécutable Minishell
MINISHELL_EXECUTABLE="./minishell"

# Liste des commandes à tester
commands=(
    # "ls"
    # "pwd"
    # "echo Hello, World!"
	"true || echo aaa && echo bbb"
	"true || (echo aaa && echo bbb)"
	"true || (echo aaa && echo bbb"
	"true || echo aaa && echo bbb)"
	"true || (echo a && echo b) && echo c"
	"true || (echo a) && echo b"
	"true || ((echo a && echo b) && echo c)"

    # Ajoutez d'autres commandes ici
)

# Fonction pour comparer les sorties
compare_outputs() {
    command_output=$($1)
    minishell_output=$(echo "$1" | $MINISHELL_EXECUTABLE | sed '/minishell>/d')

    if [ "$command_output" != "$minishell_output" ]; then
        echo "Différence détectée pour la commande: $1"
        echo "Sortie Bash: $command_output"
        echo "Sortie Minishell: $minishell_output"
        echo "---------------------------------------"
    fi
}

# Exécutez les commandes et comparez les sorties
for cmd in "${commands[@]}"; do
    compare_outputs "$cmd"
done

echo "Comparaison terminée."
