// revision 1
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  eve::wide wf0 = {3.0f, 2.5f, -32.7f, 1.0f};
  eve::wide wf1 = {4.2f, 1.5f, -100.834f, eve::eps(eve::as<float>())/2};

  std::cout << "<- wf0                = " << wf0 << "\n";
  std::cout << "<- wf1                = " << wf1 << "\n";

  std::cout << "-> two_div_approx(wf0, wf1) = " << eve::two_div_approx(wf0, wf1) << "\n";

  auto [d, e] = eve::two_div_approx(1.0f, 3.0f);
  std::cout << std::setprecision(15);
  std::cout << double(d) << " + " << double(e) << std::endl;
  std::cout << double(e)+double(d) << std::endl;
  std::cout << 1.0/3.0 << std::endl;
  std::cout << 1.0f/3.0f <<  std::endl;
  std::cout <<  1.0/3.0 - (double(e)+double(d))<< std::endl;
}
