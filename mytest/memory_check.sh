#!/bin/bash

# Définir le chemin de votre exécutable Minishell
MINISHELL_EXECUTABLE="../minishell"

# Créer un fichier pour stocker les commandes avec fuites de mémoire
LEAKS_OUTPUT_FILE="outfile/leaks_output.txt"
> "$LEAKS_OUTPUT_FILE"

# Vérifier si le fichier d'entrée des commandes est spécifié en argument
if [ -z "$1" ]; then
    echo "Usage: $0 <fichier_commandes>"
    exit 1
fi

# Initialiser les compteurs
total_tests=0
successful_tests=0

# Fonction pour exécuter une commande avec Valgrind
run_with_valgrind() {
    command="$1"
    # Exécute la commande avec Valgrind dans un sous-shell pour isoler la redirection de la sortie
    valgrind_output=$( (valgrind --trace-children=yes --leak-check=full --show-leak-kinds=all --suppressions=valgrind.supp "$MINISHELL_EXECUTABLE" <<< "$command") 2>&1 >/dev/null )

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
	else
		# Incrémenter le compteur de tests réussis si aucune fuite de mémoire n'a été détectée
		successful_tests=$((successful_tests + 1))
    fi
	    total_tests=$((total_tests + 1))

}

# Lire les commandes à partir du fichier spécifié, une ligne à la fois
while IFS= read -r cmd; do
    run_with_valgrind "$cmd"
done < "$1"

echo "Analyse des fuites de mémoire terminée."
echo "TESTS : $successful_tests / $total_tests"
