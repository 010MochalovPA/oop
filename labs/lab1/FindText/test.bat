rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"
set PATH_TEST="test-files"

rem проверяем отсутствие аргументов
%PROGRAM% %PATH_TEST%\one-line.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" %PATH_TEST%\invalid-argument-count.txt
if ERRORLEVEL 1 goto err

rem проверяем передачу не существующего файла
%PROGRAM% %PATH_TEST%\does-not-exist.txt cat > %TEMP%/output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" %PATH_TEST%\failed-to-open-read.txt
if ERRORLEVEL 1 goto err

rem проверяем отсутствие искомой строки в файле
%PROGRAM% %PATH_TEST%\text.txt cat > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" %PATH_TEST%\expected-output-for-not-found.txt
if ERRORLEVEL 1 goto err

rem проверяем корректные данные
%PROGRAM% %PATH_TEST%\text.txt put > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" %PATH_TEST%\expected-output-for-text.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1