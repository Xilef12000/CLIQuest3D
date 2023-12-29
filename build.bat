ECHO OFF
setlocal ENABLEDELAYEDEXPANSION
echo compiling...
mkdir build
gcc src/main.c -o build/CLIQuest3D.exe
set excode=!errorlevel!
if %excode%==0 (
    echo finished compiling
    echo starting...
    .\build\CLIQuest3D.exe
    set excode=!errorlevel!
    if !excode!==0 (
        echo program exited successful with exit code !excode!
    ) else (
        echo program stopped with exit code !excode!
    )
) else (
   echo compiling error with exit code %excode%
)
ECHO ON
