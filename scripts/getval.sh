#! /bin/bash


# read variable from the configuration file
# Usage:
# ../scripts/getval.sh output/config.tcl "centerRot(0)"
# ../scripts/getval.sh output/config.tcl omegaRot
function getval() {
    local ctrlfile=$1
    local pat=$2
    (printf "%s\n" "${tclarg:-}" ; cat $ctrlfile; printf "\nputs $%s\n" $pat)  | tclsh | tail -n 1
}

# if the file called directly
if [[ "$(basename "$0")" == "getval.sh" ]]; then
    if [[ "$#" != 2 ]]; then
	printf "(getval.sh) must have exactly two arguments: tcl file, variable name\n" > /dev/stderr
	exit 255
    fi
    if [[ ! -r "$1" ]]; then
	printf "(getval.sh) cannot read file: %s\n" "$1"  > /dev/stderr
	exit 255
    fi
    getval "$1" "$2"
fi
