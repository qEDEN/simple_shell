#!/bin/sh
while true
do
    printf "\$ "
    read -r command

    if [ -z "$command" ]; then
        continue
    fi

    case "$command" in
        exit)
            break
            ;;
        env)
            # Print the current environment
            env
            ;;
        *)
            # Check if the command exists in PATH
            if command -v "$command" > /dev/null 2>&1; then
                # Execute the command with arguments
                /bin/sh -c "$command"
            else
                echo "./simple_shell: $command: command not found"
            fi
            ;;
    esac
done
