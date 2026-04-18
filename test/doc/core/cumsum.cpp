// revision 0
#include <eve/module/core.hpp>
#include <iostream>


int main()
{
  kumi::tuple t{1.0f, 2.0f, 30000.0f, 10000.0f};
  std::cout << "t                                   " << t                                    << std::endl;
  std::cout << "eve::cumsum(t)                      " << eve::cumsum(t)                      << std::endl;
  std::cout << "eve::cumsum(1.0, 2.0, 3.0, 10000.0) " << eve::cumsum(1.0, 2.0, 30000.0, 10000.0) << std::endl;
  std::cout << "eve::cumsum(t)                      " << eve::cumsum(t)                      << std::endl;
  std::cout << "eve::cumsum[eve::widen](t)          " << eve::cumsum[eve::widen](t)          << std::endl;
  std::array<std::int16_t, 4> a{1, 2, 30000, 10000};
  auto ta = std::bit_cast<kumi::result::fill_t<4, std::int16_t>>(a);
  std::cout << "eve::cumsum[eve::saturated](ta)     " << eve::cumsum[eve::saturated](ta)    << std::endl;
  std::cout << "eve::cumsum(ta)                     " << eve::cumsum(ta)                    << std::endl;
  std::cout << "eve::cumsum[eve::widen](ta)         " << eve::cumsum[eve::widen](ta)        << std::endl;
  using wf_t = eve::wide<float>;
  auto e = wf_t([](auto i,  auto){return eve::sqr(float(i)); });
  kumi::tuple wt{wf_t(e), 2.0f, 30000.0f, 10000.0f};
  std::cout << "wt                                  " << wt                                 << std::endl;
  std::cout << "eve::cumsum(wt)                     " << eve::cumsum(wt)                    << std::endl;

};
