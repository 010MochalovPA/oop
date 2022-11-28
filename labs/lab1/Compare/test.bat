rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"
set PATH_TEST="test-files"


rem проверяем неверное кол-во аргементов
echo test empty1.txt
%PROGRAM% %PATH_TEST%\empty1.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument-count.txt
if ERRORLEVEL 1 goto err

rem проверяем сравнение пустых файлов
echo test empty1.txt empty2.txt
%PROGRAM% %PATH_TEST%\empty1.txt %PATH_TEST%\empty2.txt > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %PATH_TEST%\empty1.txt %PATH_TEST%\empty2.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\files-are-equal.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при сравнении несуществующего файла
echo test non-existing-file-name.txt one-line1.txt
%PROGRAM% %PATH_TEST%\non-existing-file-name.txt %PATH_TEST%\one-line1.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\failed-to-open.txt
if ERRORLEVEL 1 goto err

echo test one-line1.txt non-existing-file-name.txt
%PROGRAM% %PATH_TEST%\one-line1.txt %PATH_TEST%\non-existing-file-name.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\failed-to-open.txt
if ERRORLEVEL 1 goto err

rem проверяем сравнение совпадающих файлов с одной строкой
echo test one-line1.txt one-line2.txt
%PROGRAM% %PATH_TEST%\one-line1.txt %PATH_TEST%\one-line2.txt > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %PATH_TEST%\one-line1.txt %PATH_TEST%\one-line2.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\files-are-equal.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при сравнение разных файлов с одной строкой
echo test one-line1.txt one-line3.txt
%PROGRAM% %PATH_TEST%\one-line1.txt %PATH_TEST%\one-line3.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %PATH_TEST%\one-line1.txt %PATH_TEST%\one-line3.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\files-are-different-1.txt
if ERRORLEVEL 1 goto err

rem проверяем сравнение совпадающих файлов из нескольких строк
echo test multiline1.txt multiline2.txt
%PROGRAM% %PATH_TEST%\multiline1.txt %PATH_TEST%\multiline2.txt > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %PATH_TEST%\multiline1.txt %PATH_TEST%\multiline2.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\files-are-equal.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при сравнение разных файлов из нескольких строк
echo test multiline1.txt multiline3.txt
%PROGRAM% %PATH_TEST%\multiline1.txt %PATH_TEST%\multiline3.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %PATH_TEST%\multiline1.txt %PATH_TEST%\multiline3.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\files-are-different-2.txt
if ERRORLEVEL 1 goto err


echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1