#!/bin/bash

# 1. Создать файлы 1..20.txt
for (( i=1; i<=20; i++ )) do touch $i.txt; done

# 2. Записать в каждый его имя
for i in $(ls *.txt); do echo $i > $i; done

# 3. Удалить файлы без "4" в имени
shopt -s extglob
rm -v !(*4*|*.sh) > /dev/null

# 4. Поменять содержимое файла 14.txt
echo asdf > 14.txt

# 5*. Создание системы вложенных папок
homedir=$(pwd)

for i in 1 2 3
do
  for (( j=1; j <= i; j++ ))
  do
    mkdir $i
    cd $i
  done
  touch $i.txt
  cd $homedir
done

# Создание симлинков
ln -s 1/1.txt 1.txt
ln -s 2/2/2.txt 2.txt
ln -s 3/3/3/3.txt 3.txt

# Вывод результата
tree
