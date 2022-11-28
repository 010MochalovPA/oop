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

rem ��������� ������������ ���������
echo test a 
%PROGRAM% a > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument-byte.txt
if ERRORLEVEL 1 goto err

echo test -1
%PROGRAM% -1 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument-byte.txt
if ERRORLEVEL 1 goto err

rem ��������� ������������ ������ ��������� (256)
echo test 256 
%PROGRAM% 256 > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-size.txt
if ERRORLEVEL 1 goto err

rem ��������� ����������� ��������
echo test 0 
%PROGRAM% 0 > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-output-for-0.txt
if ERRORLEVEL 1 goto err

echo test 255
%PROGRAM% 255 > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-output-for-255.txt
if ERRORLEVEL 1 goto err

rem ��������� ��������� ���������� ��������
echo test 6
%PROGRAM% 6 > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-output-for-6.txt
if ERRORLEVEL 1 goto err

echo test 121
%PROGRAM% 121 > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-output-for-121.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1