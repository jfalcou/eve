// revision 1
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  eve::wide wf0 = {3.0f, 2.5f, 32.7f, 1.0f};

  std::cout << "<- wf0                = " << wf0 << "\n";

  std::cout << "-> two_sqrt_approx(wf0) = " << eve::two_sqrt_approx(wf0) << "\n";

  auto [d, e] = eve::two_sqrt_approx(3.0f);
  std::cout << std::setprecision(15);
  std::cout << double(d) << " + " << double(e) << std::endl;
  std::cout << double(e)+double(d) << std::endl;
  std::cout << eve::sqrt(3.0) << std::endl;
  std::cout << eve::sqrt(3.0f) <<  std::endl;
  std::cout << eve::sqrt(3.0) - (double(e)+double(d))<< std::endl;
}
