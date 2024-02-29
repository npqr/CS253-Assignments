param (
    [string]$arg
)

if ($arg -eq "1") {
    # Run the compiled program
    & .\main
} else {
    # Compile the C++ code
    & g++ -o main main.cpp .\include\jsoncpp\jsoncpp.cpp

    # Check if compilation was successful
    if ($LASTEXITCODE -eq 0) {
        Write-Host "Software Compiled Successfully. Running the software now..." -ForegroundColor Green
        
        # Run the compiled program
        & .\main
    } else {
        Write-Host "Compilation failed. Please check the code and try again." -ForegroundColor Red
    }
}