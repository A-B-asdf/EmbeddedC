#!/bin/python3

import subprocess

SIGRTMAX = 64
SIGKILL = 9
SIGSTOP = 19

def compile():
    subprocess.run("gcc custom_sigint.c -o a.out".split())

def run():
    compile()
    subprocess.run(["./a.out"])

def test():
    compile()
    process = subprocess.Popen(["./a.out"], stdout=subprocess.PIPE)
    print(process.stdout.readline().decode('utf-8').strip())  # pid
    l = process.stdout.readline().decode('utf-8').strip()  # 
    print(l)
    SIGRTMAX = int(l.split()[1])
    l = process.stdout.readline().decode('utf-8').strip()  # 
    print(l)
    SIGKILL = int(l.split()[1])
    l = process.stdout.readline().decode('utf-8').strip()  # 
    print(l)
    SIGSTOP = int(l.split()[1])
    for i in range(1, SIGRTMAX + 1):
        if i not in [SIGKILL, SIGSTOP]:
            # os.kill(PID, i)           # always kills for some reason..
            # process.send_signal(i)    # doesn't work at all (:
            subprocess.run(["kill", "-s", str(i), str(process.pid)])
            if process.poll() is not None:
                print("Oops, we accidentally killed the process :(")
                print(f"it was signal {i} btw")
                break
            print(process.stdout.readline().decode('utf-8').strip())
    subprocess.run(["kill", "-s", "9", str(process.pid)])

if __name__ == "__main__":
    test()
