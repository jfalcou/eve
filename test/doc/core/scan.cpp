#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide x = {1.0, 2.0, 3.0, 4.0};

  std::cout << "x: " << x << "\n";
  std::cout << "eve::scan(x): " << eve::scan(x) << "\n";
  std::cout << "eve::scan(x, eve::mul, eve::one): " << eve::scan(x, eve::mul, eve::one) << "\n";
}
