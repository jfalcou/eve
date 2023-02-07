#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <tts/tts.hpp>
#include <iostream>
#include <numeric>
#include <vector>

int main()
{
  std::vector<float>  v = {1.0f, 2.0f, 3.0f, 4.0f};

  std::cout << " -> v                                                                                                                        = "
            << tts::as_string(v)
            << "\n";

  std::cout << " -> eve::algo::transform_reduce(v, [](auto x) { return x + x }, 0.f)                                                         = "
            << eve::algo::transform_reduce(v, [](auto x) { return x + x; }, 0.) << "\n";

  std::cout << " -> std::transform_reduce(v.begin(), v.end(), std::plus<>{}, 0.f, [](auto x) { return x + x })                               = "
            << std::transform_reduce(v.begin(), v.end(), 0., std::plus<>{}, [](auto x) { return x + x; }) << "\n";

  std::cout << " -> eve::algo::reduce(eve::views::map(v, [](auto x) { return x + x }), 0.f)                                                  = "
            << eve::algo::reduce(eve::views::map(v, [](auto x) { return x + x; }), 0.f) << "\n";

  std::cout << " -> eve::algo::transform_reduce(v, [](auto x) { return x + x }, std::pair{eve::mul, eve::one}, 1.f)  = "
            << eve::algo::transform_reduce(v, [](auto x) { return x + x; }, std::pair{eve::mul, eve::one}, 1.f) << "\n";

  std::cout << " -> eve::algo::transform_reduce[eve::algo::fuse_operations](v, [](auto x, auto sum) { return eve::fma(x, 2.f, sum); }, 0.f)  = "
            << eve::algo::transform_reduce[eve::algo::fuse_operations](v, [](auto x, auto sum) { return eve::fma(x, .5f, sum); }, 0.f) << "\n";
}
