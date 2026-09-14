GREEN="\033[32m"
RED="\033[31m"
RESET="\033[0m"

SUCCESS=0
FAIL=0
COUNTER=0

FILE_NORMAL="test_normal.txt"
FILE_FLAGS="test_flags.txt"

echo -e "Hello World!\nThis is line 2.\n\nLine 4 after empty line." > $FILE_NORMAL

printf "Line 1\n\n\nLine 4 with tab:\tEndTab\n\n   Line 6 spaces\n\n" > $FILE_FLAGS
printf "\x01\x02\x1f\x7f\x15" >> $FILE_FLAGS

run_test() {
    local test_args="$1"
    ((COUNTER++))

    ./s21_cat $test_args > res_s21.log 2>&1
    cat $test_args > res_orig.log 2>&1
    
    if diff -q res_s21.log res_orig.log > /dev/null; then
        echo -e "[ $COUNTER ] Args: '$test_args' -> ${GREEN}SUCCESS${RESET}"
        ((SUCCESS++))
    else
        echo -e "[ $COUNTER ] Args: '$test_args' -> ${RED}FAIL${RESET}"
        echo "--- Различия (Выш код < | Оригинал >) ---"
        diff res_s21.log res_orig.log | head -n 10
        echo "----------------------------------------"
        ((FAIL++))
    fi
}

echo "=== ЗАПУСК ТЕСТОВ ДЛЯ S21_CAT ==="

run_test "-b $FILE_FLAGS"
run_test "-e $FILE_FLAGS"
run_test "-n $FILE_FLAGS"
run_test "-s $FILE_FLAGS"
run_test "-t $FILE_FLAGS"
run_test "-v $FILE_FLAGS"
run_test "-E $FILE_FLAGS"
run_test "-T $FILE_FLAGS"
run_test "--number-nonblank $FILE_FLAGS"
run_test "--number $FILE_FLAGS"
run_test "--squeeze-blank $FILE_FLAGS"
run_test "-b -n $FILE_FLAGS"
run_test "-n -b $FILE_FLAGS"
run_test "-s -n -e $FILE_FLAGS"
run_test "$FILE_NORMAL $FILE_FLAGS"
run_test "-n $FILE_NORMAL $FILE_FLAGS"

rm -f res_s21.log res_orig.log $FILE_NORMAL $FILE_FLAGS

echo "=============================="
echo -e "Всего тестов: $COUNTER | ${GREEN}Успешно: $SUCCESS${RESET} | ${RED}Упало: $FAIL${RESET}"

if [ $FAIL -ne 0 ]; then exit 1; fi
