@echo off
echo Deploying Robot files to Professor's OneDrive...

:: Set source to the current folder where this script lives
set SOURCE="%~dp0 "

:: Set destination to the OneDrive folder (CHANGE THIS PATH!)
set DEST="C:\Users\zaeem\Hudson Valley Community College\Christopher M Mascolo - Self Balancing Robot"

:: Run the sync
:: /MIR perfectly mirrors the folders (adds new files, deletes removed ones)
:: /XD excludes directories (.git and your local Archive)
:: /XF excludes specific files (.gitignore and this batch script)
robocopy %SOURCE% %DEST% /MIR /XD .git Archive /XF .gitignore deploy.bat

echo.
echo Deployment Complete!
pause