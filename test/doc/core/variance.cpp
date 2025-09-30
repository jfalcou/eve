// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, 1.0};
  eve::wide wf1{0.0, -4.0, 1.0, -1.0, 2.0, -2.0, -eve::smallestposval(eve::as(1.0)), eve::smallestposval(eve::as(1.0))};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wi1{0, -4, 1, -1, 2, -2, 3, -3};

  std::cout << "<- wf0                                        = " << wf0 << "\n";
  std::cout << "<- wf1                                        = " << wf1 << "\n";
  std::cout << "<- wi0                                        = " << wi0 << "\n";
  std::cout << "<- wi1                                        = " << wi1 << "\n";
  std::cout << std::setprecision(15);

  std::cout << "-> variance(wf0, wf1)                          = " << eve::variance(wf0, wf1) << "\n";
  std::cout << "-> variance(wi0, wi1)                          = " << eve::variance(wi0, wi1) << "\n";
  std::cout << "-> variance[ignore_last(2)](wi0, wi1)          = " << eve::variance[eve::ignore_last(2)](wi0, wi1) << "\n";
  std::cout << "-> variance[wi0 != 0](wi0, wi1)                = " << eve::variance[wi0 != 0](wi0, wi1) << "\n";
  std::cout << "-> variance[raw](wi0, wi1)                     = " << eve::variance[eve::raw](wi0, wi1) << "\n";
  auto eps_2 = eve::eps(eve::as<float>())/2;
  std::cout << "-> variance(1.0f, eps_2, eps_2, eps_2)         = " << eve::variance(1.0f, eps_2, eps_2, eps_2) << "\n";
  std::cout << "-> variance[kahan](1.0f, eps_2, eps_2, eps_2)  = " << eve::variance[eve::kahan](1.0f, eps_2, eps_2, eps_2) << " // float computation\n";
  std::cout << "-> variance[raw](1.0f, eps_2, eps_2, eps_2)    = " << eve::variance[eve::raw](1.0f, eps_2, eps_2, eps_2) << "\n";
  auto deps_2 = double(eps_2);
  std::cout << "-> variance(1.0, deps_2, deps_2, eps_2)        = " << float(eve::variance[eve::kahan](1.0, deps_2, deps_2, deps_2)) << " // double computation converted to float\n";
  auto tup = kumi::tuple{1.0f, eps_2, eps_2, eps_2};
  std::cout << "-> variance[kahan](tup)   = " << eve::variance[eve::kahan](tup) << "\n";
  std::cout <<eve::variance(1.0f, 2.0f, 3.0f, 4.0f) << "\n";
  std::cout <<eve::variance[eve::raw](1.0f, 2.0f, 3.0f, 4.0f) << "\n";
  std::cout <<eve::variance[eve::unbiased](1.0f, 2.0f, 3.0f, 4.0f) << "\n";
  std::cout <<eve::variance[eve::unbiased][eve::raw](1.0f, 2.0f, 3.0f, 4.0f) << "\n";
  std::cout <<eve::variance[eve::unbiased][eve::raw][eve::widen](1.0f, 2.0f, 3.0f, 4.0f) << "\n";

}
