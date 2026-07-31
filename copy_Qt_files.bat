set QT_BIN=C:\tools\Qt\6.11.1\msvc2022_64\bin
set EXE=C:\Users\morit\OneDrive\Anwendungen\Smoeresizer\out\debug\Smoeresizer.exe

if not exist "%EXE%" (
    echo Executable not found: %EXE%
    exit /b 1
)

"%QT_BIN%\windeployqt6.exe" --debug "%EXE%"