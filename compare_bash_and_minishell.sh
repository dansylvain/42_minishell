#!/bin/bash

# Définir le chemin de votre exécutable Minishell
MINISHELL_EXECUTABLE="./minishell"

# Définir les chemins des fichiers de sortie
BASH_OUTPUT_FILE="bash_output.txt"
MINISHELL_OUTPUT_FILE="minishell_output.txt"

# Vider les fichiers de sortie avant chaque exécution
> "$BASH_OUTPUT_FILE"
> "$MINISHELL_OUTPUT_FILE"

# Liste des commandes à tester
commands=(
    "/bin/ls"
	""
	"/bin/ls -a"
	"echo bonjour"
	"echo"
	"echo -n bonjour"
	"ls -a | rev"
	"exit 42"
	"echo $?"
	"ls -a"
	"echo $?"
	"ls fichiernulachier"
	"echo $?"
	"echo $? + $?"
	"ls "includes""
	"echo \"cat lol.c | cat > lol.c\""
	"ls inclu\"des\""
	"echo '$USER'"
	"cat includes/minishell.h"
	"cat <includes/minishell.h"
	"echo papa >> file1"
	"echo maman >> file1"
	"cat file1"
	"cat file1 | grep papa | more"
	"ls fichiernul | grep bla | more"
	"echo aaa && echo bbb || echo ccc"
	"echo aaa || echo bbb || echo ccc"
	"false && echo bbb || echo ccc"
	"false || echo bbb || echo ccc"
	"false && echo bbb && echo ccc"
	
	"echo $SHELL"
)

# Fonction pour comparer les sorties
compare_outputs() {
    command="$1"
    command_output=$(eval "$command" 2>&1)
    minishell_output=$($MINISHELL_EXECUTABLE <<< "$command" 2>&1 | tail -n +2 | sed '$d')

    if [ "$command_output" != "$minishell_output" ]; then
        echo "Différence détectée pour la commande: $command"
        echo "Sortie Minishell: $minishell_output"
        echo "Sortie Bash: $command_output"
        echo "---------------------------------------"
    fi

    # Ajouter les sorties dans les fichiers correspondants
    echo "Commande: $command" >> "$BASH_OUTPUT_FILE"
    echo "$command_output" >> "$BASH_OUTPUT_FILE"
    echo "" >> "$BASH_OUTPUT_FILE"

    echo "Commande: $command" >> "$MINISHELL_OUTPUT_FILE"
    echo "$minishell_output" >> "$MINISHELL_OUTPUT_FILE"
    echo "" >> "$MINISHELL_OUTPUT_FILE"
}

# Exécutez les commandes et comparez les sorties
for cmd in "${commands[@]}"; do
    compare_outputs "$cmd"
done

echo "Comparaison terminée."
