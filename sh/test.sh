#!/bin/bash

# check the container, whose name is 'atcoder' is running
CONTAINER_NAME="atcoder"
if [ ! "$(docker ps -q -f name=$CONTAINER_NAME)" ]; then
    echo "Container $CONTAINER_NAME is not running. Please run the container first."
    exit 1
else
    echo "Container $CONTAINER_NAME is running."
fi

BASEDIR="/workdir"
LANG_WORKSPACE_MAP=(
    "cpp $BASEDIR/contest"
    "python $BASEDIR/contest_python"
    "rust $BASEDIR/contest_rust"
)

# default is cpp, if no argument is given. argument is set by --lang option
LANG="cpp"
CONTEST_NAME=""
PROBLEM_ID=""

# Parse arguments
while [ $# -gt 0 ]; do
    case "$1" in
        --lang)
            if [ $# -lt 2 ]; then
                echo "Error: --lang requires an argument."
                exit 1
            fi
            LANG=$2
            shift 2
            ;;
        -*)
            echo "Unknown option: $1"
            exit 1
            ;;
        *)
            # 最初の引数はコンテスト名、2番目の引数は問題IDとして扱う
            if [ -z "$CONTEST_NAME" ]; then
                CONTEST_NAME=$1
            elif [ -z "$PROBLEM_ID" ]; then
                PROBLEM_ID=$1
            else
                echo "Error: Too many arguments."
                echo "Usage: $0 [--lang language] contest_name problem_id"
                exit 1
            fi
            shift
            ;;
    esac
done

# Get the workspace path from LANG_WORKSPACE_MAP
WORKSPACE=""
for i in "${LANG_WORKSPACE_MAP[@]}"; do
    KEY="${i%% *}"
    VALUE="${i#* }"
    if [ "$KEY" = "$LANG" ]; then
        WORKSPACE=$VALUE
        break
    fi
done

echo "Workspace: $WORKSPACE"

# Check if contest name is provided
if [ -z "$CONTEST_NAME" ]; then
    echo "Please specify the contest name."
    echo "Usage: $0 [--lang language] contest_name problem_id"
    exit 1
fi

# Check if the contest directory already exists
CONTEST_DIR="$WORKSPACE/$CONTEST_NAME"
if [ -d "$CONTEST_DIR" ]; then
    echo "Directory $CONTEST_DIR is already created."
    exit 1
fi

# Check if problem id is provided
if [ -z "$PROBLEM_ID" ]; then
    echo "Please specify the problem id."
    echo "Usage: $0 [--lang language] contest_name problem_id"
    exit 1
fi

echo "Contest name: $CONTEST_NAME"
echo "Problem ID: $PROBLEM_ID"

# If language is cpp
if [ "$LANG" = "cpp" ]; then
    docker exec -it $CONTAINER_NAME /bin/bash -c "cd $CONTEST_DIR/$PROBLEM_ID && g++ -o out main.cpp"
    docker exec -it $CONTAINER_NAME /bin/bash -c "cd $CONTEST_DIR/$PROBLEM_ID && atcoder-tools test --exec ./out"
fi

# If language is python
if [ "$LANG" = "python" ]; then
    echo "Not implemented yet."
fi

# If language is rust
if [ "$LANG" = "rust" ]; then
    echo "Not implemented yet."
fi
