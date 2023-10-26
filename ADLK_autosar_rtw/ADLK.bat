
set MATLAB=D:\APP\matlab2022

cd .

if "%1"=="" ("D:\APP\MATLAB~1\bin\win64\gmake"  -f ADLK.mk all) else ("D:\APP\MATLAB~1\bin\win64\gmake"  -f ADLK.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
exit /B 1