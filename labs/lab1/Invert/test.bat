rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"
set PATH_TEST="test-files"


rem проверяем неверное кол-во аргементов
echo test
%PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument-count.txt
if ERRORLEVEL 1 goto err

rem проверяем неправильную матрицу
echo test broken-matrix.txt
%PROGRAM% %PATH_TEST%\broken-matrix.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-input-matrix.txt
if ERRORLEVEL 1 goto err

rem проверяем матрицу c символом
echo test broken-matrix-with-char.txt
%PROGRAM% %PATH_TEST%\broken-matrix-with-char.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-input-matrix.txt
if ERRORLEVEL 1 goto err



rem проверяем корректные данные
echo test matrix1.txt
%PROGRAM% %PATH_TEST%\matrix1.txt > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-invert-matrix1.txt
if ERRORLEVEL 1 goto err

echo test matrix2.txt
%PROGRAM% %PATH_TEST%\matrix2.txt > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-invert-matrix2.txt
if ERRORLEVEL 1 goto err

rem проверяем матрицу c определителем 0
echo test matrix3.txt
%PROGRAM% %PATH_TEST%\matrix3.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\determinate0.txt
if ERRORLEVEL 1 goto err
echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1