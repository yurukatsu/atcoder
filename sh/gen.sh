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
            # Assume this is the contest name
            CONTEST_NAME=$1
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

# If the workspace is not found, create new directory
if [ -z "$WORKSPACE" ]; then
    WORKSPACE="$BASEDIR/contest_$LANG"
    mkdir -p $WORKSPACE
    echo "Created new workspace: $WORKSPACE"
fi

# Check if contest name is provided
if [ -z "$CONTEST_NAME" ]; then
    echo "Please specify the contest name."
    exit 1
fi

# Check if the contest directory already exists
CONTEST_DIR="$WORKSPACE/$CONTEST_NAME"
if [ -d "$CONTEST_DIR" ]; then
    echo "Directory $CONTEST_DIR already exists."
    exit 1
fi

# Create the contest directory
docker exec -it $CONTAINER_NAME atcoder-tools gen --lang $LANG --workspace $WORKSPACE --without-login $CONTEST_NAME

# Change owner of the created directory
docker exec -it $CONTAINER_NAME chown -R $(id -u):$(id -g) $CONTEST_DIR
