// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <numeric>


int main()
{
  kumi::tuple t{ 2.0f, 3.0f, 1.0f,10000.0f};
  std::cout << "t                                        " << t                                             << std::endl;
  std::cout << "eve::cumfun(add, t)                      " << eve::cumfun(eve::add, t)                      << std::endl;
  std::cout << "eve::cumfun(add, 1.0, 2.0, 3.0, 10000.0) " << eve::cumfun(eve::add, 1.0, 2.0, 3.0, 10000.0) << std::endl;
  std::cout << "eve::cumfun(add, t)                      " << eve::cumfun(eve::add, t)                      << std::endl;
  std::cout << "eve::cumfun[eve::widen](add, t)          " << eve::cumfun[eve::widen](eve::add, t)          << std::endl;
  std::cout << "eve::cumfun(mul, t)          " << eve::cumfun(eve::mul, t)          << std::endl;
  std::cout << "eve::cumfun(min, t)          " << eve::cumfun(eve::min, t)          << std::endl;
  std::array<std::int16_t, 4> a{1, 2, 3, 32767};
  auto ta = std::bit_cast<kumi::result::fill_t<4, std::int16_t>>(a);
  std::cout << "ta                                       " << ta << std::endl;
  std::cout << "eve::cumfun[eve::saturated](add, ta)     " << eve::cumfun[eve::saturated](eve::add, ta)     << std::endl;
  std::cout << "eve::cumfun(add, ta)                     " << eve::cumfun(eve::add, ta)                     << std::endl;
  std::cout << "eve::cumfun[eve::widen](add, ta)         " << eve::cumfun[eve::widen](eve::add, ta)         << std::endl;
  using wf_t = eve::wide<float>;
  auto e = wf_t([](auto i,  auto){return eve::sqr(float(i)); });
  kumi::tuple wt{wf_t(e), 2.0f, 30000.0f, 100000.0f};
  std::cout << "wt                                       " << wt                                            << std::endl;
  std::cout << "eve::cumfun(add, wt)                     " << eve::cumfun(eve::add, wt)                     << std::endl;
  std::cout << "eve::cumfun(mul, wt)                     " << eve::cumfun(eve::mul, wt)                     << std::endl;
  std::cout << "eve::cumfun(add, wt)                     " << eve::cumfun(eve::add, wt)                     << std::endl;
  std::cout << "eve::cumfun(min, wt)                     " << eve::cumfun(eve::min, wt)                     << std::endl;
  std::cout << "eve::cumfun(max, wt)                     " << eve::cumfun(eve::max, wt)                     << std::endl;
};
