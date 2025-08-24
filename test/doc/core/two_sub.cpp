// revision 1
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  eve::wide wf0 = {3.0f, 2.5f, -32.7f, 1.0f};
  eve::wide wf1 = {4.2f, 1.5f, -100.834f, eve::eps(eve::as<float>())/2};

  std::cout << "<- wf0               = " << wf0 << "\n";
  std::cout << "<- wf1               = " << wf1 << "\n";
  std::cout << std::setprecision(20);
  std::cout << "-> two_sub(wf0, wf1)      = " << eve::two_sub(wf0, wf1) << "\n";
  std::cout << "-> two_sub[raw](wf0, wf1) = " << eve::two_sub[eve::raw](wf0, wf1) << "\n";
}
