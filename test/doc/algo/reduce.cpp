#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <tts/tts.hpp>
#include <numeric>
#include <iostream>
#include <vector>

int main()
{
  std::vector<double>  v = {1.2,2.3,3.4,4.5,5.6,6.7};

  std::cout << " -> v                                                        = "
            << tts::as_string(v)
            << "\n";

  std::cout << " -> eve::algo::reduce(v, 0.)                                 = "
            << eve::algo::reduce(v, 0.) << "\n";

  std::cout << " -> eve::algo::reduce(v, std::pair{eve::mul, 1.}, 1.)        = "
            << eve::algo::reduce(v, std::pair{eve::mul, 1.}, 1.) << "\n";

  std::cout << " -> std::reduce(v.begin(), v.end(), 1., std::multiplies<>{}) = "
            << std::reduce(v.begin(), v.end(), 1., std::multiplies<>{}) << "\n";

  return 0;
}
