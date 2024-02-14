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
    "ls"
    "pwd"
    "echo Hello, World!"
    # "not_existing_command"
	"ls | wc"
	"ls|wc"
	"ls        |       wc"

	# gestion d'erreur (syntax error)
	# "ls |"
	# "ls |     "
	# "|"
	# "ls >"
	# "ls >  # space"
	# "ls > \"\""
	# "echo hello >>"
	# ">>"


	#invalid pointer
	# "ls | rev | tr 'e' 'E' | grep -v \"file\" | cat -e"
	
			
	
	"ls | exit"
	"cat file | rev"

	"ls > file"
	"ls > wc"
	"ls > notexisting"
	"ls    >   file"
	"exit > file"
	"cd > file"
	"ls > file > file2 > file3 > file4"
	"ls > file > file2 >> file3 > file4"
	"> file"
	"ls > file | ls"



	# permission
	# "ls > no_permission/file"
	#"ls > no_permission/file > file2 > file3 | ls"
	# "touch a > no_permission/file"

	#builtin pipe problem
	# "echo hello >> file"
	# "echo hello >> not_existing"
	# "echo hello >> no_permission/file"

	"wc < file"
	"wc < notexisting"
	# "wc < no_permission/file"
	"cat < file | wc"
	# "wc <"
	"< file wc"
	# "<"

	# "wc << END"
	# "wc << END"
	# "wc << END"
	# "<< END"
	# "wc << ls"
	# "export HEY=hello    &&   wc << \$HEY"
	# "wc << he'll'o"
	# "wc << END | rev"
	# "cat | wc << FIN		#todo"
	# "<<"

	#wildcard
	# "echo *"
	# "echo \"*\""
	# "echo '*'"
	# "echo \$*"
	# "cat *.c"
	# "touch \"file with spaces\"       and       rm *"
	# "cat src/*.c | grep \"printf\""
	
	# "ls >>> file"
	# "ls >>      > file"
	# "ls >      >> file"
	# "wc <<< file"
	# "wc <<      < file"
	# "wc <> file"
	# "ls >< file"
	# "ls |> wc"
	# "echo hello >    > file"
	# "ls | rev << END"


	# "true || echo aaa && echo bbb"
	# "true || (echo aaa && echo bbb)"
	# "true || (echo aaa && echo bbb"
	# "true || echo aaa && echo bbb)"
	# "true || (echo a && echo b) && echo c"
	# "true || (echo a) && echo b"
	# "true || ((echo a && echo b) && echo c)"
	# "true || \"(\"echo b && echo c)"

	"echo a && ls >"
	"echo a && awoiejlk"
	"ls > file && echo \"salut\""
	"false && (echo aaa)"
	"(ls && ls)"
	"ls & & ls"
	"ls && && ls"
	"ls | | ls"
	"ls (&&) ls"
	"echo \"&&\" ls"
	"exit && ls"
	"ls && exit"
	"ls &&"
	"&& ls"
	"&&"
	"||"
	"(&&)"
	"echo a || wc << fin"


	  # Ajout d'une commande inexistante pour tester
    # Ajoutez d'autres commandes ici
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
