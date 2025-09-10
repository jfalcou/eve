// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>
#include <tts/tts.hpp>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wf1{2.0, 3.0, -1.0, -2.0, -3.0, -4.0, 18.0, 32.0};
  using t_t = decltype(wf0);

  std::cout << "<- wf0                                  = " << wf0 << "\n";
  std::cout << "<- wf1                                  = " << wf1 << "\n";

  auto ma = eve::welford_average(wf0, 2*wf0, 3*wf0);
  auto mb = eve::welford_average(wf1, wf0);
  auto mab= eve::average(wf0, 2*wf0, 3*wf0, wf1, wf0);
  auto wmab = eve::welford_average(ma, mb);
  std::cout << "ma     " << t_t(ma) << std::endl;
  std::cout << "mb     " << t_t(mb) << std::endl;
  std::cout << "mab    " << mab << std::endl;
  std::cout << "wmab   " << t_t(wmab) << std::endl;

}
