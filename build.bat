@echo off
g++ 2_Account.cpp 4_SavingsAccount.cpp 6_CurrentAccount.cpp 7_main.cpp -o bank.exe
if %errorlevel% neq 0 (
    echo Build failed. Please install MinGW-w64 and add to PATH.
    exit /b %errorlevel%
)
echo Build successful! Run bank.exe to start.
