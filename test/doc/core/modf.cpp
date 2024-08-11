// revision 1
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{-0.0f,  1.30f, -1.3f,  eve::inf(eve::as<float>()),  0.0f,
                eve::nan(eve::as<float>()), 2.0f,  eve::prev(2.0f)};

  std::cout << "<- wf0                          = " << wf0 << "\n";

  std::cout << "-> modf(wf0)                    = " << eve::modf(wf0) << "\n";
  std::cout << "-> modf[raw2](wf0)               = " << eve::modf[eve::raw2](wf0) << "\n";
  std::cout << "-> modf[pedantic](wf0)          = " << eve::modf[eve::pedantic](wf0) << "\n";
  std::cout << "-> modf[almost](wf0)            = " << eve::modf[eve::almost](wf0) << "\n";
}
