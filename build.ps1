param([bool]$enable_tests=$false)
$enable_tests_str = 'OFF'
if ( $enable_tests )
{
    $enable_tests_str = 'ON'
}
try {Remove-Item -Recurse -Force build} catch {}
try {Remove-Item -Force orderbook-app.exe} catch {}
try {Remove-Item -Force orderbook-test.exe} catch {}
mkdir build
cd build
cmake -DENABLE_TESTS="$enable_tests_str" ..
cmake --build .
Copy-Item "./core/app/Debug/orderbook-app.exe" -Destination ".."
Copy-Item "./core/test/Debug/orderbook-test.exe" -Destination ".."
cd ..