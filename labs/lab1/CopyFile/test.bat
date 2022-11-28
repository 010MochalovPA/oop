rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"
set PATH_TEST="test-files"

rem ��������� �������� ���������� ����������
%PROGRAM% %PATH_TEST%\one-line.txt > %TEMP%/output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-arguments-count.txt
if ERRORLEVEL 1 goto err

rem ��������� ����������� ������� ����� (�������� ��� �� ��������� ����� �������� ������������)
%PROGRAM% %PATH_TEST%\empty.txt %TEMP%\empty.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\empty.txt %PATH_TEST%\empty.txt
if ERRORLEVEL 1 goto err

rem ��������� ����������� ����� �� ����� ������
%PROGRAM% %PATH_TEST%\one-line.txt %TEMP%\one-line.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\one-line.txt %PATH_TEST%\one-line.txt
if ERRORLEVEL 1 goto err

rem ��������� ����������� ����� �� ���������� �����
%PROGRAM% %PATH_TEST%\multiline.txt %TEMP%\multiline.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\multiline.txt %PATH_TEST%\multiline.txt
if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ������ ��� ����������� ��������������� �����
%PROGRAM% %PATH_TEST%\non-existing-file-name.txt %TEMP%\non-existing-file-name.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\failed-to-open-read.txt
if ERRORLEVEL 1 goto err

rem ������� ��������� ��� ������ ��� ������������� ������ � �������� ���� (� ����������� ���� ���������)
%PROGRAM% %PATH_TEST%\multiline.txt %PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto
fc.exe %TEMP%\output.txt %PATH_TEST%\failed-to-open-write.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1