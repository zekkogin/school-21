#!/bin/bash

SUCCES_COUNTER=0
FAIL_COUNTER=0
DIFF_RES=""
echo "" > log.txt
TESTFILE="data.txt"

cat $TESTFILE > test1_cat.txt
./s21_cat $TESTFILE > test1_s21_cat.txt
DIFF_RES="$(diff -s test1_cat.txt test1_s21_cat.txt)"
if [ "$DIFF_RES" == "Files test1_cat.txt and test1_s21_cat.txt are identical" ]
then
(( SUCCES_COUNTER++ ))
else
(( FAIL_COUNTER++ ))
echo "$DIFF_RES" >> log.txt
fi

rm test1_cat.txt test1_s21_cat.txt

cat -b $TESTFILE > test1_cat.txt
./s21_cat -b $TESTFILE > test1_s21_cat.txt
DIFF_RES="$(diff -s test1_cat.txt test1_s21_cat.txt)"
if [ "$DIFF_RES" == "Files test1_cat.txt and test1_s21_cat.txt are identical" ]
then
(( SUCCES_COUNTER++ ))
else
(( FAIL_COUNTER++ ))
echo "$DIFF_RES" >> log.txt
fi

rm test1_cat.txt test1_s21_cat.txt

cat -e $TESTFILE > test1_cat.txt
./s21_cat -e $TESTFILE > test1_s21_cat.txt
DIFF_RES="$(diff -s test1_cat.txt test1_s21_cat.txt)"
if [ "$DIFF_RES" == "Files test1_cat.txt and test1_s21_cat.txt are identical" ]
then
(( SUCCES_COUNTER++ ))
else
(( FAIL_COUNTER++ ))
echo "$DIFF_RES" >> log.txt
fi

rm test1_cat.txt test1_s21_cat.txt

cat -n $TESTFILE > test1_cat.txt
./s21_cat -n $TESTFILE > test1_s21_cat.txt
DIFF_RES="$(diff -s test1_cat.txt test1_s21_cat.txt)"
if [ "$DIFF_RES" == "Files test1_cat.txt and test1_s21_cat.txt are identical" ]
then
(( SUCCES_COUNTER++ ))
else
(( FAIL_COUNTER++ ))
echo "$DIFF_RES" >> log.txt
fi

rm test1_cat.txt test1_s21_cat.txt

cat -s $TESTFILE > test1_cat.txt
./s21_cat -s $TESTFILE > test1_s21_cat.txt
DIFF_RES="$(diff -s test1_cat.txt test1_s21_cat.txt)"
if [ "$DIFF_RES" == "Files test1_cat.txt and test1_s21_cat.txt are identical" ]
then
(( SUCCES_COUNTER++ ))
else
(( FAIL_COUNTER++ ))
echo "$DIFF_RES" >> log.txt
fi

rm test1_cat.txt test1_s21_cat.txt

cat -t $TESTFILE > test1_cat.txt
./s21_cat -t $TESTFILE > test1_s21_cat.txt
DIFF_RES="$(diff -s test1_cat.txt test1_s21_cat.txt)"
if [ "$DIFF_RES" == "Files test1_cat.txt and test1_s21_cat.txt are identical" ]
then
(( SUCCES_COUNTER++ ))
else
(( FAIL_COUNTER++ ))
echo "$DIFF_RES" >> log.txt
fi

rm test1_cat.txt test1_s21_cat.txt

cat -v $TESTFILE > test1_cat.txt
./s21_cat -v $TESTFILE > test1_s21_cat.txt
DIFF_RES="$(diff -s test1_cat.txt test1_s21_cat.txt)"
if [ "$DIFF_RES" == "Files test1_cat.txt and test1_s21_cat.txt are identical" ]
then
(( SUCCES_COUNTER++ ))
else
(( FAIL_COUNTER++ ))
echo "$DIFF_RES" >> log.txt
fi

rm test1_cat.txt test1_s21_cat.txt

cat -benstv $TESTFILE > test1_cat.txt
./s21_cat -benstv $TESTFILE > test1_s21_cat.txt
DIFF_RES="$(diff -s test1_cat.txt test1_s21_cat.txt)"
if [ "$DIFF_RES" == "Files test1_cat.txt and test1_s21_cat.txt are identical" ]
then
(( SUCCES_COUNTER++ ))
else
(( FAIL_COUNTER++ ))
echo "$DIFF_RES" >> log.txt
fi

rm test1_cat.txt test1_s21_cat.txt

# cat -T $TESTFILE > test1_cat.txt
# ./s21_cat -T $TESTFILE > test1_s21_cat.txt
# DIFF_RES="$(diff -s test1_cat.txt test1_s21_cat.txt)"
# if [ "$DIFF_RES" == "Files test1_cat.txt and test1_s21_cat.txt are identical" ]
# then
# (( SUCCES_COUNTER++ ))
# else
# (( FAIL_COUNTER++ ))
# echo "$DIFF_RES" >> log.txt
# fi

# rm test1_cat.txt test1_s21_cat.txt

# cat -E $TESTFILE > test1_cat.txt
# ./s21_cat -E $TESTFILE > test1_s21_cat.txt
# DIFF_RES="$(diff -s test1_cat.txt test1_s21_cat.txt)"
# if [ "$DIFF_RES" == "Files test1_cat.txt and test1_s21_cat.txt are identical" ]
# then
# (( SUCCES_COUNTER++ ))
# else
# (( FAIL_COUNTER++ ))
# echo "$DIFF_RES" >> log.txt
# fi

# rm test1_cat.txt test1_s21_cat.txt

# cat --number-nonblank $TESTFILE > test1_cat.txt
# ./s21_cat --number-nonblank $TESTFILE > test1_s21_cat.txt
# DIFF_RES="$(diff -s test1_cat.txt test1_s21_cat.txt)"
# if [ "$DIFF_RES" == "Files test1_cat.txt and test1_s21_cat.txt are identical" ]
# then
# (( SUCCES_COUNTER++ ))
# else
# (( FAIL_COUNTER++ ))
# echo "$DIFF_RES" >> log.txt
# fi

# rm test1_cat.txt test1_s21_cat.txt

echo "SUCCESS: $SUCCES_COUNTER"
echo "FAIL: $FAIL_COUNTER"
cat log.txt