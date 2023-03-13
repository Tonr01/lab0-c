# Test the speed of list_sort
option fail 0
option malloc 0
new
ih RAND 500000
time list_sort
free