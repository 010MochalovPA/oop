rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"
set PATH_TEST="test-files"

rem проверяем отсутствие аргументов
%PROGRAM% %PATH_TEST%\fox.txt > %TEMP%/output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument-count.txt
if ERRORLEVEL 1 goto err

rem проверяем передачу не существующего файла
%PROGRAM% %PATH_TEST%\does-not-exist.txt %PATH_TEST%\fox.txt dog cat > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\failed-to-open-read.txt
if ERRORLEVEL 1 goto err

rem проверяем невозможность записи 
%PROGRAM% %PATH_TEST%\fox.txt %PROGRAM% dog cat > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

rem проверяем замену строки в файле
%PROGRAM% %PATH_TEST%\fox.txt %TEMP%\output.txt dog cat
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\fox-replace-dog-with-cat.txt
if ERRORLEVEL 1 goto err

%PROGRAM% %PATH_TEST%\mama.txt %TEMP%\output.txt ma mama
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\mama-replace-ma-with-mama.txt
if ERRORLEVEL 1 goto err

%PROGRAM% %PATH_TEST%\12312312345.txt %TEMP%\output.txt 1231234 999
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\12312312345-replace-1231234-with-999.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1