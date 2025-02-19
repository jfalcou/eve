// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i+c/2);});
  eve::wide wf1{-3.0, 0.5, 3.0, 4.0};
  eve::wide wi = {93, 25, 32, 180, 1, 2, 3, 4};
  eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;});

  std::cout << "<- wf            = " << wf << "\n";
  std::cout << "<- wf1           = " << wf1<< "\n";
  std::cout << "<- wi            = " << wi << "\n";
  std::cout << "<- wu            = " << wu << "\n";

  std::cout << "-> factorial(wf) = " << eve::factorial(wf) << "\n";
  std::cout << "-> factorial(wi) = " << eve::factorial(wi) << "\n";
  std::cout << "-> factorial(wu) = " << eve::factorial(wu) << "\n";
  std::cout << "-> factorial(wf1) = " << eve::factorial(wf1) << "\n";
  std::cout << "-> factorial[pedantic](wf1) = " << eve::factorial[eve::pedantic](wf1) << "\n";

}
