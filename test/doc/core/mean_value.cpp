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
//   eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
//   eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wf0                                  = " << wf0 << "\n";
//   std::cout << "<- wi0                      = " << wi0 << "\n";
//   std::cout << "<- wu0                      = " << wu0 << "\n";

  std::cout << "-> mean_value(wf0, 2*wf0, 3*wf0)           = " << eve::mean_value(wf0, 2*wf0, 3*wf0) << "\n";
  std::cout << "-> mean_value[welford](wf0, 2*wf0, 3*wf0)  = " << eve::mean_value[eve::welford](wf0, 2*wf0, 3*wf0).avg_ << "\n";
  std::cout << "-> mean_value[kahan](wf0, 2*wf0, 3*wf0)    = " << eve::mean_value[eve::kahan](wf0, 2*wf0, 3*wf0) << "\n";

  auto ma = eve::mean_value[eve::welford](wf0, 2*wf0, 3*wf0);
  auto mb = eve::mean_value[eve::welford](wf1, wf0);
  auto mab= eve::mean_value(wf0, 2*wf0, 3*wf0, wf1, wf0);
  auto wmab = eve::mean_value[eve::welford](ma, mb);
  std::cout << "ma     " << t_t(ma) << std::endl;
  std::cout << "mb     " << t_t(mb) << std::endl;
  std::cout << "mab    " << t_t(mab) << std::endl;
  std::cout << "wmab   " << t_t(wmab) << std::endl;

}
