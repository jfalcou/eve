#!/bin/sh

more $1 | jq "$2 | .[]" | tr -d '\"' | sed 's/\\\\/\\/g'
