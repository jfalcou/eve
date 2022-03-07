#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "detail/print.hpp"
#include <iomanip>
#include <typeinfo>


struct load_op
{
  auto operator()(auto x) const { return eve::convert(x, eve::as<double>{})*2.3; }
};

struct store_op
{
  auto operator()(auto x, eve::as<int>) const { return eve::zero(eve::as(x)); } //eve::sqrt(eve::convert(x, eve::as<float>{})); }
};

int main()
{
  std::vector<int> v(10), v1(10);
  eve::algo::iota(v, 1);
  eve::algo::iota(v1, -4);
  auto vm  = eve::views::map(v1, load_op{});
  auto v1m = eve::views::map_convert(v1, load_op{}, store_op{});

  std::cout << std::setprecision(6) << std::endl;
  std::cout << " -> v                                    = "; eve::detail::print(v);
  std::cout << " -> vm                                   = "; eve::detail::print(vm);
  std::cout << " -> v1                                   = "; eve::detail::print(v1);
  std::cout << " -> v1m                                  = "; eve::detail::print(v1m);
  auto z = eve::read(v1m.begin());
  std::cout << typeid(z).name()  << std::endl;
  return 0;
}
