// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  auto spv  = eve::smallestposval(eve::as<double>());
  auto maxd = eve::prev(spv);
  auto mind = eve::mindenormal(eve::as<double>());
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, spv, mind, maxd, -0.0};

  std::cout << "<- wf0                         = " << wf0 << "\n";

  std::cout << "-> flush_denormal(wf0)                 = " << eve::flush_denormal(wf0) << "\n";
  std::cout << "-> flush_denormal[ignore_last(2)](wf0) = " << eve::flush_denormal[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> flush_denormal[wf0 != md](wf0)      = " << eve::flush_denormal[wf0 != mind](wf0) << "\n";
}
