// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>
#include <cfenv>


int main()
{
  eve::wide wf0{1.0f, 1.0f, 2.0f, 3.0f, -1.0f, -2.0f, -3.0f, -4.0f};
  eve::wide wf1{eve::eps(eve::as(1.0f))/4, -eve::eps(eve::as(1.0f))/4, 1.0f, -1.0f, 2.0f, -2.0f, 3.0f, -3.0f};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wi1{0, -4, 1, -1, 2, -2, 3, -3};
  eve::wide<std::uint16_t, eve::fixed<8>> wu0{65534u, 65000u, 2u, 3u, 4u, 5u, 6u, 7u};
  eve::wide<std::uint16_t, eve::fixed<8>> wu1{2u, 6u, 5u, 4u, 3u, 2u, 1u, 0u};

  std::cout << std::setprecision(16) << "<- wf0                           = " << wf0 << "\n";
  std::cout << std::setprecision(16) << "<- wf1                           = " << wf1 << "\n";
  std::cout << "<- wi0                           = " << wi0 << "\n";
  std::cout << "<- wi1                           = " << wi1 << "\n";
  std::cout << "<- wu0                           = " << wu0 << "\n";
  std::cout << "<- wu1                           = " << wu1 << "\n";

  std::cout << "-> add(wf0, wf1)                 = " << eve::add(wf0, wf1) << "\n";
  std::cout << "-> add[ignore_last(2)](wf0, wf1) = " << eve::add[eve::ignore_last(2)](wf0, wf1) << "\n";
  std::cout << "-> add[wf0 != 0](wf0, wf1)       = " << eve::add[wf0 != 0](wf0, wf1) << "\n";
  std::cout << "-> add(wu0, wu1)                 = " << eve::add(wu0, wu1) << "\n";
  std::cout << "-> add(wi0, wi1)                 = " << eve::add(wi0, wi1) << "\n";

  std::cout << std::setprecision(16) << "-> add(wf0, wf1)                  = " << eve::add(wf0, wf1) << "\n";
  std::cout << std::setprecision(16) << "-> add[to_nearest_odd(wf0, wf1)   = " << eve::add(wf0, wf1) << "\n";
  std::cout << std::setprecision(16) << "-> add[lower](wf0, wf1)           = " << eve::add[eve::lower](wf0, wf1) << "\n";
  std::cout << std::setprecision(16) << "-> add[upper](wf0, wf1)           = " << eve::add[eve::upper](wf0, wf1) << "\n";
  std::cout << std::setprecision(16) << "-> add[lower][strict](wf0, wf1)   = " << eve::add[eve::lower][eve::strict](wf0, wf1) << "\n";
  std::cout << std::setprecision(16) << "-> add[upper][strict](wf0, wf1)   = " << eve::add[eve::upper][eve::strict](wf0, wf1) << "\n";

  std::cout << "-> add(wu0, wu1)                 = " << eve::add(wu0, wu1) << "\n";
  std::cout << "-> add[widen](wu0, wu1)          = " << eve::add[eve::widen](wu0, wu1) << "\n";
  std::cout << "-> add(wf0, wf1)                 = " << eve::add(wf0, wf1) << "\n";
  std::cout << "-> add[widen](wf0, wf1)          = " << eve::add[eve::widen](wf0, wf1) << "\n";
  auto eps_4 = eve::eps(eve::as<float>())/4;
  std::cout << "-> add(1.0f, eps_4, eps_4, eps_4, eps_4)          = " << eve::add(1.0f, eps_4, eps_4, eps_4, eps_4) << "\n";
  std::cout << "-> add[kahan](1.0f, eps_4, eps_4, eps_4, eps_4)   = " << eve::add[eve::kahan](1.0f, eps_4, eps_4, eps_4, eps_4) << "// float result\n";
  std::cout << "-> add(1.0f, eps_4, eps_4, eps_4, eps_4)          = " << eve::add(1.0f, eps_4, eps_4, eps_4, eps_4) << "\n";
  std::cout << "-> add[widen](1.0f, eps_4, eps_4, eps_4, eps_4)   = " << float(eve::add[eve::widen](1.0f, eps_4, eps_4, eps_4, eps_4)) << "// double result converted to float\n";
  auto tup = kumi::tuple{1.0f, eps_4, eps_4, eps_4, eps_4};
  std::cout << "-> add[kahan](tup)                                = " << eve::add[eve::kahan](tup) << "\n";
  std::cout << eve::add[eve::kahan](1.0, 2.0, 3.0, 4.0, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0) << std::endl;
  std::cout << eve::add[eve::widen](1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f) << std::endl;
  std::cout << sizeof(eve::add[eve::widen](1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f)) << std::endl;
  std::cout << eve::add(0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4., -6.0) << "\n";

}
