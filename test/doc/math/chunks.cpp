// revision 1
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  kumi::tuple a{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
  using wd = eve::wide<double,  eve::fixed<4>>;

  std::cout << a << "\n";
  auto b =  kumi::chunks<4>(a);
  std::cout << b << "\n";
//   kumi::for_each([&](auto tile)
//   {
//     get<0>(tile)++;
//   },b);
  std::cout << b  << "\n";

  kumi::tuple<wd, wd> wt;
  auto zipped = kumi::zip(b, wt);
  kumi::for_each( [](auto& m) { auto [s, t] = m; t = kumi::apply([](wd(s);*/ }, zipped);
  std::cout << wt << std::endl;

}
