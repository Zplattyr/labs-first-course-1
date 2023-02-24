#!/bin/bash

sym="$1"
len="$2"

for file in $(pwd)/*
	do
    filename=$(basename $file)
	name=${filename%.*}
    suf=${filename##*.}

    while [ $len -gt ${#name} ]; do
	    name="$name""$sym"
    done

    if ! [[ "$name" == "${filename%.*}" ]] && [[ -f $file ]] && ! [[ "$suf" == "sh" ]]; then
        mv "$filename" "$name"."$suf"
    fi
done
