#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -32768.0f};

  auto pf2 = eve::combine(pf,pf);
  std::cout << "pf                  ---> "  << pf << "\n";
  std::cout << "eve::combine(pf,pf) ---> "  << pf2 << "\n";
}
