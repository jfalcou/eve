#include <tts/tts.hpp>
#include <eve/module/dd.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using w_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  auto ep =  eve::eps(eve::as<float>());
  std::cout << ep << std::endl;
  w_ft hi = { 1.0f, 1.0f, 1.0f, 1.0f};
  w_ft lo = { 2*ep , ep,  ep/2, ep/4};
  using wdf_t = eve::as_dd_t<w_ft>;
  wdf_t z(hi, lo);
  std::cout << tts::typename_<wdf_t> << std::endl;
  std::cout << tts::typename_<eve::underlying_type_t<wdf_t>> << std::endl;

  std::cout
    << "---- simd" << std::setprecision(13) << std::endl
    << "<- z      = " << z << std::endl
    << "-> sqr(z) = " << eve::sqr(z) << std::endl;
  auto sz = eve::sqr(z);
  auto dsz = eve::sqr (eve::float64(eve::low(z))+eve::float64(eve::high(z)));
  std::cout << (eve::float64(eve::low(sz))+eve::float64(eve::high(sz))) << std::endl;
  std::cout << dsz << std::endl;
  std::cout << eve::abs(dsz-(eve::float64(eve::low(sz))+eve::float64(eve::high(sz)))) << std::endl;
  return 0;
}
