#!/bin/bash

# COUNTER_SUCCESS=0
# COUNTER_FAIL=0
# DIFF_RES=""
# echo "" > log.txt

#     TEST1="-e abc -i s21_grep.c"
#     echo "$TEST1"
#     ./s21_grep $TEST1 > s21_grep.txt
#     grep $TEST1 > grep.txt
#     DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
#     if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
#       then
#         (( COUNTER_SUCCESS++ ))
#       else
#         echo "$TEST1" >> log.txt
#         (( COUNTER_FAIL++ ))
#     fi


#     TEST1="-e abc -v s21_grep.c"
#     echo "$TEST1"
#     ./s21_grep $TEST1 > s21_grep.txt
#     grep $TEST1 > grep.txt
#     DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
#     if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
#       then
#         (( COUNTER_SUCCESS++ ))
#       else
#         echo "$TEST1" >> log.txt
#         (( COUNTER_FAIL++ ))
#     fi


#     TEST1="-e abc -c s21_grep.c"
#     echo "$TEST1"
#     ./s21_grep $TEST1 > s21_grep.txt
#     grep $TEST1 > grep.txt
#     DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
#     if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
#       then
#         (( COUNTER_SUCCESS++ ))
#       else
#         echo "$TEST1" >> log.txt
#         (( COUNTER_FAIL++ ))
#     fi


#     TEST1="-e abc -l s21_grep.c"
#     echo "$TEST1"
#     ./s21_grep $TEST1 > s21_grep.txt
#     grep $TEST1 > grep.txt
#     DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
#     if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
#       then
#         (( COUNTER_SUCCESS++ ))
#       else
#         echo "$TEST1" >> log.txt
#         (( COUNTER_FAIL++ ))
#     fi


#     TEST1="-e abc -n s21_grep.c"
#     echo "$TEST1"
#     ./s21_grep $TEST1 > s21_grep.txt
#     grep $TEST1 > grep.txt
#     DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
#     if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
#       then
#         (( COUNTER_SUCCESS++ ))
#       else
#         echo "$TEST1" >> log.txt
#         (( COUNTER_FAIL++ ))
#     fi

# echo "SUCCESS: $COUNTER_SUCCESS"
# echo "FAIL: $COUNTER_FAIL"











# out1=s21_GrepTest.txt
# out2=GrepTest.txt
# num=0
# pattern=the
# pattern_file=pattern1.txt
# file2=text8.txt

# echo "----|TESTS FOR ONE FILES|----"
# for flag in e i v c l n
# do
#     ((num++))
#     echo "----------------------------------------"
#     echo "Test  #$num  flags:  -$flag"
#     echo "Template: $pattern"
#     echo "----------------------------------------"
#     for file in text1.txt text4.txt text8.txt
#     do
#         ./s21_grep -$flag $pattern $file > $out1
#         grep -$flag $pattern $file > $out2
#     done
#     diff -s $out1 $out2
# done

# echo "   "
# echo "----|TESTS FOR SEVERAL FILES|----"
# for flag in e i v c l n
# do
#     ((num++))
#     echo "----------------------------------------"
#     echo "Test  #$num  flags:  -$flag"
#     echo "Template: $pattern"
#     echo "----------------------------------------"
#     for file in text1.txt text4.txt
#     do
#         ./s21_grep -$flag $pattern $file $file2 > $out1
#         grep -$flag $pattern $file $file2 > $out2
#     done
#     diff -s $out1 $out2
# done

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
// echo "" > log.txt

for var in -e -i -v -c -l -n
do
    TEST1="ABS tests/test_regex.c  $var"
    echo "$TEST1"
    ./s21_grep $TEST1 > s21_grep.txt
    grep $TEST1 > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        (( COUNTER_SUCCESS++ ))
      else
        echo "$TEST1" >> log.txt
        (( COUNTER_FAIL++ ))
    fi
    # rm s21_grep.txt grep.txt

    TEST2="for tests/test_regex.c $var"
    echo "$TEST2"
    ./s21_grep $TEST2 > s21_grep.txt
    grep $TEST2 > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        (( COUNTER_SUCCESS++ ))
      else
        echo "$TEST2" >> log.txt
        (( COUNTER_FAIL++ ))
    fi
  #   # rm s21_grep.txt grep.txt

    TEST3="-e for -e int grep.c $var"
    echo "$TEST3"
    ./s21_grep $TEST3 > s21_grep.txt
    grep $TEST3 > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        (( COUNTER_SUCCESS++ ))
      else
        echo "$TEST3" >> log.txt
        (( COUNTER_FAIL++ ))
    fi
  #   # rm s21_grep.txt grep.txt

  TEST3.1="-e for -e ^int grep.c grep.h Makefile $var"
    echo "$TEST3"
    ./s21_grep $TEST3 > s21_grep.txt
    grep $TEST3 > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        (( COUNTER_SUCCESS++ ))
      else
        echo "$TEST3" >> log.txt
        (( COUNTER_FAIL++ ))
    fi
  #   # rm s21_grep.txt grep.txt


    TEST4="-e for -e ^int grep.c $var"
    echo "$TEST4"
    ./s21_grep $TEST4 > s21_grep.txt
    grep $TEST4 > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        (( COUNTER_SUCCESS++ ))
      else
        echo "$TEST4" >> log.txt
        (( COUNTER_FAIL++ ))
    fi
  #   # rm s21_grep.txt grep.txt

    TEST5="-e regex -e ^print grep.c $var pattern.txt"
    echo "$TEST5"
    ./s21_grep $TEST5 > s21_grep.txt
    grep $TEST5 > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        (( COUNTER_SUCCESS++ ))
      else
        echo "$TEST5" >> log.txt
        (( COUNTER_FAIL++ ))
    fi
  #   # rm s21_grep.txt grep.txt

    TEST6="-e while -e void grep.c Makefile $var pattern.txt"
    echo "$TEST6"
    ./s21_grep $TEST6 > s21_grep.txt
    grep $TEST6 > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        (( COUNTER_SUCCESS++ ))
      else
        echo "$TEST6" >> log.txt
        (( COUNTER_FAIL++ ))
    fi
  #   # rm s21_grep.txt grep.txt

    TEST7="-e regex -e ^print grep.c $var pattern2.txt"
    echo "$TEST7"
    ./s21_grep $TEST7 > s21_grep.txt
    grep $TEST7 > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        (( COUNTER_SUCCESS++ ))
      else
        echo "$TEST7" >> log.txt
        (( COUNTER_FAIL++ ))
    fi
  #   # rm s21_grep.txt grep.txt

    TEST8="-e while -e void grep.c Makefile $var pattern2.txt"
    echo "$TEST8"
    ./s21_grep $TEST8 > s21_grep.txt
    grep $TEST8 > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        (( COUNTER_SUCCESS++ ))
      else
        echo "$TEST8" >> log.txt
        (( COUNTER_FAIL++ ))
    fi
  #   # rm s21_grep.txt grep.txt

    TEST9="-e regex -e ^print grep.c $var pattern3.txt"
    echo "$TEST9"
    ./s21_grep $TEST9 > s21_grep.txt
    grep $TEST9 > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        (( COUNTER_SUCCESS++ ))
      else
        echo "$TEST9" >> log.txt
        (( COUNTER_FAIL++ ))
    fi
  #   # rm s21_grep.txt grep.txt

    TEST10="-e while -e void grep.c Makefile $var pattern3.txt"
    echo "$TEST10"
    ./s21_grep $TEST10 > s21_grep.txt
    grep $TEST10 > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        (( COUNTER_SUCCESS++ ))
      else
        echo "$TEST10" >> log.txt
        (( COUNTER_FAIL++ ))
    fi
    # rm s21_grep.txt grep.txt

    TEST11="-e regex -e ^print grep.c $var pattern.txt  pattern2.txt"
    echo "$TEST11"
    ./s21_grep $TEST11 > s21_grep.txt
    grep $TEST11 > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        (( COUNTER_SUCCESS++ ))
      else
        echo "$TEST11" >> log.txt
        (( COUNTER_FAIL++ ))
    fi
    # rm s21_grep.txt grep.txt

    TEST12="-e while -e void grep.c Makefile $var pattern.txt pattern2.txt"
    echo "$TEST12"
    ./s21_grep $TEST12 > s21_grep.txt
    grep $TEST12 > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        (( COUNTER_SUCCESS++ ))
      else
        echo "$TEST12" >> log.txt
        (( COUNTER_FAIL++ ))
    fi
    # rm s21_grep.txt grep.txt

    TEST13="-e regex -e ^print grep.c $var pattern.txt pattern2.txt pattern3.txt"
    echo "$TEST13"
    ./s21_grep $TEST13 > s21_grep.txt
    grep $TEST13 > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        (( COUNTER_SUCCESS++ ))
      else
        echo "$TEST13" >> log.txt
        (( COUNTER_FAIL++ ))
    fi
    # rm s21_grep.txt grep.txt

    TEST14="-e while -e void grep.c Makefile $var pattern.txt pattern2.txt pattern3.txt"
    echo "$TEST14"
    ./s21_grep $TEST14 > s21_grep.txt
    grep $TEST14 > grep.txt
    DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
    if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        (( COUNTER_SUCCESS++ ))
      else
        echo "$TEST14" >> log.txt
        (( COUNTER_FAIL++ ))
    fi
    # rm s21_grep.txt grep.txt
done

for var in -e -i -v -c -l -n
do
  for var2 in -e -i -v -c -l -n
  do
        if [ $var != $var2 ]
        then

          TEST1="for grep.c grep.h Makefile $var $var2"
          echo "$TEST1"
          ./s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
#           # rm s21_grep.txt grep.txt

          TEST2="for grep.c $var $var2"
          echo "$TEST2"
          ./s21_grep $TEST2 > s21_grep.txt
          grep $TEST2 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST2" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
#           # rm s21_grep.txt grep.txt

          TEST3="-e for -e ^int grep.c grep.h Makefile $var $var2"
          echo "$TEST3"
          ./s21_grep $TEST3 > s21_grep.txt
          grep $TEST3 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST3" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
#           # rm s21_grep.txt grep.txt

          TEST4="-e for -e ^int grep.c $var $var2"
          echo "$TEST4"
          ./s21_grep $TEST4 > s21_grep.txt
          grep $TEST4 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST4" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
#           # rm s21_grep.txt grep.txt

#           TEST5="-e regex -e ^print grep.c $var $var2 -f tests/pattern.txt"
#           echo "$TEST5"
#           ./s21_grep $TEST5 > s21_grep.txt
#           grep $TEST5 > grep.txt
#           DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
#           if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
#             then
#               (( COUNTER_SUCCESS++ ))
#             else
#               echo "$TEST5" >> log.txt
#               (( COUNTER_FAIL++ ))
#           fi
# #           # rm s21_grep.txt grep.txt

#           TEST6="-e while -e void grep.c Makefile $var $var2 -f tests/pattern.txt"
#           echo "$TEST6"
#           ./s21_grep $TEST6 > s21_grep.txt
#           grep $TEST6 > grep.txt
#           DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
#           if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
#             then
#               (( COUNTER_SUCCESS++ ))
#             else
#               echo "$TEST6" >> log.txt
#               (( COUNTER_FAIL++ ))
#           fi
          # rm s21_grep.txt grep.txt
# доработать f
          # TEST7="-e regex -e ^print grep.c $var $var2 -f tests/pattern2.txt"
          # echo "$TEST7"
          # ./s21_grep $TEST7 > s21_grep.txt
          # grep $TEST7 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST7" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

          # TEST8="-e while -e void grep.c Makefile $var $var2 -f pattern2.txt"
          # echo "$TEST8"
          # ./s21_grep $TEST8 > s21_grep.txt
          # grep $TEST8 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST8" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

          # TEST9="-e regex -e ^print grep.c $var $var2 -f pattern3.txt"
          # echo "$TEST9"
          # ./s21_grep $TEST9 > s21_grep.txt
          # grep $TEST9 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST9" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

          # TEST10="-e while -e void grep.c Makefile $var $var2 $var3 -f pattern3.txt"
          # echo "$TEST10"
          # ./s21_grep $TEST10 > s21_grep.txt
          # grep $TEST10 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST10" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

          # TEST11="-e regex -e ^print grep.c $var $var2 $var3 -f pattern.txt -f pattern2.txt"
          # echo "$TEST11"
          # ./s21_grep $TEST11 > s21_grep.txt
          # grep $TEST11 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST11" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

          # TEST12="-e while -e void grep.c Makefile $var $var2 $var3 -f pattern.txt -f pattern2.txt"
          # echo "$TEST12"
          # ./s21_grep $TEST12 > s21_grep.txt
          # grep $TEST12 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST12" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

          # TEST13="-e regex -e ^print grep.c $var $var2 $var3 -f pattern.txt -f pattern2.txt pattern3.txt"
          # echo "$TEST13"
          # ./s21_grep $TEST13 > s21_grep.txt
          # grep $TEST13 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST13" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

          # TEST14="-e while -e void grep.c Makefile $var $var2 $var3 -f pattern.txt -f pattern2.txt pattern3.txt"
          # echo "$TEST14"
          # ./s21_grep $TEST14 > s21_grep.txt
          # grep $TEST14 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST14" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

     fi     
  done
done

# for var in -v -c -l -n -h -s -i #-o
# do
#   for var2 in -v -c -l -n -h -s -i #-o
#   do
#       for var3 in -v #-c -l -n -h -s -i #-o
#       do
#         if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
#         then
          # TEST1="for grep.c grep.h Makefile $var $var2 $var3"
          # echo "$TEST1"
          # ./s21_grep $TEST1 > s21_grep.txt
          # grep $TEST1 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST1" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
#           rm s21_grep.txt grep.txt

          # TEST2="for grep.c $var $var2 $var3"
          # echo "$TEST2"
          # ./s21_grep $TEST2 > s21_grep.txt
          # grep $TEST2 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST2" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

          # TEST3="-e for -e ^int grep.c grep.h Makefile $var $var2 $var3"
          # echo "$TEST3"
          # ./s21_grep $TEST3 > s21_grep.txt
          # grep $TEST3 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST3" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

          # TEST4="-e for -e ^int grep.c $var $var2 $var3"
          # echo "$TEST4"
          # ./s21_grep $TEST4 > s21_grep.txt
          # grep $TEST4 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST4" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

          # TEST5="-e regex -e ^print grep.c $var $var2 $var3 -f pattern.txt"
          # echo "$TEST5"
          # ./s21_grep $TEST5 > s21_grep.txt
          # grep $TEST5 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST5" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

          # TEST6="-e while -e void grep.c Makefile $var $var2 $var3 -f pattern.txt"
          # echo "$TEST6"
          # ./s21_grep $TEST6 > s21_grep.txt
          # grep $TEST6 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST6" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

          # TEST7="-e regex -e ^print grep.c $var $var2 $var3 -f pattern2.txt"
          # echo "$TEST7"
          # ./s21_grep $TEST7 > s21_grep.txt
          # grep $TEST7 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST7" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

          # TEST8="-e while -e void grep.c Makefile $var $var2 $var3 -f pattern2.txt"
          # echo "$TEST8"
          # ./s21_grep $TEST8 > s21_grep.txt
          # grep $TEST8 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST8" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

          # TEST9="-e regex -e ^print grep.c $var $var2 $var3 -f pattern3.txt"
          # echo "$TEST9"
          # ./s21_grep $TEST9 > s21_grep.txt
          # grep $TEST9 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST9" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

          # TEST10="-e while -e void grep.c Makefile $var $var2 $var3 -f pattern3.txt"
          # echo "$TEST10"
          # ./s21_grep $TEST10 > s21_grep.txt
          # grep $TEST10 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST10" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

          # TEST11="-e regex -e ^print grep.c $var $var2 $var3 -f pattern.txt -f pattern2.txt"
          # echo "$TEST11"
          # ./s21_grep $TEST11 > s21_grep.txt
          # grep $TEST11 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST11" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

          # TEST12="-e while -e void grep.c Makefile $var $var2 $var3 -f pattern.txt -f pattern2.txt"
          # echo "$TEST12"
          # ./s21_grep $TEST12 > s21_grep.txt
          # grep $TEST12 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST12" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

          # TEST13="-e regex -e ^print grep.c $var $var2 $var3 -f pattern.txt -f pattern2.txt pattern3.txt"
          # echo "$TEST13"
          # ./s21_grep $TEST13 > s21_grep.txt
          # grep $TEST13 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST13" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

          # TEST14="-e while -e void grep.c Makefile $var $var2 $var3 -f pattern.txt -f pattern2.txt pattern3.txt"
          # echo "$TEST14"
          # ./s21_grep $TEST14 > s21_grep.txt
          # grep $TEST14 > grep.txt
          # DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          # if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
          #   then
          #     (( COUNTER_SUCCESS++ ))
          #   else
          #     echo "$TEST14" >> log.txt
          #     (( COUNTER_FAIL++ ))
          # fi
          # rm s21_grep.txt grep.txt

#         fi
#       done
#   done
# done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"