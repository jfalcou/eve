// revision 0
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>


int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wf1{0.0, -4.0, 1.0, -1.0, 2.0, -2.0, 3.0, -3.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wi1{0, -4, 1, -1, 2, -2, 3, -3};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};
  eve::wide wu1{7u, 6u, 5u, 4u, 3u, 2u, 1u, 0u};

  std::cout << "<- wf0                           = " << wf0 << "\n";
  std::cout << "<- wf1                           = " << wf1 << "\n";
  std::cout << "<- wi0                           = " << wi0 << "\n";
  std::cout << "<- wi1                           = " << wi1 << "\n";
  std::cout << "<- wu0                           = " << wu0 << "\n";
  std::cout << "<- wu1                           = " << wu1 << "\n";

  std::cout << "-> mul(wf0, wf1)                 = " << eve::mul(wf0, wf1) << "\n";
  std::cout << "-> mul[ignore_last(2)](wf0, wf1) = " << eve::mul[eve::ignore_last(2)](wf0, wf1) << "\n";
  std::cout << "-> mul[wf0 != 0](wf0, wf1)       = " << eve::mul[wf0 != 0](wf0, wf1) << "\n";
  std::cout << "-> mul(wu0, wu1)                 = " << eve::mul(wu0, wu1) << "\n";
  std::cout << "-> mul(wi0, wi1)                 = " << eve::mul(wi0, wi1) << "\n";

  std::cout << "-> mul(wu0, wu1)                 = " << eve::mul(wu0, wu1) << "\n";
  std::cout << "-> mul[widen](wu0, wu1)          = " << eve::mul[eve::widen](wu0, wu1) << "\n";
  std::cout << "-> mul(wf0, wf1)                 = " << eve::mul(wf0, wf1) << "\n";
  std::cout << "-> mul[widen](wf0, wf1)          = " << eve::mul[eve::widen](wf0, wf1) << "\n";
  std::cout << std::setprecision(15);
  auto pi = eve::pi(eve::as<float>());
  auto e  = eve::euler(eve::as<float>());
  auto l2 = eve::log_2(eve::as<float>());
  auto tup = eve::zip{pi, e, 1.2345f, l2, pi, e, 1.2345f, l2, 1.35f*pi, l2+pi,  0.07856f};
  std::cout << "-> mul[kahan](tup)  = " << eve::mul[eve::kahan](tup) << "\n";
  std::cout << "-> mul(tup)         = " << eve::mul(tup) << "\n";
  std::cout << "-> mul[widen](tup)  = " << float(eve::mul[eve::widen](tup)) << "\n";
  auto z = eve::zip(wf0, wf1, wf1);
  std::cout << "-> mul[kahan](wf0, wf1, wf1)  = " << eve::mul[eve::kahan](z) << "\n";
  std::cout << "-> mul[kahan](wf0, wf1, wf1)  = " << eve::mul[eve::kahan](wf0, wf1, wf1) << "\n";

}
