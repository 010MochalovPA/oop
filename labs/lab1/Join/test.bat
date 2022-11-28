rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамл€ющих кавычек (если они были)

rem ѕеременна€ PROGRAM будет хранить первый аргумент командной строки заключЄнный в кавычки
set PROGRAM="%~1"
set PATH_TEST="test-files"

rem провер€ем отсутствие аргументов
%PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument-count.txt
if ERRORLEVEL 1 goto err

rem провер€ем передачу не существующего файла
%PROGRAM% %PATH_TEST%\does-not-exist.bin %PATH_TEST%\2.bin %TEMP%\output.bin > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\failed-to-open-read.txt
if ERRORLEVEL 1 goto err

rem провер€ем невозможность записи 
%PROGRAM% %PATH_TEST%\does-not-exist.bin %PATH_TEST%\2.bin %PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

rem провер€ем объединение 2ух бинарных файлов
%PROGRAM% %PATH_TEST%\1.bin %PATH_TEST%\2.bin %TEMP%\output.bin
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.bin %PATH_TEST%\bin-join-1-with-2.bin
if ERRORLEVEL 1 goto err

rem провер€ем объединение 3ех бинарных файлов
%PROGRAM% %PATH_TEST%\1.bin %PATH_TEST%\2.bin %PATH_TEST%\3.bin %TEMP%\output.bin
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.bin %PATH_TEST%\bin-join-1-2-3.bin
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1