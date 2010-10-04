#! /bin/bash

# get rid of extra include's

dirnames=". ../plugins/ ../cpptcl"

#inclist=$(

for fname in $(find ${dirnames} -name '*.cpp' ) $(find ${dirnames} -name '*.h' ); do
    printf "processing: $fname \n"
    grep '\#include' "${fname}" > "${fname}.inc"

    while read -r line
    do
	# back up file
	# comment line 
	printf "trying: $fname: $line\n" 
	cp "${fname}" "${fname}".backup 
	sed -e "s,$line,//$line,g" "${fname}.backup" > "${fname}"
	if make 2>/dev/null > make.log; then
	    # do nothing 
	    printf "success with: $fname: $line\n" 
	else
	    # restore from backup
	    printf "failed with: $fname: $line\n" 
	    cp "${fname}.backup"  "${fname}"
	fi
    done < "${fname}.inc"
done