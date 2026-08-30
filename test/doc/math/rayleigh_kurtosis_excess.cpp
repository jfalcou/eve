// revision 0
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  using wf_t = eve::wide<float>;
  using wd_t = eve::wide<double>;

  std::cout << std::setprecision(9);
  std::cout << "-> rayleigh_kurtosis_excess(as<float>())          = " << eve::rayleigh_kurtosis_excess(eve::as<float>())          << "\n";
  std::cout << "-> rayleigh_kurtosis_excess(as<wf_t>())           = " << eve::rayleigh_kurtosis_excess(eve::as<wf_t>())           << "\n";
  std::cout << "-> rayleigh_kurtosis_excess[lower](as<wf_t>())    = " << eve::rayleigh_kurtosis_excess[eve::lower](eve::as<wf_t>()) << "\n";
  std::cout << "-> rayleigh_kurtosis_excess[upper](as<wf_t>())    = " << eve::rayleigh_kurtosis_excess[eve::upper](eve::as<wf_t>()) << "\n";

  std::cout << std::setprecision(17);
  std::cout << "-> rayleigh_kurtosis_excess(as<double>())         = " << eve::rayleigh_kurtosis_excess(eve::as<double>())         << "\n";
  std::cout << "-> rayleigh_kurtosis_excess(as<wd_t>())           = " << eve::rayleigh_kurtosis_excess(eve::as<wd_t>())           << "\n";
  std::cout << "-> rayleigh_kurtosis_excess[lower](as<wd_t>())    = " << eve::rayleigh_kurtosis_excess[eve::lower](eve::as<wd_t>()) << "\n";
  std::cout << "-> rayleigh_kurtosis_excess[upper](as<wd_t>())    = " << eve::rayleigh_kurtosis_excess[eve::upper](eve::as<wd_t>()) << "\n";
}
