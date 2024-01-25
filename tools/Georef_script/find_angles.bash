#!/bin/bash

# Define an array
my_array=("0" "45" "90" "135" "180" "225" "270" "315")

# Loop through the array
for roll in "${my_array[@]}"
do
	for pitch in "${my_array[@]}"
	do
		for heading in "${my_array[@]}"
		do
			
			rosrun logger lidarGeoreferencer -f -a -135 -b -45 -d 1 -e 50 -h $heading -p $pitch -r $roll -x 0.04667 -y -0.0362 -z -0.3473 -s $1 $2 > $3'/r'$roll'_p'$pitch'_h'$heading'.xyz'
		done
	done
done

