#include <eve/constant/constant.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

int main()
{
  std::cout << "---- simd" << std::setprecision(15) << std::endl
            << "-> Constant<wide_ft, 0X3F1DE9E7U>()           " << eve::Constant<wide_ft, 0X3F1DE9E7U>()<< std::endl
            << "-> Constant<wide_dt, 0x3FE3BD3CC9BE45DEULL>() " << eve::Constant<wide_dt, 0x3FE3BD3CC9BE45DEULL>()<< std::endl;

  std::cout << "---- scalar" << std::endl
            << "-> Constant<float, 0X3F1DE9E7U>()             " << eve::Constant<float, 0X3F1DE9E7U>()<< std::endl
            << "-> Constant<double, 0x3FE3BD3CC9BE45DEULL>()  " << eve::Constant<double, 0x3FE3BD3CC9BE45DEULL>()<< std::endl;

  return 0;
}
