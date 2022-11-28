rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"
set PATH_TEST="test-files"


rem ��������� ���������� ���������
echo test without arguments 
%PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument-count.txt
if ERRORLEVEL 1 goto err

rem ��������� ���� ������������� ��������� 123
echo test 123 
%PROGRAM% 123 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-notation.txt
if ERRORLEVEL 1 goto err

rem ��������� ���� ������������� �������� ����� (2^32)-1
echo test 111111111111111111111111111111111 
%PROGRAM% 111111111111111111111111111111111 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\exceeds-size.txt
if ERRORLEVEL 1 goto err

rem ��������� ���� ����������� ������� (0)
echo test 0 
%PROGRAM% 0 > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\expected-output-for-0.txt
if ERRORLEVEL 1 goto err

rem ��������� ���� ����������� ������� (4294967295)
echo test 11111111111111111111111111111111
%PROGRAM% 11111111111111111111111111111111 > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\expected-output-for-4294967295.txt
if ERRORLEVEL 1 goto err

rem ��������� ���� ������� (400)
echo test 110010000
%PROGRAM% 110010000 > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\expected-output-for-400.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1