// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{

  eve::wide wf0 = {3, 2, 1, 0};
  eve::wide wf1 = {4, 1, 2, 100};
  eve::wide wf2 = -wf0-4*eve::eps(eve::as<float>());
  eve::wide wf3 = -wf1+4*eve::eps(eve::as<float>());

  std::cout << "<- wf0                                             = " << wf0 << "\n";
  std::cout << "<- wf1                                             = " << wf1 << "\n";
  std::cout << "<- wf2                                             = " << wf2 << "\n";
  std::cout << "<- wf3                                             = " << wf3 << "\n";

  std::cout << "-> sum_of_prod(wf0, wf1, wf2, wf3)                 = " << eve::sum_of_prod(wf0, wf1, wf2, wf3) << "\n";
  std::cout << "-> sum_of_prod[ignore_last(2)](wf0, wf1, wf2, wf3) = " << eve::sum_of_prod[eve::ignore_last(2)](wf0, wf1, wf2, wf3) << "\n";
  std::cout << "-> sum_of_prod[raw](wf0, wf1, wf2, wf3)            = " << eve::sum_of_prod[eve::raw](wf0, wf1, wf2, wf3) << "\n";
  std::cout << "-> sum_of_prod[pedantic](wf0, wf1, wf2, wf3)       = " << eve::sum_of_prod[eve::pedantic](wf0, wf1, wf2, wf3) << "\n";
}
