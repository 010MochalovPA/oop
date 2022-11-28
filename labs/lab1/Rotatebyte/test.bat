rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"
set PATH_TEST="test-files"


rem проверяем отсутствие одного из аргементов
echo test without any argument 
%PROGRAM% 5 2 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-arguments-count.txt
if ERRORLEVEL 1 goto err

rem проверяем некоректное значение <byte>
echo test a 2 L
%PROGRAM% a 2 L > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument-byte.txt
if ERRORLEVEL 1 goto err

rem проверяем некоректное значение <number of bits>
echo test 5 a L
%PROGRAM% 5 a L > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument-number-of-bits.txt
if ERRORLEVEL 1 goto err

rem проверяем некоректное значение <direction>
echo test 5 2 A
%PROGRAM% 5 2 A > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument-direction.txt
if ERRORLEVEL 1 goto err

rem проверяем некоректный размер <byte>
echo test 256 2 L
%PROGRAM% 256 2 L > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\size-exceeds.txt
if ERRORLEVEL 1 goto err

rem проверяем корректные значения "17 2 L"
echo test 17 2 L
%PROGRAM% 17 2 L > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-output-for-17-2-L.txt
if ERRORLEVEL 1 goto err

rem проверяем корректные значения "17 8 L"
echo test 17 8 L
%PROGRAM% 17 8 L > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-output-for-17-8-L.txt
if ERRORLEVEL 1 goto err

rem проверяем корректные значения "15 2 R"
echo test 15 2 R
%PROGRAM% 15 2 R > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-output-for-15-2-R.txt
if ERRORLEVEL 1 goto err

rem проверяем корректные значения "15 8 R"
echo test 15 8 R
%PROGRAM% 15 8 R > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-output-for-15-8-R.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1