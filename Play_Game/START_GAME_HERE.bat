@echo off
cd /d "%~dp0Game_Files"
set PATH=%~dp0Game_Files\DLL;%PATH%
start "" "game_178.exe"
