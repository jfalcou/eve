// revision 0
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  using wf_t = eve::wide<float>;
  using wd_t = eve::wide<double>;

  std::cout << std::setprecision(9);
  std::cout << "-> rayleigh_skewness(as<float>())          = " << eve::rayleigh_skewness(eve::as<float>())          << "\n";
  std::cout << "-> rayleigh_skewness(as<wf_t>())           = " << eve::rayleigh_skewness(eve::as<wf_t>())           << "\n";
  std::cout << "-> rayleigh_skewness[lower](as<wf_t>())    = " << eve::rayleigh_skewness[eve::lower](eve::as<wf_t>()) << "\n";
  std::cout << "-> rayleigh_skewness[upper](as<wf_t>())    = " << eve::rayleigh_skewness[eve::upper](eve::as<wf_t>()) << "\n";

  std::cout << std::setprecision(17);
  std::cout << "-> rayleigh_skewness(as<double>())         = " << eve::rayleigh_skewness(eve::as<double>())         << "\n";
  std::cout << "-> rayleigh_skewness(as<wd_t>())           = " << eve::rayleigh_skewness(eve::as<wd_t>())           << "\n";
  std::cout << "-> rayleigh_skewness[lower](as<wd_t>())    = " << eve::rayleigh_skewness[eve::lower](eve::as<wd_t>()) << "\n";
  std::cout << "-> rayleigh_skewness[upper](as<wd_t>())    = " << eve::rayleigh_skewness[eve::upper](eve::as<wd_t>()) << "\n";
}
