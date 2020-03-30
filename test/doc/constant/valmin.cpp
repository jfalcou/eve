#include <eve/constant/valmin.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  std::cout << "Valmin<int>()    = " << eve::Valmin(eve::as<int>()) << "\n";
  std::cout << "Valmin<double>()   = " << eve::Valmin(eve::as<double>()) << "\n";

  using wi4 = eve::wide<int,eve::fixed<4>>;
  using wd2 = eve::wide<double,eve::fixed<2>>;

  std::cout << "Valmin<wide<int,fixed<4>>>()   = " << eve::Valmin(eve::as<wi4>()) << "\n";
  std::cout << "Valmin<wide<double,fixed<2>>>()  = " << eve::Valmin(eve::as<wd2>()) << "\n";
}
