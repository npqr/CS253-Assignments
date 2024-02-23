# Compile the C++ code
& g++ main.cpp -o main

# Check if compilation was successful
if ($LASTEXITCODE -eq 0) {
    Write-Host "Software Compiled Successfully. Running the software now..." -ForegroundColor Green
    
    # Run the compiled program
    & .\main
} else {
    Write-Host "Compilation failed. Please check the code and try again." -ForegroundColor Red
}
