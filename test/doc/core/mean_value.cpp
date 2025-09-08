// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>
#include <tts/tts.hpp>

int main()
{
  std::cout << eve::mean_value(1.0, 2.0) << std::endl;
  auto wa0 = eve::detail::wf<double>(1.0, 1);
  std::cout << eve::mean_value(wa0, 2.0) << std::endl;
//   std::cout << eve::mean_value(1.0, wa0)<< std::endl;
  std::cout << eve::mean_value(wa0, wa0)<< std::endl;

  auto ma = eve::mean_value(1.0, 2.0);
  auto mb = eve::mean_value(3.0, 4.0, 5.0);
  auto mab = eve::mean_value(ma, mb);
  std::cout << mab <<  std::endl;
  std::cout << eve::detail::is_wf_v<decltype(ma)> << std::endl;
  std::cout << eve::detail::is_wf_v<double> << std::endl;
  std::cout << tts::typename_<eve::detail::internal_welford_t<decltype(ma)>> << std::endl;
  std::cout << tts::typename_<eve::detail::internal_welford_t<double>> << std::endl;
}
