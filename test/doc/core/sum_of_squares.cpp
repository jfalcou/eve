// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>
#include <cfenv>


int main()
{
  eve::wide wf0{1.0f, 1.0f, 2.0f, 3.0f, -1.0f, -2.0f, -3.0f, -4.0f};
  eve::wide wf1{eve::eps(eve::as(1.0f))/4, -eve::eps(eve::as(1.0f))/4, 1.0f, -1.0f, 2.0f, -2.0f, 3.0f, -3.0f};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wi1{0, -4, 1, -1, 2, -2, 3, -3};
  eve::wide<std::uint16_t, eve::fixed<8>> wu0{65534u, 65000u, 2u, 3u, 4u, 5u, 6u, 7u};
  eve::wide<std::uint16_t, eve::fixed<8>> wu1{2u, 6u, 5u, 4u, 3u, 2u, 1u, 0u};

  std::cout << std::setprecision(20) << "<- wf0                           = " << wf0 << "\n";
  std::cout << std::setprecision(20) << "<- wf1                           = " << wf1 << "\n";
  std::cout << "<- wi0                           = " << wi0 << "\n";
  std::cout << "<- wi1                           = " << wi1 << "\n";
  std::cout << "<- wu0                           = " << wu0 << "\n";
  std::cout << "<- wu1                           = " << wu1 << "\n";

  std::cout << "-> sum_of_squares(wf0, wf1)                 = " << eve::sum_of_squares(wf0, wf1) << "\n";
  std::cout << "-> sum_of_squares[ignore_last(2)](wf0, wf1) = " << eve::sum_of_squares[eve::ignore_last(2)](wf0, wf1) << "\n";
  std::cout << "-> sum_of_squares[wf0 != 0](wf0, wf1)       = " << eve::sum_of_squares[wf0 != 0](wf0, wf1) << "\n";
  std::cout << "-> sum_of_squares(wu0, wu1)                 = " << eve::sum_of_squares(wu0, wu1) << "\n";
  std::cout << "-> sum_of_squares(wi0, wi1)                 = " << eve::sum_of_squares(wi0, wi1) << "\n";

  std::cout << std::setprecision(20) << "-> sum_of_squares(wf0, wf1)                  = " << eve::sum_of_squares(wf0, wf1) << "\n";
  std::cout << std::setprecision(20) << "-> sum_of_squares[to_nearest_odd(wf0, wf1)   = " << eve::sum_of_squares(wf0, wf1) << "\n";
  std::cout << std::setprecision(20) << "-> sum_of_squares[lower](wf0, wf1)           = " << eve::sum_of_squares[eve::lower](wf0, wf1) << "\n";
  std::cout << std::setprecision(20) << "-> sum_of_squares[upper](wf0, wf1)           = " << eve::sum_of_squares[eve::upper](wf0, wf1) << "\n";
  std::cout << std::setprecision(20) << "-> sum_of_squares[lower][strict](wf0, wf1)   = " << eve::sum_of_squares[eve::lower][eve::strict](wf0, wf1) << "\n";
  std::cout << std::setprecision(20) << "-> sum_of_squares[upper][strict](wf0, wf1)   = " << eve::sum_of_squares[eve::upper][eve::strict](wf0, wf1) << "\n";

//   std::cout << "-> sum_of_squares(wu0, wu1)                 = " << eve::sum_of_squares(wu0, wu1) << "\n";
//   std::cout << "-> sum_of_squares[widen](wu0, wu1)          = " << eve::sum_of_squares[eve::widen](wu0, wu1) << "\n";
//   std::cout << "-> sum_of_squares(wf0, wf1)                 = " << eve::sum_of_squares(wf0, wf1) << "\n";
//   std::cout << "-> sum_of_squares[widen](wf0, wf1)          = " << eve::sum_of_squares[eve::widen](wf0, wf1) << "\n";
  auto sqteps_2 = eve::sqrteps(eve::as<float>())/2;
  double dsqteps_2 = double(sqteps_2);
  std::cout << "-> sum_of_squares(1.0f, sqteps_2, sqteps_2, sqteps_2, sqteps_2)          = " << eve::sum_of_squares(1.0f, sqteps_2, sqteps_2, sqteps_2, sqteps_2) << "\n";
  std::cout << "-> sum_of_squares[kahan](1.0f, sqteps_2, sqteps_2, sqteps_2, sqteps_2)   = " << eve::sum_of_squares[eve::kahan](1.0f, sqteps_2, sqteps_2, sqteps_2, sqteps_2) << "// float result\n";
  std::cout << "-> sum_of_squares(1.0, dsqteps_2, dsqteps_2, dsqteps_2, dsqteps_2)   = " << eve::sum_of_squares(1.0, dsqteps_2, dsqteps_2, dsqteps_2, dsqteps_2) << "// double result\n";

}
