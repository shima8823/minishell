#!/bin/bash

# echo -e 'echo $USER' | ./minishell > minishell.txt 2> /dev/null
# echo -e 'echo $USER' | bash > bash.txt

RED="\033[31m"
GREEN="\033[32m"
WHITE="\033[37m"

function env_var_test()
{
	echo -e $@ | ./minishell > minishell.txt 2> /dev/null
	echo 'hello, minishell' > bash.txt
	echo '> '$@ >> bash.txt
	echo -e $@ | bash >> bash.txt
	echo -n '> ' >> bash.txt
	diff -q minishell.txt bash.txt &> /dev/null
	if [ $? -eq 0 ]; then
		printf "$GREEN[$@]\n"
	elif [ $? -eq 1 ]; then
		printf "$RED[$@]\n"
		printf "$WHITE""minishell.txt\n"
		printf '['
		awk 'NR==3' minishell.txt | awk '{printf $0}'
		echo ']'
		printf "bash.txt\n"
		printf '['
		awk 'NR==3' bash.txt | awk '{printf $0}'
		echo ']'
	fi
}

# basic
printf "$WHITE===== basic test =====\n"
env_var_test 'echo $USER'
env_var_test 'echo a$USER'
env_var_test 'echo $USER$PATH'
echo
# double quote
printf "$WHITE===== double quote =====\n"
env_var_test 'echo "$USER"'
env_var_test 'echo "a$USER"'
env_var_test 'echo "$USER ushiro"'
env_var_test 'echo "$USER$PATH"'
env_var_test 'echo "$USER hello $PATH"'
env_var_test 'echo mae"$USER"ushiro'
env_var_test 'echo mae"ho$USER ge"ushiro'
env_var_test 'echo mae"ho$USER$PATH"ushiro'
env_var_test 'echo mae"ho$USER ge $PATH"ushiro'
echo
# single quote
printf "$WHITE===== single quote =====\n"
env_var_test 'echo '\''$USER'\'
env_var_test 'echo '\''a$USER'\'
env_var_test 'echo '\''$USER ushiro'\'
env_var_test 'echo '\''$USER$PATH'\'
env_var_test 'echo '\''$USER hello $PATH'\'
env_var_test 'echo mae'\''$USER'\''ushiro'
env_var_test 'echo mae'\''ho$USER ge'\''ushiro'
env_var_test 'echo mae'\''ho$USER$PATH'\''ushiro'
env_var_test 'echo mae'\''ho$USER ge $PATH'\''ushiro'
echo

# mix
printf "$WHITE===== mix =====\n"
env_var_test 'echo "l"s$USER'\''ushiro'\'
env_var_test 'echo "$"$'\''$USER'\'
env_var_test 'echo "$USER '\''$PATH'\''"'
echo

# shell変数は当然間違い
printf "$WHITE===== shell variable =====\n"
env_var_test 'echo $USER=hell'
echo

# NOTHING
printf "$WHITE===== nothing =====\n"
env_var_test 'echo $NOTHING'
env_var_test 'echo a$NOTHING'
env_var_test 'echo a$NOTHING$PATH'
env_var_test 'echo "$NOTHING"'
env_var_test 'echo "$NOTHING ushiro"'
env_var_test 'echo mae"ho$NOTHING ge $PATH"ushiro'

# 分割
# export TEST="cho hello"
# e{cho hello} 2
# e{ cho hello} 3
# {cho hello} 2
# nasi
# e {cho hello} 3
