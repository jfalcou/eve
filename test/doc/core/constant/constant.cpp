#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

int main()
{
  std::cout << "---- simd" << std::setprecision(15) << std::endl
            << "-> constant<wide_ft, 0X3F1DE9E7U>()           " << eve::constant<wide_ft, 0X3F1DE9E7U>()<< std::endl
            << "-> constant<wide_dt, 0x3FE3BD3CC9BE45DEULL>() " << eve::constant<wide_dt, 0x3FE3BD3CC9BE45DEULL>()<< std::endl;

  std::cout << "---- scalar" << std::endl
            << "-> constant<float, 0X3F1DE9E7U>()             " << eve::constant<float, 0X3F1DE9E7U>()<< std::endl
            << "-> constant<double, 0x3FE3BD3CC9BE45DEULL>()  " << eve::constant<double, 0x3FE3BD3CC9BE45DEULL>()<< std::endl;

  return 0;
}
