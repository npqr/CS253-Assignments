#!/bin/bash

### PART 1 ###

# $# is the number of arguments passed to the script

if [ "$#" != 2 ]; then
  echo "Usage: main.sh <input file> <output file>" # This is the usage message
  exit 1
fi

inp="$1"
outp="$2"

echo "Input File : $inp"
echo "Output File : $outp"

### PART 2 ###

# test -f checks if the file exists

if test -f $inp; then  
echo "Yay!, Input file named $inp exists"
else
echo "Gomen!, no such input file named $inp"
fi  

### PART 3 ###

# sorts and gets unique cities

echo "------------------"  > "$outp" 
echo "Unique cities in the given data file: " >> "$outp"

awk '

BEGIN {
    FS=", "; OFS=""; 
}

NR > 1 {
    print $3
}

' "$inp" | sort | uniq >> "$outp"

### PART 4 ###

# simple bubble sort to sort the salaries and then print the top 3
# we maintain 4 arrays to store the details of each individual
# we use a function swap to swap the elements of the array

echo "------------------" >> "$outp"
echo "Details of top 3 individuals with the highest salary: " >> "$outp"

awk '

BEGIN {
    FS=", "; OFS=", ";
}

{
    name[NR] = $1
    age[NR] = $2
    city[NR] = $3
    salary[NR] = $4
}

END {
    n = length(name)

    for (i = 1; i < n; i++) {
        for (j = 1; j < n - i; j++) {
            if ((salary[j] - 0) < (salary[j+1] - 0))
            {
                swap(name, j, j+1)
                swap(age, j, j+1)
                swap(city, j, j+1)
                swap(salary, j, j+1)
            }
        }
    }

    for (i = 1; i <= 3; i++)
        print name[i], age[i], city[i], salary[i] >> "'"$outp"'"

}

function swap(arr, i, j) {
    temp = arr[i]
    arr[i] = arr[j]
    arr[j] = temp
}

' "$inp" >> "$outp"


### PART 5 ###

# used two arrays to store sum and count of salaries for each city

echo "------------------" >> "$outp"
echo "Details of average salary of each city: " >> "$outp"

awk '

BEGIN {
    FS=", ";
}

NR > 1 { 
    sum[$3]+=$4;
    count[$3]++
} 

END {
    for (city in sum) 
        print "City: " city ", Salary: " sum[city]/count[city]
}

' "$inp" >> "$outp"

### PART 6 ###

# calculate overall average salary and then print accordingly
# we maintain 4 arrays to store the details of each individual

echo "------------------" >> "$outp"
echo "Details of individuals with a salary above the overall average salary: " >> "$outp"

awk '

BEGIN {
    FS=","; OFS=" "; sum=0; count=0;
}

NR > 1 {
    sum+=$4;
    count++;
    name[NR] = $1
    age[NR] = $2
    city[NR] = $3
    salary[NR] = $4
}

END {
    avg=sum/count

    for (i = 2; i <= NR; i++) 
        if(salary[i] - 0 > avg)
            print name[i], age[i], city[i], salary[i]  
}

' "$inp" >> "$outp"

echo "------------------" >> "$outp"

## Special note :

# Single > instead of >> ensures any file with name $outp will be overwritten
# Subsequent use of >> ensures anything is "appended" to $outp and not overwritten
# All the awk scripts are included in this file itself
# NR > 1 is used to skip the first line of the input file
# FS and OFS are used to set the field separator and output field separator respectively
# I did 'salary[i] - 0' to convert it into numerical value for comparison
# This is because, in the input file, salary is a string and not a number
# and thus would sort it lexicographically

### DONE ###

echo "Stuff done and exported to $outp!"
echo "Sayonara!"
