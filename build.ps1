param([bool]$enable_tests=$false)
$enable_tests_str = 'OFF'
if ( $enable_tests )
{
    $enable_tests_str = 'ON'
}
Remove-Item -Recurse -Force build
Remove-Item -Force Orderbook.exe
Remove-Item -Force Orderbook-Tests.exe
mkdir build
cd build
cmake -DENABLE_TESTS="$enable_tests_str" ..
cmake --build .
robocopy ./Debug .. Orderbook.exe
robocopy ./Debug .. Orderbook-Tests.exe