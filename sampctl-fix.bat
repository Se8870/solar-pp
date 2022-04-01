@echo off
@title SAMPCTL FIX - Se8870

echo -------------------------
echo sampctl fixer by Se8870
echo -------------------------
echo.
echo.

echo Deleting cache package...
rmdir /s /q dependencies
rmdir /s /q %appdata%\sampctl\plugins
rmdir /s /q %appdata%\sampctl\packages

echo Ensuring packages...
sampctl ensure --update

echo.
echo Package have been refreshed, please try "sampctl build" again!
pause
