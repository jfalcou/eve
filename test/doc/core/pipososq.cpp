// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>
#include <cfenv>
#include <vector>


int main()
{
  eve::wide wf0{1.0f, 1.0f, 2.0f, 3.0f, -1.0f, -2.0f, -3.0f, -4.0f};
  eve::wide wf1{eve::eps(eve::as(1.0f))/4, -eve::eps(eve::as(1.0f))/4, 1.0f, -1.0f, 2.0f, -2.0f, 3.0f, -3.0f};
  std::cout << std::setprecision(15) << "<- wf0                           = " << wf0 << "\n";
  std::cout << "<- wf1                           = " << wf1 << "\n";
  std::cout << std::setprecision(16);
  auto sqteps_2 = eve::sqrteps(eve::as<float>())/2;
  std::cout << "-> sum_of_squares(1.0f, sqteps_2, sqteps_2, sqteps_2, sqteps_2)          = " << eve::sum_of_squares(1.0f, sqteps_2, sqteps_2, sqteps_2, sqteps_2) << "\n";
  std::cout << "-> sum_of_squares[kahan](1.0f, sqteps_2, sqteps_2, sqteps_2, sqteps_2)   = " << eve::sum_of_squares[eve::kahan](1.0f, sqteps_2, sqteps_2, sqteps_2, sqteps_2) << "// float result\n";
//  std::cout << "-> sum_of_squares[widen](1.0f, sqteps_2, sqteps_2, sqteps_2, sqteps_2)   = " << eve::sum_of_squares[eve::widen](1.0f, sqteps_2, sqteps_2, sqteps_2, sqteps_2) << "// double result\n";

  std::vector v{1.0f, sqteps_2, sqteps_2, sqteps_2, sqteps_2};
  std::cout << "-> sum_of_squares(v)   = " << eve::sum_of_squares(v) << "\n";

}
