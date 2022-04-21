#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "print.hpp"

int main()
{
  std::vector<double>  v = {1.2,2.3,3.4,4.5,5.6,6.7};

  std::cout << " -> v                                         = ";
  doc_utils::print(v);

  std::cout << " -> eve::algo::reduce(v, 0.)                  = "
            << eve::algo::reduce(v, 0.) << "\n";

  std::cout << " -> eve::algo::reduce(v, {eve::mul, 1.}, 1.)  = "
            << eve::algo::reduce(v, std::pair{eve::mul, 1.}, 1.) << "\n";

  return 0;
}
