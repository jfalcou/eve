// revision 0
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  using wf_t = eve::wide<float>;
  using wd_t = eve::wide<double>;

  std::cout << std::setprecision(9);
  std::cout << "-> extreme_value_skewness(as<float>())          = " << eve::extreme_value_skewness(eve::as<float>())          << "\n";
  std::cout << "-> extreme_value_skewness(as<wf_t>())           = " << eve::extreme_value_skewness(eve::as<wf_t>())           << "\n";
  std::cout << "-> extreme_value_skewness[lower](as<wf_t>())    = " << eve::extreme_value_skewness[eve::lower](eve::as<wf_t>()) << "\n";
  std::cout << "-> extreme_value_skewness[upper](as<wf_t>())    = " << eve::extreme_value_skewness[eve::upper](eve::as<wf_t>()) << "\n";

  std::cout << std::setprecision(17);
  std::cout << "-> extreme_value_skewness(as<double>())         = " << eve::extreme_value_skewness(eve::as<double>())         << "\n";
  std::cout << "-> extreme_value_skewness(as<wd_t>())           = " << eve::extreme_value_skewness(eve::as<wd_t>())           << "\n";
  std::cout << "-> extreme_value_skewness[lower](as<wd_t>())    = " << eve::extreme_value_skewness[eve::lower](eve::as<wd_t>()) << "\n";
  std::cout << "-> extreme_value_skewness[upper](as<wd_t>())    = " << eve::extreme_value_skewness[eve::upper](eve::as<wd_t>()) << "\n";
}
