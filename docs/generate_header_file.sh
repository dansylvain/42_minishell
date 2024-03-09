#!/bin/bash

generate_header_file() {
    local source_file="$1"
    local header_file="${source_file%.c}.h"
    local base_name=$(basename "$source_file" .c)
    local include_guard="${base_name^^}_H"

    cat > "$header_file" <<EOF
#ifndef $include_guard
#define $include_guard

#include <minishell.h>

EOF

    while IFS= read -r line; do
        if [[ "$line" == *"/*=========================================================================="* ]]; then
            break
        fi
        if [[ "$line" =~ ^[a-zA-Z_][a-zA-Z0-9_]*[[:space:]]+[a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*\(.*\) ]]; then
            echo "$line;" >> "$header_file"
        fi
    done < "$source_file"

    echo "" >> "$header_file"
    echo "#endif" >> "$header_file"
}

# if [ $# -lt 1 ]; then
#     echo "Usage: $0 <source_file.c>"
#     exit 1
# fi

find src -type f -name "*.c" | while read -r file; do
    generate_header_file "$file"
    echo "Header file generated: ${file%.c}.h"
done
