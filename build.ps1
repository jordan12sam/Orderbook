param([bool]$enable_tests=$false)
$enable_tests_str = 'OFF'
if ( $enable_tests )
{
    $enable_tests_str = 'ON'
}
Remove-Item -Recurse -Force build
Remove-Item -Force orderbook-app.exe
Remove-Item -Force orderbook-test.exe
mkdir build
cd build
cmake -DENABLE_TESTS="$enable_tests_str" ..
cmake --build .
robocopy ./core/app/Debug .. orderbook-app.exe
robocopy ./core/test/Debug .. orderbook-test.exe
cd ..