// revision 1
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0 = {30.0, 2.5, -32.7, 1.0};
  eve::wide wf1 = {4.2, 1.5, -100.834, eve::eps(eve::as<double>())/2};

  std::cout << "<- wf0               = " << wf0 << "\n";
  std::cout << "<- wf1               = " << wf1 << "\n";

  std::cout << "-> fast_two_add(wf0, wf1) = " << eve::fast_two_add(wf0, wf1) << "\n";
}
