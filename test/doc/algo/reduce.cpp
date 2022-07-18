#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <numeric>
#include <iostream>
#include <vector>

void print(auto r) {
  for (auto x : r) {
    std::cout << x << " ";
  }
  std::cout << '\n';
}

int main()
{
  std::vector<double>  v = {1.2,2.3,3.4,4.5,5.6,6.7};

  std::cout << " -> v                                                        = ";
  print(v);

  std::cout << " -> eve::algo::reduce(v, 0.)                                 = "
            << eve::algo::reduce(v, 0.) << "\n";

  std::cout << " -> eve::algo::reduce(v, std::pair{eve::mul, 1.}, 1.)        = "
            << eve::algo::reduce(v, std::pair{eve::mul, 1.}, 1.) << "\n";

  std::cout << " -> std::reduce(v.begin(), v.end(), 1., std::multiplies<>{}) = "
            << std::reduce(v.begin(), v.end(), 1., std::multiplies<>{}) << "\n";

  return 0;
}
