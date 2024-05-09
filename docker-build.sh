#!/bin/bash

this_path=$(readlink -f "$0")
this_dir=$(dirname "$this_path")
this_file=$(basename "$this_path")
this_name=${this_file%.*}

# Command Line Options
short_opts=
long_opts="preset:"

# Command Line Argument Handling

function usage()
{
  echo "Usage: $this_file [options]"
  echo
  echo Build docker image and build xvector inside the container
  echo
  echo --preset=\<debug-x64\|release-x64\>
}

function try_help()
{
  local exit_code=$1
  usage
  echo
  echo Try \'$this_name --help\' for more information.
  exit $exit_code
}

function help()
{
  local exit_code=$1
  usage
  echo
  echo ""

  exit $exit_code
}

opts=$(getopt -o "$short_opts" --long "$long_opts" -n "$this_name" -- "$@")

if [ $? != 0 ] ; then
  echo
  try_help 1
fi

#echo opts=$opts

# e (errexit) - exit immediately if any command exits with a non-zero status
# x (xtrace) - enables a debug mode that prints each command and its arguments
# u (nounset) - treats unset (or undefined) variables as an error when performing parameter expansion
# n (noexec) - reads commands without executing them, which is useful for checking syntax errors
#set -exu

eval set -- "$opts"

# Optional Arguments

preset=release-x64
while true; do
  case "$1" in
    --help)
      help 0
      ;;
    --preset)
      preset=$2
      shift 2
      ;;
    --)
      shift
      break
      ;;
    *)
      break
      ;;
  esac
done

docker build -t xvector .
docker run -it --rm --privileged -v .:/xvector xvector
