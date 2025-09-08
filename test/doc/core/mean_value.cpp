// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>
#include <tts/tts.hpp>

int main()
{
  std::cout << "00 " << eve::mean_value(1.0, 2.0) << std::endl;
  auto wa0 = eve::detail::wf<double>(1.0, 1);
  std::cout << "01 " << eve::mean_value(wa0, 2.0) << std::endl;
  std::cout <<  "  001 " << eve::mean_value(1.0, wa0)<< std::endl;
  std::cout  << "02 "<< eve::mean_value(wa0, wa0)<< std::endl;

  auto ma = eve::mean_value(1.0, 2.0);
  auto mb = eve::mean_value(3.0, 4.0, 5.0);
  auto mab = eve::mean_value(ma, mb);
  std::cout << "03 "<< mab <<  std::endl;
  std::cout << "04 "<< eve::mean_value(1.0, 2.0, 3.0, 4.0, 5.0)<< std::endl;
  std::cout << "1 " << eve::detail::is_wf_v<decltype(ma)> << std::endl;
  std::cout << "2 " << eve::detail::is_wf_v<double> << std::endl;
  std::cout << "3 " << tts::typename_<eve::detail::internal_welford_t<decltype(ma)>> << std::endl;
  std::cout << "4 " << tts::typename_<eve::detail::internal_welford_t<double>> << std::endl;

 auto mbf = eve::mean_value(3.0f, 4.0f, 5.0f);
 auto mbd = eve::mean_value[eve::widen](3.0f, 4.0f, 5.0f);
 std::cout << "5 " << tts::typename_<decltype(mbf)> << std::endl;
 std::cout << "6 " << tts::typename_<decltype(mbd)> << std::endl;


}
