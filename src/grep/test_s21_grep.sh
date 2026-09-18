GREEN="\033[32m"
RED="\033[31m"
RESET="\033[0m"

SUCCESS=0
FAIL=0
COUNTER=0

FILE1="grep_t1.txt"
FILE2="grep_t2.txt"
PATTERNS_FILE="patterns.txt"

echo -e "apple\nBANANA\ncherry\napple pie\n12345\nmy sweet apple" > $FILE1
echo -e "banana\nCHERRY\napple\n98765" > $FILE2
echo -e "apple" > $PATTERNS_FILE

run_test() {
    local args="$1"
    COUNTER=$((COUNTER + 1))
    
    eval "./s21_grep $args" > res_s21.log 2>&1
    eval "grep $args" > res_orig.log 2>&1
    
    if diff -q res_s21.log res_orig.log > /dev/null; then
        echo -e "[ $COUNTER ] Args: '$args' -> ${GREEN}SUCCESS${RESET}"
        SUCCESS=$((SUCCESS + 1))
    else
        echo -e "[ $COUNTER ] Args: '$args' -> ${RED}FAIL${RESET}"
        echo "--- Различия (Ваш < | Оригинал >) ---"
        diff res_s21.log res_orig.log | head -n 3
        echo "-------------------------------------"
        FAIL=$((FAIL + 1))
    fi
}

echo "=== ЗАПУСК ТЕСТОВ ДЛЯ S21_GREP ==="

run_test "'apple' $FILE1"
run_test "'^[0-9]' $FILE1"
run_test "-e 'cherry' $FILE1"
run_test "-f $PATTERNS_FILE $FILE1"
run_test "-i 'APPLE' $FILE1"
run_test "-v 'apple' $FILE1"
run_test "-c 'apple' $FILE1"
run_test "-l 'apple' $FILE1"
run_test "-n 'apple' $FILE1"
run_test "-o 'apple' $FILE1"
run_test "'apple' $FILE1 $FILE2"
run_test "-h 'apple' $FILE1 $FILE2"
run_test "-s 'apple' non_existent_file.txt"

rm -f res_s21.log res_orig.log $FILE1 $FILE2 $PATTERNS_FILE

echo "=============================="
echo -e "Всего тестов: $COUNTER | ${GREEN}Успешно: $SUCCESS${RESET} | ${RED}Упало: $FAIL${RESET}"

if [ $FAIL -ne 0 ]; then exit 1; fi
