rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"
set PATH_TEST="test-files"

rem проверяем корректное значение
echo test correct
%PROGRAM% %PATH_TEST%\bmp_24.bmp > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-output.txt
if ERRORLEVEL 1 goto err

rem проверяем отсуствие аргументов
echo test incorrect
%PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument-count.txt
if ERRORLEVEL 1 goto err

rem проверяем неверный аргумент
echo test incorrect
%PROGRAM% %PATH_TEST%\test.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\not-bmp-file.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1