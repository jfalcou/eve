#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<8>>;

int main()
{
  wide_ft pf = {1.2f,0.34f,0.056f,0.0078f};
  wide_it pi = {-1, 2,-3, 4,-5, 6,-7, 8};

  std::cout << pf << "\n"
            << eve::broadcast(pf, eve::index<3> ) << "\n";

  std::cout << "\n";

  std::cout << pi << "\n"
            << eve::broadcast(pi, eve::index<5> ) << "\n";
}
