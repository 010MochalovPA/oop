rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"
set PATH_TEST="test-files"


rem проверяем отсутствие аргемента
echo test without arguments 
%PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument-count.txt
if ERRORLEVEL 1 goto err

rem проверяем некорректный аргумент
echo test a
%PROGRAM% a > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-notation.txt
if ERRORLEVEL 1 goto err

echo test -2
%PROGRAM% -2 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-notation.txt
if ERRORLEVEL 1 goto err

echo test 4294967296
%PROGRAM% 4294967296 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument.txt
if ERRORLEVEL 1 goto err

rem проверяем пограничные значения
echo test 0
%PROGRAM% 0 > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\expected-output-for-0.txt
if ERRORLEVEL 1 goto err

echo test 4294967295
%PROGRAM% 4294967295 > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\expected-output-for-4294967295.txt
if ERRORLEVEL 1 goto err

rem проверяем корректное значение (253)
echo test 253
%PROGRAM% 253 > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\expected-output-for-253.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1