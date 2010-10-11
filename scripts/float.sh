#!/bin/bash
#
# Evaluate a floatin' point number expression.
# Usage:
# directly: ./float.sh "4+5"
# in bash script 
# source float.sh
# echo $(float_eval "4+5")

function float_eval()
{
    if [ $# -ne 1 ]; then
	printf "float.sh:%i: number of arguments should be 1, %i given\n" $LINENO $# > "/dev/stderr"
	printf "float.sh:%i: arguments: $*\n" $LINENO > "/dev/stderr"
	exit 2
    fi
    local expr=$1
    local stat=0
    result=$(awk "BEGIN {print $expr}")
    stat=$?
    if [[ $stat -eq 0  &&  -z "$result" ]]; then stat=1; fi
    echo $result
    return $stat
}

# Test code if invoked directly.
if [[ $(basename "$0" .sh) == 'float' ]]; then
    # Use comman' line arguments if thar be any.
    if [[ $# -gt 0 ]]; then
        echo $(float_eval $*)
    else
        # Turn off pathname expansion so * doesn't get expanded
        set -f
        e="12.5 / 3.2"
        echo $e is $(float_eval "$e")
        e="100.4 / 4.2 + 3.2 * 6.5"
        echo $e is $(float_eval "$e")
        e="1e-15 + 1e-45"
        echo $e is $(float_eval "$e")
        a=12.0
        b=3.0
        c=$(float_eval "$a / $b")
        echo "$a / $b" is $c
        set +f
    fi
fi
