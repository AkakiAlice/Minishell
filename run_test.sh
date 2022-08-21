test_lists=(
	# "simple_cmd"
	"sintax"
	# "pipes"
	# "redirects"
)

BOLD="\e[1m"
YELLOW="\033[0;33m"
GREY="\033[38;5;244m"
PURPLE="\033[0;35m"
BLUE="\033[0;36m"
RED="\e[0;31m"
END="\033[0m"

chmod 000 ./unit_test/test_files/invalid_permission
mkdir ./outfiles
mkdir ./mini_outfiles
mkdir ./bash_outfiles

printf $YELLOW
printf "\n****************** MINISHELL TESTER ******************\n\n"

PROMPT=$(echo -e "\nexit\n" | ./minishell | head -n 1 | sed -r "s:\x1B\[[0-9;]*[mK]::g")

for testfile in ${test_lists[*]}; do

	printf $PURPLE
	echo ———————————— $testfile

	while read teste; do

		((i++))

		rm -rf ./outfiles/*
		rm -rf ./mini_outfiles/*
		MINI_OUTPUT=$(echo -e "$teste" | ./minishell 2> /dev/null | sed -r "s:\x1B\[[0-9;]*[mK]::g" | grep -v "$PROMPT" | grep -v ^exit$ )
		MINI_OUTFILES=$(cp ./outfiles/* ./mini_outfiles &>/dev/null)
		MINI_EXIT_CODE=$(echo -e "./minishell\n$teste\necho \$?\nexit\n" | ./minishell 2> /dev/null | sed -r "s:\x1B\[[0-9;]*[mK]::g" | grep -v "$PROMPT" | grep -v ^exit$ | tail -n 1)
		MINI_ERROR_MSG=$(echo "$teste" | ./minishell 2>&1 > /dev/null | grep -o '[^:]*$' | head -n1)

		rm -rf ./outfiles/*
		rm -rf ./bash_outfiles/*
		BASH_OUTPUT=$(LC_COLLATE=C bash -c "$teste" 2> /dev/null)
		BASH_EXIT_CODE=$(echo $?)
		BASH_OUTFILES=$(cp ./outfiles/* ./bash_outfiles &>/dev/null)
		BASH_ERROR_MSG=$(LC_COLLATE=C bash -c "$teste" 2>&1 > /dev/null | grep -o '[^:]*$'  | head -n1)

		OUTFILES_DIFF=$(diff --brief ./mini_outfiles ./bash_outfiles)

		printf $BLUE
		printf "\nTest %3s: " $i
		if [[ "$MINI_OUTPUT" == "$BASH_OUTPUT" && "$MINI_EXIT_CODE" == "$BASH_EXIT_CODE" && "$MINI_ERROR_MSG" == "$BASH_ERROR_MSG"  && -z "$OUTFILES_DIFF" ]]; then
			printf ✅
			((ok++))
		elif [ "$MINI_ERROR_MSG" != "$BASH_ERROR_MSG" ]; then
			printf ⚠️
		else
			printf ❌
		fi
		printf "$GREY $teste \n$END"

		if [ "$OUTFILES_DIFF" ]; then
			echo "$OUTFILES_DIFF"
			echo mini outfiles:
			cat ./mini_outfiles/*
			echo bash outfiles:
			cat ./bash_outfiles/*
		fi
		if [ "$MINI_OUTPUT" != "$BASH_OUTPUT" ]; then
			echo mini output = \($MINI_OUTPUT\)
			echo bash output = \($BASH_OUTPUT\)
		fi
		if [ "$MINI_EXIT_CODE" != "$BASH_EXIT_CODE" ]; then
			echo mini exit code = $MINI_EXIT_CODE
			echo bash exit code = $BASH_EXIT_CODE
		fi
		if [ "$MINI_ERROR_MSG" != "$BASH_ERROR_MSG" ]; then
			echo mini error = \($MINI_ERROR_MSG\)
			echo bash error = \($BASH_ERROR_MSG\)
		fi

		# Exit after specific test on single-test mode
		if [[ $1 && $1 -eq $i ]]; then
			exit 0
		fi
	done < ./unit_test/$testfile
done

chmod 666 ./unit_test/test_files/invalid_permission
rm -rf ./outfiles/*
rm -rf ./mini_outfiles
rm -rf ./bash_outfiles

printf $PURPLE
printf $BOLD
echo   $ok/$i
printf $END

if [[ "$ok" == "$i" ]]; then
	echo "🎊 🎊 🎊"
	echo "😎 😎 😎"
	echo "🎉 🎉 🎉"
	exit 0
else
	echo "😭 😭 😭"
	exit 1
fi
