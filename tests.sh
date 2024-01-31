#!/bin/bash

#! expect packet added in order to got this script working
#! (=> sudo apt-get install expect)

# Définition le chemin vers minishell
MINISHELL=./minishell

# Définition des fichiers
OUTPUT_FILE=output.txt
CORRECT_OUTPUT_FILE=correct_output.txt
DIFF_FILE=diff_output.txt

# Vider le fichier de sortie
echo -n > $OUTPUT_FILE

# execution de minishell + entrée commande -> copie de l'output dans output.txt 
run_minishell() {
    echo "Commande: $1" >> $OUTPUT_FILE
    {
        echo "$1"
        if [ -n "$2" ]; then
            echo "$2"
        fi
    } | $MINISHELL >> $OUTPUT_FILE 2>&1
    echo "-----------------------" >> $OUTPUT_FILE
    echo "" >> $OUTPUT_FILE  # Ajoute une ligne vide entre chaque série de tests
}

# Commandes à tester
run_minishell "cd" "pwd"
run_minishell "cd /"  "pwd"
run_minishell "cd chemin/inexistant"  "pwd"
run_minishell "cd src/builtins"  "pwd"
run_minishell "cd .."  "pwd"



# Comparaison avec fichier de référence

if diff -u $OUTPUT_FILE $CORRECT_OUTPUT_FILE >> $DIFF_FILE; then
    echo "Les tests ont réussi! Fichier de sortie identique au fichier de référence."
else
    echo "Les tests ont échoué. Différences enregistrées dans : $DIFF_FILE"
fi
