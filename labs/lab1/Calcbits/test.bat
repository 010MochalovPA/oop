rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамл€ющих кавычек (если они были)

rem ѕеременна€ PROGRAM будет хранить первый аргумент командной строки заключЄнный в кавычки
set PROGRAM="%~1"
set PATH_TEST="test-files"


rem провер€ем отсутствие аргемента
echo test without arguments 
%PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-arguments-count.txt
if ERRORLEVEL 1 goto err

rem провер€ем корректное значение (5)
echo test 5
%PROGRAM% 5 > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-output-for-5.txt
if ERRORLEVEL 1 goto err

rem провер€ем корректное значение (0)
echo test 0
%PROGRAM% 0 > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-output-for-0.txt
if ERRORLEVEL 1 goto err

rem провер€ем корректное значение (255)
echo test 255
%PROGRAM% 255 > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-output-for-255.txt
if ERRORLEVEL 1 goto err

rem провер€ем некорректное значение (256)
echo test 256
%PROGRAM% 256 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\size-exceeds.txt
if ERRORLEVEL 1 goto err

rem провер€ем некорректное значение (-1)
echo test -1
%PROGRAM% -1 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument.txt
if ERRORLEVEL 1 goto err

rem провер€ем некорректное значение (a)
echo test a
%PROGRAM% a > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1