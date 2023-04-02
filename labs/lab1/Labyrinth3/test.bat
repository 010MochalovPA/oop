rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"
set PATH_TEST="test-files"

rem ��������� �������� ���-�� ����������
echo test
%PROGRAM% labyrinth.txt > %TEMP%\output23.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output23.txt %PATH_TEST%\invalid-argument-count.txt
if ERRORLEVEL 1 goto err

rem �������� ��������
echo test broken-labyrinth.txt %TEMP%\output2.txt > %TEMP%\output.txt
%PROGRAM% %PATH_TEST%\broken-labyrinth.txt %TEMP%\output2.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\no-path.txt
if ERRORLEVEL 1 goto err

echo test broken-labyrinth-a.txt %TEMP%\output2.txt > %TEMP%\output.txt
%PROGRAM% %PATH_TEST%\broken-labyrinth-a.txt %TEMP%\output2.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\Invalid-labyrinth.txt
if ERRORLEVEL 1 goto err

echo test broken-labyrinth-b.txt %TEMP%\output2.txt > %TEMP%\output.txt
%PROGRAM% %PATH_TEST%\broken-labyrinth-b.txt %TEMP%\output2.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\Invalid-labyrinth.txt
if ERRORLEVEL 1 goto err

echo test labyrinth-1.txt %TEMP%\output.txt
%PROGRAM% %PATH_TEST%\labyrinth-1.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\out-labyrinth-1.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1