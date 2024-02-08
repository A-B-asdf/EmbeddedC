#!/bin/bash

# запускает несколько дочерних процессов с командой sleep
for i in {1..5}
do
    ./child_process.sh $(($i * 10)) &
done

sleep 1

# записывает количество отработанных процессов в файл
echo "Отработано процессов: $(($(ps -ef | grep -c ./child_process.sh) - 1))" > processed.txt

# переходит в sleep 3600
sleep 3600
