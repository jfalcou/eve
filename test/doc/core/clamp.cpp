// revision 1 TODO investigate last result
#include <eve/module/core.hpp>
#include <iostream>

eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});

int main(){
  auto ma = eve::maximum(wf)/2;
  auto mi = eve::minimum(wf)/2;
  std::cout << "<- wf = " << wf << "\n";
  std::cout << "<- ma = " << ma << "\n";
  std::cout << "<- mi = " << mi << "\n";

  std::cout << "-> clamp(wf, mi, ma)                 = " << eve::clamp(wf, mi, ma)  << "\n";
  std::cout << "-> clamp[ignore_last(2)](wf, mi, ma) = " << eve::clamp[eve::ignore_last(2)](wf, mi, ma)  << "\n";
  std::cout << "-> clamp[wf != -4.0f](wf, mi, ma)    = " << eve::clamp[wf != -2.0f](wf, mi, ma)  << "\n";

}
