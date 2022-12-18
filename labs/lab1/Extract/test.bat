rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамл€ющих кавычек (если они были)

rem ѕеременна€ PROGRAM будет хранить первый аргумент командной строки заключЄнный в кавычки
set PROGRAM="%~1"
set PATH_TEST="test-files"

rem провер€ем отсутствие аргументов
echo test test.bin
%PROGRAM% %PATH_TEST%\test.bin > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument-count.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при невозможности записи в выходной файл (в исполн€емый файл программы)
echo test test.bin %PROGRAM%
%PROGRAM% %PATH_TEST%\test.bin %PROGRAM% 2 10
if NOT ERRORLEVEL 1 goto err

rem провер€ем передачу не существующего файла
echo test does-not-exist.bin output.bin 5 10
%PROGRAM% %PATH_TEST%\does-not-exist.bin %TEMP%\output.bin 5 10 > %TEMP%/output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\failed-to-open-read.txt
if ERRORLEVEL 1 goto err

rem провер€ем некорректные аргументы start possition и fragment size
echo test test.bin output.bin -1 2
%PROGRAM% %PATH_TEST%\test.bin %TEMP%\output.bin -1 2 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument.txt
if ERRORLEVEL 1 goto err

echo test test.bin output.bin a 2
%PROGRAM% %PATH_TEST%\test.bin %TEMP%\output.bin a 2 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument.txt
if ERRORLEVEL 1 goto err

echo test test.bin output.bin 2 -1
%PROGRAM% %PATH_TEST%\test.bin %TEMP%\output.bin 2 -1 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument.txt
if ERRORLEVEL 1 goto err

echo test test.bin output.bin 16 40
%PROGRAM% %PATH_TEST%\test.bin %TEMP%\output.bin 16 40 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-extractable-fragment.txt
if ERRORLEVEL 1 goto err

echo test test.bin output.bin 40 1
%PROGRAM% %PATH_TEST%\test.bin %TEMP%\output.bin 40 1 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-extractable-fragment.txt
if ERRORLEVEL 1 goto err

rem провер€ем корректные данные start possition и fragment size
echo test test.bin output.bin 2 10
%PROGRAM% %PATH_TEST%\test.bin %TEMP%\output.bin 2 10
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.bin %PATH_TEST%\correct-2-10.bin
if ERRORLEVEL 1 goto err

echo test test.bin output.bin 2 0
%PROGRAM% %PATH_TEST%\test.bin %TEMP%\output.bin 2 0
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.bin %PATH_TEST%\empty.bin
if ERRORLEVEL 1 goto err

echo test test.bin output.bin 16 16
%PROGRAM% %PATH_TEST%\test.bin %TEMP%\output.bin 16 16
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.bin %PATH_TEST%\correct-16-16.bin
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1