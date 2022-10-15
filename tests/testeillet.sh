# MINISHELL-TESTER

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"
BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

MSHELL_PATH=../

PASS=0
FAIL=0

clean() {
	rm file file1 file2 file3 lol ls bla
}

get_test() {
	if ! [ -f "${MSHELL_PATH}minishell" ]; then
		printf "${RED}ERROR${RESET}: Minishell path doesn't contain the executable\n"
		exit 1
	fi
	for var in $@; do
		if [ "${var::1}" = "-" ]; then
			continue
		fi
		if [ ! -f "$var" ]; then
			printf "File '$var' does not exist\n"
			continue
		fi
		while IFS= read -r line; do
			run_test $line
		done < "$var"
	done
}

run_test() {
	TEST1=$(echo $line "; exit" | ${MSHELL_PATH}minishell 2>/dev/null)
	ES_1=$?
	TEST2=$(echo $line "; exit" | bash 2>/dev/null)
	ES_2=$?
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
		printf " $BOLDGREEN%s$RESET" "✓ "
		let PASS++
	else
		printf " $BOLDRED%s$RESET" "✗ "
		let FAIL++
	fi
	printf "$CYAN \"$line\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		printf $RED"  - Your output : \t$RED$TEST1$RESET\n"
		printf $GREEN"  - Expected output : \t$GREEN$TEST2$RESET\n"
	fi
	if [ "$ES_1" != "$ES_2" ]; then
		echo
		printf $RED"  - Your exit status : $RED$ES_1$RESET\n"
		printf $GREEN"  - Expected exit status : $GREEN$ES_2$RESET\n"
	fi
	sleep 0.1
}

test_results()
{
	echo
	printf $BOLDWHITE
	echo ----- TEST RESULTS -----
	printf "  - Passed = "
	echo $PASS
	printf "  - Failed = "
	echo $FAIL
	printf "\n$RESET"
}

get_test $@
test_results
clean
