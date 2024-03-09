#!/bin/bash

# Vérifiez si un répertoire est fourni en argument
if [ $# -lt 1 ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

# Récupérez le nom du répertoire
directory="$1"

# Parcours de tous les fichiers .h dans le répertoire donné
find "$directory" -type f -name "*.h" | while read -r file; do
    # Afficher le nom du fichier

    # Extraire les prototypes des fonctions dans le fichier .h
    grep -oE '^[[:space:]]*[a-zA-Z_][a-zA-Z0-9_]*[[:space:]]+[a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*\([^;]*\)[[:space:]]*;' "$file"
done