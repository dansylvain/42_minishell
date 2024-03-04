#!/bin/bash

# Définir le chemin de votre exécutable Minishell
MINISHELL_EXECUTABLE="./minishell"

# Créer un fichier pour stocker les commandes avec fuites de mémoire
LEAKS_OUTPUT_FILE="leaks_output.txt"
> "$LEAKS_OUTPUT_FILE"

# Liste des commandes à tester
commands="$1"

# Fonction pour exécuter une commande avec Valgrind
run_with_valgrind() {
    command="$1"
    # Exécute la commande avec Valgrind dans un sous-shell pour isoler la redirection de la sortie
    valgrind_output=$( (valgrind --trace-children=yes --leak-check=full --show-leak-kinds=all --suppressions=valgrind.supp --suppressions=ls_valgrind.supp "$MINISHELL_EXECUTABLE" <<< "$command") 2>&1 >/dev/null )

    # Vérifier s'il y a des fuites de mémoire dans la sortie de Valgrind
    if echo "$valgrind_output" | grep -q "0x"; then
		echo "---------------------------------------"
		echo "*******************************************************"
        echo "Fuites de mémoire détectées pour la commande: $command"
        echo "*******************************************************"
		echo "Sortie Valgrind:"
        echo "$valgrind_output"
        echo "---------------------------------------"
        echo "Commande: $command" >> "$LEAKS_OUTPUT_FILE"
        echo "Sortie Valgrind:" >> "$LEAKS_OUTPUT_FILE"
        echo "$valgrind_output" >> "$LEAKS_OUTPUT_FILE"
        echo "" >> "$LEAKS_OUTPUT_FILE"
    fi
}

commands=$(<commands.txt)

# Exécutez les commandes avec Valgrind et recherchez les fuites de mémoire
for cmd in $commands; do
	run_with_valgrind "$cmd"
done

echo "Analyse des fuites de mémoire terminée."
