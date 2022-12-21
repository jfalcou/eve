#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <tts/tts.hpp>
#include <iostream>
#include <numeric>
#include <vector>

int main()
{
  std::vector<float>  v = {1.0f, 2.0f, 3.0f, 4.0f};

  std::cout << " -> v                                                                                               = "
            << tts::as_string(v)
            << "\n";

  std::cout << " -> eve::algo::transform_reduce(v, [](auto x) { return x + x }, 0.)                                 = "
            << eve::algo::transform_reduce(v, [](auto x) { return x + x; }, 0.) << "\n";

  std::cout << " -> std::transform_reduce(v.begin(), v.end(), std::plus<>{}, 0., [](auto x) { return x + x })       = "
            << std::transform_reduce(v.begin(), v.end(), 0., std::plus<>{}, [](auto x) { return x + x; }) << "\n";

  std::cout << " -> eve::algo::reduce(eve::views::map(v, [](auto x) { return x + x }), 0.)                          = "
            << eve::algo::reduce(eve::views::map(v, [](auto x) { return x + x; }), 0.) << "\n";

  std::cout << " -> eve::algo::transform_reduce(v, [](auto x) { return x + x }, std::pair{eve::mul, eve::one}, 0.)  = "
            << eve::algo::transform_reduce(v, [](auto x) { return x + x; }, std::pair{eve::mul, eve::one}, 1.) << "\n";
}
