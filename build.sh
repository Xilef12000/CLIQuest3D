#!/bin/bash
echo "\e[1;36mcompiling... \e[0m"
mkdir build
gcc src/main.c -o build/CLIQuest3D.out -lm
excode=$?
if [ $excode -ne 0 ]
then
  echo "\e[1;31mcompiling error with exit code $excode\e[0m"
else
  echo "\e[1;32mfinished compiling \e[0m"
  echo "\e[1;36mstarting... \e[0m"
  /bin/stty raw
  /bin/stty -echo
  tput civis
  ./build/CLIQuest3D.out
  excode=$?
  /bin/stty sane
  tput cnorm
  if [ $excode -eq 0 ]
  then
    echo "\e[1;32mprogram exited successful with exit code $excode\e[0m"
  else
    echo "\e[1;31mprogram stopped with exit code $excode\e[0m"
  fi
fi
