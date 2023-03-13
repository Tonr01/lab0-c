# Test the speed of mysort
option fail 0
option malloc 0
new
ih RAND 500000
time sort
free