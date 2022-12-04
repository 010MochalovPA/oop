rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"
set PATH_TEST="test-files"


rem ��������� ���������� ��������� ����������
echo test 10 16
%PROGRAM% 10 16 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument-count.txt
if ERRORLEVEL 1 goto err

rem ��������� ������������ ������ ���������
echo test 1 10 1
%PROGRAM% 1 10 1 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument-notation.txt
if ERRORLEVEL 1 goto err

echo test 37 10 1
%PROGRAM% 37 10 1 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument-notation.txt
if ERRORLEVEL 1 goto err

echo test 10 1 1
%PROGRAM% 10 1 1 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument-notation.txt
if ERRORLEVEL 1 goto err

echo test 10 37 1
%PROGRAM% 10 37 1 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument-notation.txt
if ERRORLEVEL 1 goto err

rem ��������� �������� �� ����������� ���� �����������
echo test 2 10 134
%PROGRAM% 2 10 134 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument.txt
if ERRORLEVEL 1 goto err

rem ��������� 0
echo test 2 10 0
%PROGRAM% 2 10 0 > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-output-for-0.txt
if ERRORLEVEL 1 goto err

rem ��������� �� ������� ������
echo test 16 10 �1
%PROGRAM% 16 10 �1 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument.txt
if ERRORLEVEL 1 goto err

rem �������� ����� ������������ ������ (��������� �� �������)
echo test 10 12 2147483648
%PROGRAM% 10 12 2147483648 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument.txt
if ERRORLEVEL 1 goto err

echo test 10 12 -2147483648
%PROGRAM% 10 12 -2147483648 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument.txt
if ERRORLEVEL 1 goto err

rem �������� ��������� �������� value
echo test 10 12 2147483647
%PROGRAM% 10 12 2147483647 > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-output-for-10-12-2147483647.txt
if ERRORLEVEL 1 goto err

echo test 10 12 -2147483647
%PROGRAM% 10 12 -2147483647 > %TEMP%\output.txt
if  ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-output-for-10-12--2147483647.txt
if ERRORLEVEL 1 goto err

rem �������� ��������� �������� notation
echo test 2 10 1111111111111111111111111111111
%PROGRAM% 2 10 1111111111111111111111111111111 > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-output-for-2-10-1111111111111111111111111111111.txt
if ERRORLEVEL 1 goto err

echo test 2 36 1111111111111111111111111111111
%PROGRAM% 2 36 1111111111111111111111111111111 > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-output-for-2-36-1111111111111111111111111111111.txt
if ERRORLEVEL 1 goto err

rem �������� ���������� ���������� ��������
echo test 16 10 1F
%PROGRAM% 16 10 1F > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-output-for-16-10-1F.txt
if ERRORLEVEL 1 goto err


echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1