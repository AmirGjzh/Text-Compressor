@echo off
REM ============================================================
REM Huffman Text Compressor - Compilation and Setup Script
REM ============================================================

echo.
echo ==================== Compilation ====================
echo.

cd src

echo Compiling main.c...
gcc -o main.exe main.c

if %ERRORLEVEL% EQU 0 (
    echo.
    echo [OK] Compilation successful!
    echo [OK] Executable created: main.exe
    echo.
    echo ==================== Next Steps ====================
    echo.
    echo 1. Place your text file in the 'samples' folder
    echo.
    echo 2. To compress a file:
    echo    main com ..\samples\yourfile.txt
    echo.
    echo 3. To decompress:
    echo    main decom ..\output\Compressed.txt ..\output\Guide.txt
    echo.
    echo 4. For help:
    echo    main help
    echo.
    echo ====================================================
    echo.
) else (
    echo.
    echo ✗ Compilation failed!
    echo Please check your GCC installation.
    echo.
)

cd ..
pause
