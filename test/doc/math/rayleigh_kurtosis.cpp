// revision 0
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  using wf_t = eve::wide<float>;
  using wd_t = eve::wide<double>;

  std::cout << std::setprecision(9);
  std::cout << "-> rayleigh_kurtosis(as<float>())          = " << eve::rayleigh_kurtosis(eve::as<float>())          << "\n";
  std::cout << "-> rayleigh_kurtosis(as<wf_t>())           = " << eve::rayleigh_kurtosis(eve::as<wf_t>())           << "\n";
  std::cout << "-> rayleigh_kurtosis[lower](as<wf_t>())    = " << eve::rayleigh_kurtosis[eve::lower](eve::as<wf_t>()) << "\n";
  std::cout << "-> rayleigh_kurtosis[upper](as<wf_t>())    = " << eve::rayleigh_kurtosis[eve::upper](eve::as<wf_t>()) << "\n";

  std::cout << std::setprecision(17);
  std::cout << "-> rayleigh_kurtosis(as<double>())         = " << eve::rayleigh_kurtosis(eve::as<double>())         << "\n";
  std::cout << "-> rayleigh_kurtosis(as<wd_t>())           = " << eve::rayleigh_kurtosis(eve::as<wd_t>())           << "\n";
  std::cout << "-> rayleigh_kurtosis[lower](as<wd_t>())    = " << eve::rayleigh_kurtosis[eve::lower](eve::as<wd_t>()) << "\n";
  std::cout << "-> rayleigh_kurtosis[upper](as<wd_t>())    = " << eve::rayleigh_kurtosis[eve::upper](eve::as<wd_t>()) << "\n";
}
