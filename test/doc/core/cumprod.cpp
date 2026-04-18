// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <bit>

int main()
{
  kumi::tuple t{1.0f, 2.0f, 3.0f, 10000.0f};
  std::cout << "t                                    " << t                                    << std::endl;
  std::cout << "eve::cumprod(t)                      " << eve::cumprod(t)                      << std::endl;
  std::cout << "eve::cumprod(1.0, 2.0, 3.0, 10000.0) " << eve::cumprod(1.0, 2.0, 3.0, 10000.0) << std::endl;
  std::cout << "eve::cumprod(t)                      " << eve::cumprod(t)                      << std::endl;
  std::cout << "eve::cumprod[eve::widen](t)          " << eve::cumprod[eve::widen](t)          << std::endl;
  std::array<std::int16_t, 4> a{1, 2, 3, 10000};
  auto ta = std::bit_cast<kumi::result::fill_t<4, std::int16_t>>(a);
  std::cout << "eve::cumprod[eve::saturated](ta)     " << eve::cumprod[eve::saturated](ta)    << std::endl;
  std::cout << "eve::cumprod(ta)                     " << eve::cumprod(ta)                    << std::endl;
  std::cout << "eve::cumprod[eve::widen](ta)         " << eve::cumprod[eve::widen](ta)        << std::endl;


};
