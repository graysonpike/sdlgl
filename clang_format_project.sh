#!/bin/bash

# Array of directory patterns to exclude from the search (using wildcard to match at any level)
exclude_patterns=(*/dependencies/* */build/* */cmake-build-debug/*) # Add more patterns as needed

# Base find command
find_command="find ."

# Loop through the exclude_patterns array and append each pattern to the find command
for pattern in "${exclude_patterns[@]}"; do
  find_command+=" -path \"$pattern\" -prune -o"
done

# Append the search criteria and print action to the find command
find_command+=" \( -name \"*.cpp\" -o -name \"*.h\" \) -print"

# Execute the find command and pipe its output to a loop that prints each file name before formatting
eval "$find_command" | xargs -I {} bash -c 'echo "Processing file: {}"; clang-format -i "{}"'

echo "Formatting complete."
