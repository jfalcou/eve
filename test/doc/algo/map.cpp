#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "detail/print.hpp"
#include <iomanip>
#include <typeinfo>


struct load_op
{
  auto operator()(auto x) const { return eve::sqrt(eve::convert(x, eve::as<double>{})); }
};


int main()
{
  std::vector<int> v(10);
  eve::algo::iota(v, 1);
  auto vm  = eve::views::map(v, load_op{});
  auto vf1  = eve::views::map(v, eve::sqrt);
  auto vf2  = eve::views::map(v, [](auto x){return eve::sqrt(eve::convert(x, eve::as<double>{})); });

  std::cout << std::setprecision(6) << std::endl;
  std::cout << " -> v                                    = "; eve::detail::print(v);
  std::cout << " -> vm                                   = "; eve::detail::print(vm);
  std::cout << " -> vf1                                  = "; eve::detail::print(vf1);
  std::cout << " -> vf2                                  = "; eve::detail::print(vf2);
  return 0;
}
