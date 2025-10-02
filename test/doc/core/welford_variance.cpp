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

  std::cout << "<- wf0                                    = " << wf0 << "\n";
  std::cout << "<- wf1                                    = " << wf1 << "\n";

  auto ma = eve::welford_variance(wf0, 2*wf0, 3*wf0);
  auto mb = eve::welford_variance(wf1, wf0);
  auto mab= eve::welford_variance(wf0, 2*wf0, 3*wf0, wf1, wf0);
  auto wmab = eve::welford_variance(ma, mb);
  std::cout << "ma = welford_variance(wf0, 2*wf0, 3*wf0)   = " << t_t(ma) << std::endl;
  std::cout << "mb = welford_variance(wf1, wf0)            = " << t_t(mb) << std::endl;
  std::cout << "eve::variance(wf0, 2*wf0, 3*wf0, wf1, wf0) = " << mab << std::endl;
  std::cout << "eve::welford_variance(ma, mb)              = " << t_t(wmab) << std::endl;
  auto vw = eve::welford_variance(4.0f, 3.0f, 2.0f, 1.0f);
  std::cout << "avg " << vw.average<< std::endl;
  std::cout << "var " << vw.variance << std::endl;
  std::cout << "s2  " << vw.m2   << std::endl;
  std::cout << eve::welford_variance[eve::unbiased](4.0f, 3.0f, 2.0f, 1.0f)<< std::endl;
  std::cout << eve::welford_variance(
    eve::welford_variance(1.0f, 2.0f),
    eve::welford_variance(3.0f, 4.0f))<< std::endl;
  std::cout << eve::welford_variance[eve::unbiased](
    eve::welford_variance(1.0f, 2.0f),
    eve::welford_variance(3.0f, 4.0f))<< std::endl;
}
