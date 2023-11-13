# minishell
## Usage
```
brew install readline
git clone https://github.com/shima8823/minishell.git
cd minishell
make
./minishell
```
## Feature
### input
- シンプルなコマンド `ls`
- 絶対パスのコマンド `/bin/ls`
- 相対パスのコマンド `./bin/ls`
が実行可能です。

コマンド履歴機能も実装しています。
環境変数も利用可能です。

#### builtin
builtinコマンドとして
- pwd
- cd
- echo
- export
- unset
- env
- exit

の7つを機能制限付きで実装しています。

### pipe
`ls | grep a`や`cat somefile | grep b | grep c`のようなパイプを通したコマンドの実行も可能です。

### redirect
`< << > >>`4種類のリダイレクトが実装されています。
リダイレクトとパイプの併用も可能です。

![minishell](https://github.com/shima8823/minishell/assets/57759015/faeea6b3-75e7-4d59-8330-3bb82f42ce89)

