// revision 1
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0 = {30.0, 2.5, -32.7, 1.0};
  eve::wide wf1 = {4.2, 1.5, -100.834, eve::eps(eve::as<double>())/2};
  eve::wide wf2 = {2.0, 1.234, -2.0,  eve::eps(eve::as<double>())/2};

  std::cout << "<- wf0                      = " << wf0 << "\n";
  std::cout << "<- wf1                      = " << wf1 << "\n";
  std::cout << "<- wf2                      = " << wf2 << "\n";

  std::cout << "-> three_fma(wf0, wf1, wf2) = " << eve::three_fma(wf0, wf1, wf2) << "\n";
}
