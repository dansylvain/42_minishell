#!/bin/bash

# Vérifiez si un fichier .c est fourni en argument
if [ $# -lt 1 ]; then
    echo "Usage: $0 <source_file.c>"
    exit 1
fi

# Récupérez le nom du fichier source
source_file="$1"

# Créer un fichier temporaire contenant les opérateurs et les mots-clés en C
temp_file=$(mktemp)
echo -e "sizeof\nif\nelse\nwhile\nfor\ndo\nreturn\nbreak\ncontinue\nswitch\ncase\ndefault\ngoto\ntypedef\nstruct\nunion\nenum\nconst\nvolatile\nextern\nstatic\nregister\nauto\nrestrict\nalignof\noffsetof\ntypeof\nasm" > "$temp_file"

# Utilisez grep pour rechercher les appels de fonction à l'intérieur du code
grep -oE '\b[a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*\(' "$source_file" |
# Supprimez les parenthèses à la fin des noms de fonction
sed 's/[(].*//g' |
# Filtrer les opérateurs et mots-clés
grep -vF -f "$temp_file" |
# Supprimez les doublons
sort -u

# Supprimer le fichier temporaire
rm "$temp_file"
