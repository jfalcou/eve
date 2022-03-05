#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <vector>
#include <ranges>
#include <numeric>
#include <eve/algo/iota.hpp>
#include <eve/views/iota.hpp>

// template < typename R, floating_scalar_value T> linspace(R& r, T a, T b)
// {
//   auto n = T(r.size());
//   T invnm1 = 1.0f/(n-1.0f);
//   T c = b-a;
//   eve::algo::fill(r, invnm1);
//   eve::algo::inclusive_scan_inplace(r, eve::plus);
//   auto f = [a, c](auto x){return a+c*x; };
//   eve::transform_inplace(r, f);

// }

int main()
{
  std::vector<float> r1(5) , r2(5); //, r3(5);
  eve::algo::fill(r1, 2.0f);
  eve::algo::fill(r2, 2.0f);

  eve::algo::inclusive_scan_inplace(r1, std::pair{eve::add, eve::zero}, 0.0f);
  eve::algo::inclusive_scan_inplace(r2, std::pair{eve::mul, 1.0f}, 1.0f);

  std::cout << " <- eve::algo::inclusive_scan_inplace(r1, std::pair{eve::add, eve::zero}, 0.0f);\n";
  std::cout << " <- eve::algo::inclusive_scan_inplace(r2, std::pair{eve::mul, 1.0f}, 1.0f);\n";
  auto print =  [](auto v){ for(auto i : v) {std::cout << i << ' ';};  std::cout << '\n';};
  std::cout << " -> r1                         = "; print(r1);
  std::cout << " -> r2                         = "; print(r2);
  return 0;
}
