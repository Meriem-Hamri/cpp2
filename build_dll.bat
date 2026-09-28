@echo off
setlocal

rem Fonctionne meme si le script est appele depuis un autre dossier.
cd /d "%~dp0"
if errorlevel 1 exit /b 1

rem Utilise l'environnement MinGW-w64 UCRT de MSYS2.
if exist "C:\msys64\ucrt64\bin\g++.exe" set "PATH=C:\msys64\ucrt64\bin;%PATH%"

rem Le compilateur nettoie ses fichiers temporaires apres compilation.
set "TEMP=%CD%"
set "TMP=%CD%"

echo Compilation de la bibliotheque dynamique...
g++ -std=c++17 -Wall -Wextra -pedantic -DBIBLIOTHEQUE_EXPORTS ^
    -shared Pile.cpp Expression.cpp ^
    -Wl,--out-implib,libbibliotheque.a ^
    -o bibliotheque.dll

if errorlevel 1 (
    echo Erreur pendant la creation de la DLL.
    exit /b 1
)

echo Compilation de l'application...
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp ^
    -L. -lbibliotheque ^
    -o application.exe

if errorlevel 1 (
    echo Erreur pendant la creation de l'application.
    exit /b 1
)

echo Compilation terminee.
echo Fichiers produits : bibliotheque.dll, libbibliotheque.a et application.exe
rem Le .a est uniquement la bibliotheque d'importation de la DLL.

if /i "%~1"=="run" (
    application.exe
    if errorlevel 1 exit /b 1
) else (
    echo Pour compiler puis executer : build_dll.bat run
)

endlocal
