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
    } | $MINISHELL >> $OUTPUT_FILE 2>&1
    echo "-----------------------" >> $OUTPUT_FILE
}

# Commandes à tester
run_minishell "echo Allo Allo, monsieur l'ordinateur"
run_minishell "cd"
run_minishell "pwd"
run_minishell "env"
run_minishell "export"
run_minishell "echo -n \"saperlotte!\"      cornejilouille."




# Comparaison avec fichier de référence

if diff -u $OUTPUT_FILE $CORRECT_OUTPUT_FILE; then
    echo "Les tests ont réussi! Fichier de sortie identique au fichier de référence."
else
    echo "Les tests ont échoué. Différences enregistrées dans : $DIFF_FILE"
fi
