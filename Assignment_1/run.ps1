# Compile the C++ code
mkdir .\db > $null -ErrorAction SilentlyContinue

# Check if directory creation failed
if (-not (Test-Path .\db)) {
    Write-Host "Error: Administrative privileges are required to create the directory."
    Write-Host "Please run the script with elevated privileges."
    exit 1
}

& g++ -o main main.cpp "include\sqlite\libsqlite3.a" -I"\include\sqlite" -static-libgcc -static-libstdc++

# Check if compilation was successful
if ($LASTEXITCODE -eq 0) {
    Write-Host "Software Compiled Successfully. Running the software now..." -ForegroundColor Green
    
    # Run the compiled program
    & .\main
} else {
    Write-Host "Compilation failed. Please check the code and try again." -ForegroundColor Red
}
