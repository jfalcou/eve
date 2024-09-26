// revision 1
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
    eve::wide wf0{eve::nan(eve::as<double>()), eve::inf(eve::as<double>())};
//  eve::wide wf0{-0.0,  1.30, -1.3,  eve::inf(eve::as<double>())}; //,
  //    0.0f, eve::nan(eve::as<float>()), 2.0f,  eve::prev(2.0f)};

   std::cout << "<- wf0                          = " << wf0 << "\n";

  std::cout << "-> modf(wf0)                    = " << eve::modf(wf0) << "\n";
  std::cout << "-> modf[raw](wf0)               = " << eve::modf[eve::raw](wf0) << "\n";
  std::cout << "-> modf[pedantic](wf0)          = " << eve::modf[eve::pedantic](wf0) << "\n";
  std::cout << "-> modf[almost](wf0)            = " << eve::modf[eve::almost](wf0) << "\n";
}
