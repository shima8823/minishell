#!/bin/bash

# ============setup============
# brew install gnu-sed

MINISHELL_DIR="../"
MINISHELL_EXE="minishell"
# =============================

OUTPUT_DIR="./"
SHELL_DIR="`dirname $0`"
CASES_DIR="cases_exec"
CASES_EXIT_DIR="$SHELL_DIR/$CASES_DIR/exit"
CASES_PWD="$SHELL_DIR/$CASES_DIR/pwd.txt"
CASES_ENV="$SHELL_DIR/$CASES_DIR/env.txt"
CASES_CD="$SHELL_DIR/$CASES_DIR/cd.txt"
CASES_EXPORT_UNSET="$SHELL_DIR/$CASES_DIR/export_unset.txt"
CASES_PIPE_REDIRECT="$SHELL_DIR/$CASES_DIR/pipe_redirect.txt"

# もしshellがMakefileで呼ばれているならば
if [ "." != "$SHELL_DIR" ]; then
	MINISHELL_DIR="./"
	OUTPUT_DIR="tests/"
fi

OUTPUT_MINISHELL="$OUTPUT_DIR""minishell.txt"
OUTPUT_BASH="$OUTPUT_DIR""bash.txt"
# ERR_MINISHELL="$OUTPUT_DIR""minishell_err.txt"
# ERR_BASH="$OUTPUT_DIR""bash_err.txt"

RED="\033[31m"
GREEN="\033[32m"
WHITE="\033[37m"
MAGENTA="\033[35m" 
CYAN="\033[36m"

function exec_test()
{
	$MINISHELL_DIR$MINISHELL_EXE < $1 > $OUTPUT_MINISHELL 2> /dev/null
	MINISHELL_STATUS=$?
	sed -i '' -e '1d' $OUTPUT_MINISHELL
	sed -i '' -e '/minishell > /d' $OUTPUT_MINISHELL
	bash < $1 > $OUTPUT_BASH 2> /dev/null
	BASH_STATUS=$?
	# ==もしエラーメッセージも比較するなら==
	# file名に"exit"が含まれていたら
	# if [[ "$2" =~ "exit" ]]; then
	# 	#空の場合の処理
	# 	if [ ! -s $OUTPUT_BASH ]; then
	# 		echo exit > $OUTPUT_BASH
	# 	else
	# 		# 1行目に"exit"を挿入
	# 		gsed -i -e '1i exit' $OUTPUT_BASH
	# 	fi
	# fi
	# sed -i '' -e 's/bash:/minishell:/g' $OUTPUT_BASH
	# sed -i '' -e 's/ line [0-9]://g' $OUTPUT_BASH
	# =====================================
	diff -q $OUTPUT_MINISHELL $OUTPUT_BASH > /dev/null
	if [ $? -eq "0" ] && [ "$MINISHELL_STATUS" == "$BASH_STATUS" ]; then
		printf "$GREEN[$2]  $MINISHELL_STATUS\n"
	else
		printf "$RED[$2]\n"
		printf "$WHITE""minishell\n[`cat $OUTPUT_MINISHELL`]\nSTATUS[$MINISHELL_STATUS]\n"
		printf "bash\n[`cat $OUTPUT_BASH`]\nSTATUS[$BASH_STATUS]\n"
	fi
}

exec_test $CASES_PWD "pwd"
exec_test $CASES_ENV "env"
exec_test $CASES_CD "cd"
exec_test $CASES_EXPORT_UNSET "export_unset"
for file in $(ls $CASES_EXIT_DIR/*); do
	exec_test $file $file
done
exec_test $CASES_PIPE_REDIRECT "pipe_redirect"
