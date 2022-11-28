rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"
set PATH_TEST="test-files"

rem ��������� ���������� ����������
%PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument-count.txt
if ERRORLEVEL 1 goto err

rem ��������� �������� �� ������������� �����
%PROGRAM% %PATH_TEST%\does-not-exist.bin %PATH_TEST%\2.bin %TEMP%\output.bin > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\failed-to-open-read.txt
if ERRORLEVEL 1 goto err

rem ��������� ������������� ������ 
%PROGRAM% %PATH_TEST%\does-not-exist.bin %PATH_TEST%\2.bin %PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

rem ��������� ����������� 2�� �������� ������
%PROGRAM% %PATH_TEST%\1.bin %PATH_TEST%\2.bin %TEMP%\output.bin
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.bin %PATH_TEST%\bin-join-1-with-2.bin
if ERRORLEVEL 1 goto err

rem ��������� ����������� 3�� �������� ������
%PROGRAM% %PATH_TEST%\1.bin %PATH_TEST%\2.bin %PATH_TEST%\3.bin %TEMP%\output.bin
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.bin %PATH_TEST%\bin-join-1-2-3.bin
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1