#!/bin/bash

# ищем PID процесса из пункта 1
parent_PID=$(ps -ef | grep ./main.sh | grep -v grep | awk '{print $2}')

# Выводим дерево дочерних процессов
pstree $parent_PID

# ищем идентификаторы дочерних процессов с именем "./child_process",
# убиваем 3 из них
ps -ef | awk -v var=$parent_PID '{if ($3 == var && index($0, "./child_process.sh") > 0) print $2}' | head -n 3 | xargs kill

# Смотрим, что получилось
pstree $parent_PID
