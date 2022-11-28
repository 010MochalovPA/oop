rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"
set PATH_TEST="test-files"


rem ��������� �������� ���-�� ����������
echo test matrix1.txt
%PROGRAM% %PATH_TEST%\matrix1.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-argument-count.txt
if ERRORLEVEL 1 goto err

rem ��������� ������������ �������
echo test broken-matrix.txt matrix1.txt
%PROGRAM% %PATH_TEST%\broken-matrix.txt %PATH_TEST%\matrix1.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-format-matrix.txt
if ERRORLEVEL 1 goto err

rem ��������� ������� c ��������
echo test broken-matrix-with-char.txt matrix1.txt
%PROGRAM% %PATH_TEST%\broken-matrix-with-char.txt %PATH_TEST%\matrix1.txt > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\invalid-format-matrix.txt
if ERRORLEVEL 1 goto err

rem ��������� ���������� ������
echo test matrix1.txt matrix2.txt
%PROGRAM% %PATH_TEST%\matrix1.txt %PATH_TEST%\matrix2.txt  > %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\output.txt %PATH_TEST%\correct-multimatrix-result.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1