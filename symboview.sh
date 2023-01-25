#!/bin/bash
set -e

OUTFILE=$1
IN_DIR=$2
if [[ "$OUTFILE" == "" ]]; then
  echo -e "Output file not specified. Usage:\n  $0 <outfile> <directory>"
  exit 1
fi
if [[ "$IN_DIR" == "" ]]; then
  echo -e "Source directory not specified. Usage:\n  $0 <outfile> <directory>"
  exit 1
fi

IN_DIR_REAL=$(realpath "$IN_DIR")
if [[ "$IN_DIR_REAL" == "" ]]; then
  echo -e "Source directory not found. Refusing to continue"
  exit 1
fi

rm -rf "$OUTFILE"
touch "$OUTFILE"

while read -r temp ; do
  echo $temp
  echo "@FILE: $temp" >> "$OUTFILE"
  (cd $IN_DIR_REAL; objdump -t "$temp") >> "$OUTFILE"
done <<< $( (cd $IN_DIR_REAL; find -name "*.o"; find -name "*.a") | sort )
