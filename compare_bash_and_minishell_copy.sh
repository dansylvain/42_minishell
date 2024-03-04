#!/bin/bash

# Définir le chemin de votre exécutable Minishell
MINISHELL_EXECUTABLE="./minishell"

# Définir les chemins des fichiers de sortie
BASH_OUTPUT_FILE="bash_output.txt"
MINISHELL_OUTPUT_FILE="minishell_output.txt"

# Vider les fichiers de sortie avant chaque exécution
> "$BASH_OUTPUT_FILE"
> "$MINISHELL_OUTPUT_FILE"

# Vérifier si le fichier d'entrée des commandes est spécifié en argument
if [ -z "$1" ]; then
    echo "Usage: $0 <fichier_commandes>"
    exit 1
fi

# Fonction pour comparer les sorties
compare_outputs() {
    command="$1"
    command_output=$(eval "$command" 2>&1)
    minishell_output=$($MINISHELL_EXECUTABLE <<< "$command" 2>&1 | tail -n +2 | sed '$d')

    # Filtrer les sorties pour ignorer les différences non significatives
    filtered_command_output=$(echo "$command_output" | sed 's/ //g')
    filtered_minishell_output=$(echo "$minishell_output" | sed 's/ //g')

    if [ "$filtered_command_output" != "$filtered_minishell_output" ]; then
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

# Lire les commandes à partir du fichier spécifié, une ligne à la fois
while IFS= read -r cmd; do
    compare_outputs "$cmd"
done < "$1"

echo "Comparaison terminée."
