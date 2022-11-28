rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"
set PATH_TEST="test-files"

rem ��������� ���������� ����������
%PROGRAM% %PATH_TEST%\one-line.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" %PATH_TEST%\invalid-argument-count.txt
if ERRORLEVEL 1 goto err

rem ��������� �������� �� ������������� �����
%PROGRAM% %PATH_TEST%\does-not-exist.txt cat > %TEMP%/output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" %PATH_TEST%\failed-to-open-read.txt
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������� ������ � �����
%PROGRAM% %PATH_TEST%\text.txt cat > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" %PATH_TEST%\expected-output-for-not-found.txt
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������
%PROGRAM% %PATH_TEST%\text.txt put > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" %PATH_TEST%\expected-output-for-text.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1