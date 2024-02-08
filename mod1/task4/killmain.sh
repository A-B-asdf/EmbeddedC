#!/bin/bash

# ищем PID процесса из пункта 1
parent_PID=$(ps -ef | grep ./main.sh | grep -v grep | awk '{print $2}')

kill $parent_PID
