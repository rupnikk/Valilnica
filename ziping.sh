#!/bin/bash

#example: ./ziping.sh name.zip dir/project_name

name=$1

if [[ -n "$name" ]]; then
    zip "$name" "$2-F.Cu.gtl" "$2-B.Cu.gbl" "$2-Edge.Cuts.gm1" "$2.drl"
    echo "Ok"
else
    echo "argument error"
fi
