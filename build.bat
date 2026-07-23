@echo off
g++ main.cpp Account.cpp SavingsAccount.cpp CurrentAccount.cpp -o bank.exe
if %errorlevel% neq 0 (
    echo Build failed. Please install MinGW-w64 or another C++ compiler and add it to PATH.
    exit /b %errorlevel%
)
echo Build completed successfully. Run bank.exe to start the program.
