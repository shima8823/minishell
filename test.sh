#!/bin/bash

# echo -e 'echo $USER' | ./minishell > minishell.txt 2> /dev/null
# echo -e 'echo $USER' | bash > bash.txt

RED="\033[31m"
GREEN="\033[32m"
WHITE="\033[37m"
MAGENTA="\033[35m" 
# bash
CYAN="\033[36m"
# minishell

function env_var_test()
{
	echo -e "$@" | ./minishell > minishell.txt 2> /dev/null
	MYRET=`awk 'NR==3' minishell.txt | awk '{printf $0}'`
	BASHRET=`echo -e "$@" | bash`

	if [ "$MYRET" == "$BASHRET" ]; then
		printf "$GREEN[$@]\n"
	else
		printf "$RED[$@]\n"
		printf "$WHITE""minishell\n[$MYRET]\n"
		printf "bash\n[$BASHRET]\n"
	fi
}

# function env_var_create_file_test()
# {
# 	echo -e "$@" | ./minishell > minishell.txt 2> /dev/null
# 	MYRET=`awk 'NR==3' minishell.txt | awk '{printf $0}'`
# 	BASHRET=`echo -e "$@" | bash`

# 	if [ "$MYRET" == "$BASHRET" ]; then
# 		printf "$GREEN[$@]\n"
# 	else
# 		printf "$RED[$@]\n"
# 		printf "$WHITE""minishell\n[$MYRET]\n"
# 		printf "bash\n[$BASHRET]\n"
# 	fi
# }

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
env_var_test 'echo "$USER '\''$PATH'\''"'
echo

# NOTHING
printf "$WHITE===== nothing =====\n"
env_var_test 'echo $NOTHING'
env_var_test 'echo a$NOTHING'
env_var_test 'echo a$NOTHING$PATH'
env_var_test 'echo "$NOTHING"'
env_var_test 'echo "$NOTHING ushiro"'
env_var_test 'echo mae"ho$NOTHING ge $PATH"ushiro'
env_var_test 'echo echo $NOTHING'
env_var_test 'echo echo $NOTHING echo'
# echo echo $NOTHING echo
# 環境変数がなかったらparserは[echo] [echo] [echo]?

# 分割
printf "$WHITE===== command & env var =====\n"
printf "$MAGENTA""export TEST=\"cho   hello\"\n"
export TEST="cho   hello"
env_var_test 'e$TEST'
printf "$MAGENTA""export TEST=\"echo   hello\"\n"
export TEST="echo   hello"
env_var_test '$TEST'
printf "$MAGENTA""export TEST=\" hello   world\"\n"
export TEST=" hello   world"
env_var_test 'echo$TEST'
printf "$MAGENTA""export TEST=\"apple   banana\"\n"
export TEST="apple   banana"
env_var_test 'echo grape $TEST orange'
env_var_test 'echo grape $TEST$TEST'
printf "$MAGENTA""export TEST=\"  apple  dog banana\"\n"
export TEST="  apple  dog banana"
env_var_test 'echo grape $TEST $TEST$TEST'
printf "$MAGENTA""export TEST=\"  apple  dog banana  \"\n"
export TEST="  apple  dog banana  "
env_var_test 'echo grape $TEST$TEST$TEST'

# create file リダイレクトができた時に。
# printf "$WHITE===== file =====\n"
# printf "$MAGENTA""export TEST=\"ambiguous redirect\"\n"
# export TEST="ambiguous redirect"
# env_var_test 'e$TEST'

# 未対応
printf "$WHITE===== 未対応 =====\n"
# shell変数は実装しないため
env_var_test 'echo $USER=hell'
# zsh bash では echo $"echo" または echo $'echo' の挙動が違うため
env_var_test 'echo "$"$'\''$USER'\'
echo
