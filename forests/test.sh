#!/bin/bash

PROG=$1
DIR=$2

$(test -e ${PWD}/$PROG)
if [ $? -eq 1 ]
then echo "W tym katalogu nie istnieje plik $PROG !!!"
else

	OUT=$(mktemp)
	ERR=$(mktemp)
	VLG=$(mktemp)

	for f in $DIR/*.in
	do

		valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --log-file=$VLG ./$PROG < $f 1> $OUT 2> $ERR

		if [ $? -eq 0 ]
		then
			if diff -q $OUT ${f%in}out
			then
				if diff -q $ERR ${f%in}err
				then echo "$f - AC"
				else echo "$f - WA !!!"
				fi
			else echo "$f - WA !!!"
			fi
		else echo "$f - ME !!!"
		fi

	done

	rm $OUT $ERR $VLG

fi