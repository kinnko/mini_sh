#!/bin/sh
rm ../minishell_42 -rf
cd ../
cp -rf ./minishell ./minishell_42
cd ./minishell_42
git remote set-url origin git@vogsphere-v2.42tokyo.jp:vogsphere/intra-uuid-32efe9f0-9aff-4a17-bbe7-8d8df7900bbd-4503492-yueyama
git rm -r --cached .
echo "*.md" >> .gitignore
echo "*.pdf" >> .gitignore
echo "*.sh" >> .gitignore
echo "input.c" >> .gitignore
echo ".vscode/" >> .gitignore
echo "old_makefile" >> .gitignore
echo "lsh/" >> .gitignore
echo "a" >> .gitignore
echo "b" >> .gitignore
echo "pwd.c" >> .gitignore
echo "pwd.jp.c" >> .gitignore
git add .
git commit -m "for submission"
git push -f
