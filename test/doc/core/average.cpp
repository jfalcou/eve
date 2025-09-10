// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>
#include <tts/tts.hpp>

int main()
{
  std::cout << "00 " << eve::average(1.0, 2.0) << std::endl;
  auto wa0 = eve::detail::wf<double>(1.0, 1);
  std::cout << "01 " << eve::average(wa0, 2.0) << std::endl;
  std::cout <<  "  001 " << eve::average(1.0, wa0)<< std::endl;
  std::cout  << "02 "<< eve::average(wa0, wa0)<< std::endl;

  auto ma = eve::average(1.0, 2.0);
  auto mb = eve::average(3.0, 4.0, 5.0);
  auto mab = eve::average(ma, mb);
  std::cout << "03 "<< mab <<  std::endl;
  std::cout << "04 "<< eve::average(1.0, 2.0, 3.0, 4.0, 5.0)<< std::endl;
  std::cout << "1 " << eve::detail::is_wf_v<decltype(ma)> << std::endl;
  std::cout << "2 " << eve::detail::is_wf_v<double> << std::endl;
  std::cout << "3 " << tts::typename_<eve::detail::internal_welford_t<decltype(ma)>> << std::endl;
  std::cout << "4 " << tts::typename_<eve::detail::internal_welford_t<double>> << std::endl;
}
