### コンパイル

・-Wall -Wextra -Werrorフラグを使っているかどうか確認するためmake -nを使う。
・minishell compile without errors if not use flags
・リリンクしてはいけない。

### シンプルコマンドとグローバル

・絶対パスでシンプルなコマンドを実行する。
ex) /bin/ls or any other command without options
・いくつグローバル変数を使っていて、それはなぜですか。
・空のコマンドを試す。
・スペースやタブだけで試す。

```bash
/bin/ls
/bin/cat
/usr/bin/grep

/bin/midir tmp
/bin/rm -r tmp
```

### 引数と履歴

・シンプルなコマンドを絶対パスで、引数を付けて実行する。ただし、引用符は含めない。
・複数回、別のコマンドや別の引数で試す。

```bash
/bin/ls -l
/usr/bin/file minishell

/usr/bin/grep clean Makefile
/usr/bin/wc -l minishell
```

### echo

・echo コマンドを引数あり、引数なし、オプションあり、オプションなしで実行する。
・複数回違ったやり方で試す。

```bash
# no option
echo                       # status: 0 改行を出力
echo hello                 # status: 0 hello
echo -n-n-n 42             # status: 0 -n-n-n 42
echo 42 -n                 # status: 0 42 -n

# -n option
echo -n                    # status: 0 何も出力しない
echo -n 42                 # status: 0 42(no newline)
echo -n 42-n               # status: 0 42-n(no newline)
echo -n aaa -n bbb -n ccc  # status: 0　aaa -n bbb -n ccc
```

### exit

・exitを引数あり、引数なしで実行する。
・違ったやり方で複数回試す。
・minishellを再起動することを忘れないでください。 

```bash
#その都度終了ステータスを確認する。
exit                          # last exit status
exit "     42"                # 42
exit +123                     # 123
exit -456                     # 56
exit 1111111111(10)           # 199
exit 9223372036854775807      # 255
exit -9223372036854775808     # 0

#non-numeric: 255 (exit)
exit 9223372036854775808      #bash: exit: 9223...: numeric argument required
exit -9223372036854775809     #bash: exit: -9223...: numeric argument required
exit a                        #bash: exit: a: numeric argument required
exit ++1                      #bash: exit: ++1: numeric argument required
exit ft 42                    #bash: exit: ft: numeric argument required
exit 12345abc

#too-many-arg: 1 (not exit)
exit 1 2 3                    #bash: exit: too many arguments
exit 42 ft                    #bash: exit: too many arguments
```

### return value of process

・シンプルなコマンドを実行して、echo $?を実行すると？
・その結果をbashと比較してください。
・複数回試してください。また、失敗するコマンドも試してみてください。
・anything like expr $? * $?

```bash
echo $?

#normal
/bin/ls                            # 0
/usr/bin/grep notexist Makefile    # 1

#error
/bin/ls -3                         # 1
/usr/bin/grep a filenotexist       # 2
cmdnotexist                        # 127

# syntax error
echo |||||                         # 258
echo a >>                          # 258
```

### シグナル

・空のプロンプトでctrl-Cを入力すると、新しい行で新しいプロンプトが表示される。
・空のプロンプトでctrl-\を入力しても何も起きない。
・空のプロンプトでctrl-Dを入力するとminishellが終了する。
・何かをプロンプトに入力したあとに、ctrl-Cを入力すると、新しい行で新しいプロンプトが表示される。バッファもクリーンである必要がある。Enterを押して古い行が実行されないこと。
・何かをプロンプトに入力したあとに、ctrl-Dを入力すると、何も起きないはず。
・何かをプロンプトに入力したあとに、ctrl-\を入力すると、何も起きないはず。
・引数なしのcat, grep “something”等を実行したあとctrl-Cを試してください。
・引数なしのcat, grep “something”等を実行したあとctrl-\を試してください。
・引数なしのcat, grep “something”等を実行したあとctrl-Dを試してください。

```bash
# 返り値確認する
echo $?

# empty ptompt
ctrl-C                       # 1
ctrl-\                       # 0
ctrl-D                       # 0

# write something
ctrl-C                       # 1
ctrl-\                       # dosen't work
ctrl-D                       # dosen't work

# blocking cmd
ctrl-C                       # 130
ctrl-\                       # 131
ctrl-D                       # 0
```

### 二重引用符

・引数を使用して単純なコマンドを実行します。二重引用符を含めてください。
例えば　echo “ cat lol.c | cat>lol.c”
・＄以外のもの。

```bash
# basic
/bin/ls "srcs"
/bin/ls ""

# empty
echo "" "" "" | cat -e #  $(two spaces)

# quote commands
## success
"/bin/ls" srcs
"/bin/ls srcs"  error!!!!
"/bi"n/ls srcs
""bin/ech"o" "test"

## error
"/bin/echo -n hello"     #bash: /bin/echo -n hello: No such file or directory
"bin/ls" ">" "test"      #ls: >: No such file or directory
```

### 一重引用符

・引数として一重引用符を使用してコマンドを実行します。
・一重引用符で空の引数を試してください。
・一重引用符で環境変数、空白、パイプ、リダイレクトを含めてみてください。
・echo ‘$USER’ は$USERを出力しなければなりません。
・何も解釈しません。

```bash
echo 'hell
echo '$USER'
echo '"'
echo ''$USER''
echo '''$USER'''

```

### 環境

・envが現在の環境変数を表示するかどうか確認します。

```bash
# bashと比較
env | sort
```

### export

・環境変数をエクスポートし、新しい変数を作成して、古い変数を置き換えます。
envで確認します。

```bash
export
export TEST=hoge
env

export aaa
env
export

export 42="42"
export _42="42"
export _A="aaa" _B="" _C=_D _E

# overwrite
export _A="AAAAAAAAA"

# multiple equals
export TEST="a=b======c==d= "
env | grep TEST
exho $TEST

#include options
export TEST="-n hello"
env | grep TEST
echo $TEST                    #no new line

# errors
export 111=aaaa
export $env=aaaa
export #A%D=1212  これは対応しなくてもよさそう。

# += !?
export AAAAAAA+=111111111
```

### unset

・環境変数を削除します。envで確認します。

```bash
# not a valid indentifier
unset $
unset @@
unset 42

#success
unset Pwd Pwd Pwd
```

### cd

・cdを使ってディレクトリを移動する。/bin/lsを使って正しく移動したか確認する。
・正しく移動するとき、しないとき、複数回試す。
・”.”, “..”を引数として使ってみる。

```bash
# basic
cd .
cd ..
cd ../
cd ""

# relative / absolute paths

# error
cd aaaaa                       #bash: cd: aaaaaaa: No such file or directory
cd //

# 実装不要??
cd
unset HOME
cd
```

### pwd

・pwdを実行してみる。
・違うディレクトリで実行してみる。

### relative path

・相対パスでコマンドを実行する。
・複数回、違ったディレクトリから複雑な相対パスでコマンドを試してみる。

### environment path

・パスなしでコマンドを実行する。
・unset the $PATH and check if it is not working anymore.
・$PATHに複数のディレクトリを設定し、それらが左から右へ順を追っているか確認する。

```bash
# is executable?
./minishell
export PATH=$PATH:$PWD
minishell
```

### redirection

・コマンドを　＜　または　＞　をつけて実行する。
・いろんなコマンドを複数回リダイレクトを使って実行してみる。
・複数のリダイレクションで失敗するかどうか確認する。
・ヒアドキュメントを試す。履歴は更新しない。

```bash
# basic
echo aaaaa > a; cat a
echo bbbbb >> a; cat a
echo ccccc > a; cat a

ls > test.txt

# same redirect
notcommand 2> a 2> b 2> c
cat a b                           #empty
cat c                             #error

# error no 3.txt
rm 1.txt 2.txt 3.txt 4.txt
ls > 1.txt > 2.txt < 3.txt >> 4.txt
ls # no 4.txt
cat 1.txt
cat 2.txt

# structure
> f0 echo > f1 > f2 > f3 abc
cat f0 f1 f2
cat f3

# file discripter redirection
2> file
255> file
d56> file #file descriptor out of range: Bad file descriptor
```

### pipe

・”cat file | grep bla | more” のようにパイプを使ってコマンドを実行する。
・繰り返し、違ったコマンドを実行する。
・失敗するコマンドを試してみる。”ls filethatdoesntexit | grep bla | more”
 ・パイプとリダイレクトを混ぜて実行してみる。

```bash
# simple
cat Makefile | grep .c | grep fclean
cat Makefile | less

export a=bbb; echo $a

# pipe advance
## cd ignored in pipe
pwd ; echo hello | cd ..; pwd
## export igored in pipe
export TEST="a"; echo $TEST; export TEST="b" | echo $TEST
```

### go crazy and history

・type a command line then use ctrl-C then press enter the buffer should be clean and nothing try to execute.
・up, downで履歴をたどることができるか、また再実行できるか。
・動くべきでない’dasdfjlkasd’のようなコマンドを実行し、シェルがクラッシュしないで、エラーを表示するかどうか確認する。
・”cat | cat | ls” behave “normally”.
・minishellで楽しめた？

```bash
# echo
## trimmed spaces
export TEST="42      "
echo $TEST | cat -e              # 42$

# exit
## write to stderr
exit > /dev/null                 # exit

# env
## red as command line
export this="echi here > 1.txt"
$this                            #here > 1.txt

## env not expanded
export this="$PATH"
echo $this                       #$PATH

# pwd
## rm current dir
mkdir dir
cd dir
rmdir ../dir
pwd
cd .
cd .
pwd
pwd
pwd

```

environment variables

・引数として$変数を与えて、echoを実行する。
・$が一つの環境変数として解釈されるか確認する。
・二重引用符が＄を解釈するか確認する。
・$USERが存在するか確認するまたは設定する。
・echo “$USER”は$USERの値を表示するべき。

```bash
echo $
echo $$
echo " $"
echo "\$"
echo "$USER"
```
