// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  auto inf  = eve::inf(eve::as<double>());
  // auto minf = eve::minf(eve::as<double>());
  auto mind = eve::mindenormal(eve::as<double>());
  auto nan  = eve::nan(eve::as<double>());

  eve::wide wf0{0.0, 1.0, -2.0, nan, inf, mind, inf, -0.0};

  std::cout << "<- wf0                         = " << wf0 << "\n";

  std::cout << "-> fpclassify(wf0, qnan)                 = " << eve::fpclassify(std::integral_constant<std::uint8_t, 0x1>(), wf0) << "\n";
  std::cout << "-> fpclassify(wf0, poszero)              = " << eve::fpclassify(std::integral_constant<std::uint8_t, 0x2>(), wf0) << "\n";
  std::cout << "-> fpclassify(wf0, negzero)              = " << eve::fpclassify(std::integral_constant<std::uint8_t, 0x4>(), wf0) << "\n";
  std::cout << "-> fpclassify(wf0, posinf)               = " << eve::fpclassify(std::integral_constant<std::uint8_t, 0x8>(), wf0) << "\n";
  std::cout << "-> fpclassify(wf0, neginf)               = " << eve::fpclassify(std::integral_constant<std::uint8_t, 0x10>(), wf0) << "\n";
  std::cout << "-> fpclassify(wf0, denorn)               = " << eve::fpclassify(std::integral_constant<std::uint8_t, 0x20>(), wf0) << "\n";
  std::cout << "-> fpclassify(wf0, neg)                  = " << eve::fpclassify(std::integral_constant<std::uint8_t, 0x40>(), wf0) << "\n";
  std::cout << "-> fpclassify(wf0, snan)                 = " << eve::fpclassify(std::integral_constant<std::uint8_t, 0x80>(), wf0) << "\n";
  std::cout << "-> fpclassify(eve::selected_classes<neg, posinf>(), wf0>= " <<
    eve::fpclassify(eve::selected_classes<eve::detail::fpclass::poszero, eve::detail::fpclass::posinf, eve::detail::fpclass::neg>(), wf0) << std::endl;

  std::cout << "-> fpclassify(eve::selected_classes<...>(), wf0>= " <<
     eve::fpclassify(std::integral_constant<std::uint8_t, 0x2|0x8|0x40 >(), wf0) << std::endl;


//   std::cout << -((a > 0).mask()) << std::endl;
//   std::cout << ((b > 0).mask() >> (sizeof(std::uint8_t)*8-1))<< std::endl;
 }
