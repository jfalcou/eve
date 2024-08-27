#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide<int, eve::fixed<4>> in {-1, 1, 2, 3};
  auto out = eve::simd_cast(in, eve::as<eve::wide<std::uint8_t, eve::fixed<8>>>{});

  // Should print two first integers as bytes
  std::cout << out << std::endl;
}
