param (
    [string]$arg
)

if ($arg -eq "1") {
    & .\main
} else {
    & g++ -o main main.cpp .\include\jsoncpp\jsoncpp.cpp

    if ($LASTEXITCODE -eq 0) {
        Write-Host "Software Compiled Successfully. Running the software now..." -ForegroundColor Green
        & .\main
    } else {
        Write-Host "Compilation failed. Please check the code and try again." -ForegroundColor Red
    }
}