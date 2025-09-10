// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>
#include <tts/tts.hpp>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wf1{2.0, 3.0, -1.0, -2.0, -3.0, -4.0, 18.0, 32.0};

  std::cout << "<- wf0                                  = " << wf0 << "\n";
  std::cout << "<- wf1                                  = " << wf1 << "\n";

  std::cout << "-> average(wf0, 2*wf0, 3*wf0)           = " << eve::average(wf0, 2*wf0, 3*wf0) << "\n";
  std::cout << "-> average[kahan](wf0, 2*wf0, 3*wf0)    = " << eve::average[eve::kahan](wf0, 2*wf0, 3*wf0) << "\n";

}
