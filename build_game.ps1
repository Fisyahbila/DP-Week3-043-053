$files = @(Get-ChildItem -Path "$PSScriptRoot\src" -Filter *.cpp -Recurse | Where-Object {$_.Name -ne "test_main.cpp"} | Select-Object -ExpandProperty FullName)
& "C:\ucrt64\bin\g++.exe" -fdiagnostics-color=always -g $files -o "$PSScriptRoot\balatro_game.exe"
