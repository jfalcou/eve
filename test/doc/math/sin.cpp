// revision 1
#include <eve/module/math.hpp>
#include <iostream>


int main()
{
  eve::wide wf = {0.0, 0.25, 0.5, 2.0, -0.0, -0.25, -0.5, -2.0};
  wf *= eve::pi[eve::downward](eve::as(wf));

  std::cout << "<- wf = " << wf << "\n";

  std::cout << "-> sin(wf)                = " << eve::sin(wf) << "\n";
  std::cout << "-> sin[ignore_last(2)](wf)= " << eve::sin[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> sin[wf != -2.0f](wf)   = " << eve::sin[wf != -2.0f](wf) << "\n";
  std::cout << "-> sin[quarter_circle](wf)= " << eve::sin[eve::quarter_circle](wf) << "\n";
  std::cout << "-> sin[half_circle](wf)   = " << eve::sin[eve::half_circle](wf) << "\n";
  std::cout << "-> sin[full_circle](wf)   = " << eve::sin[eve::full_circle](wf) << "\n";
}
