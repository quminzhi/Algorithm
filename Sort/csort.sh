#!/bin/bash
# Program:
#   This program is used to make comparison among various sorting algorithms.
#
# Author: Minzhi Qu
# University of Washington, Tacoma
# quminzhi@gmail.com

echo -e "The script is used to test the performance of different sorting algorithms."
read -p "Please input executable file: " -t 30 file
read -p "Please input test data: " -t 30 data

file=${file:-"csort"}
data=${data:-"random_data_01"}
output="result"

MAX_SIZE=1000000

# TODO: input check
if [ ! -e $file ]; then
    echo -e "Error: file $file is not found."
    exit 240
fi

if [ ! -e $data ]; then
    echo -e "Error: file $data is not found."
    exit 240
fi

# TODO: test for given data
printf "test for bubble sort: running...\n"
printf "Test: Bubble Sort\n" > $output
for (( i=1000; i<$MAX_SIZE/100; i=i*2))
do
    printf "# of test data: $i  -->  " >> $output
    { time -v ./csort -c bubble -f $data -n $i; } 2>> $output
    printf "\n" >> $output
done
printf "Done: Bubble Sort\n\n" >> $output
printf "test for bubble sort: done.\n"

printf "test for insertion sort: running...\n"
printf "Test: Insertion Sort\n" >> $output
for (( i=1000; i<$MAX_SIZE/10; i=i*2))
do
    printf "# of test data: $i  -->  " >> $output
    { time ./csort -c insertion -f $data -n $i; } 2>> $output
    printf "\n" >> $output
done
printf "Done: Insertion Sort\n\n" >> $output
printf "test for insertion sort: done.\n"

printf "test for seletion sort: running...\n"
printf "Test: Selection Sort\n" >> $output
for (( i=1000; i<$MAX_SIZE/10; i=i*2))
do
    printf "# of test data: $i  -->  " >> $output
    { time ./csort -c selection -f $data -n $i; } 2>> $output
    printf "\n" >> $output
done
printf "Done: Selection Sort\n" >> $output
printf "test for selection sort: done.\n"

printf "test for merge sort: running...\n"
printf "Test: Merge Sort\n" >> $output
for (( i=1000; i<$MAX_SIZE; i=i*2))
do
    printf "# of test data: $i  -->  " >> $output
    { time ./csort -c merge -f $data -n $i; } 2>> $output
    printf "\n" >> $output
done
printf "Done: Merge Sort\n" >> $output
printf "test for merge sort: done.\n"

printf "test for quick sort: running...\n"
printf "Test: Quick Sort\n" >> $output
for (( i=1000; i<$MAX_SIZE; i=i*2))
do
    printf "# of test data: $i  -->  " >> $output
    { time ./csort -c qsort -f $data -n $i; } 2>> $output
    printf "\n" >> $output
done
printf "Done: Quick Sort\n" >> $output
printf "test for quick sort: done.\n"

printf "all works done.\n"

exit 0
