#include <eve/module/core.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/algo.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <vector>
#include <eve/module/transforms/utils.hpp>
#include <chrono>

  constexpr void
  df_4(auto f) noexcept // 4 elements
  {
    using e_t = eve::underlying_type_t<std::remove_reference_t<decltype(f[0])>>;
    e_t f0, f1, f2, f3;
    eve::detail::sd(f[0], f[2], f0, f1);
    eve::detail::sd(f[1], f[3], f2, f3);
    eve::detail::sd(f0, f2, f[0], f[1]);
    eve::detail::sd(f1, f3, f[2], f[3]);
  }


  constexpr void
  df_4(auto& ff0, auto & ff1,  auto & ff2,  auto & ff3) noexcept // 4 elements
  {
    using t_t = std::remove_reference_t<decltype(ff0)>;
    t_t f0, f1, f2, f3;
    eve::detail::sd(ff0, ff2, f0, f1);
    eve::detail::sd(ff1, ff3, f2, f3);
    eve::detail::sd(f0, f2, ff0, ff1);
    eve::detail::sd(f1, f3, ff2, ff3);
  }

int main()
{
  using e_t = float;
  using i_t = eve::as_integer_t<e_t>;
  i_t n = 1 << 21;
  std::vector<e_t> v(n);

  {
    for(i_t i=0; i <n ; ++i) v[i] = i;

    auto f  = &v[0];
    auto fn = f+n;
    using we_t = eve::wide<e_t>;
    using wi_t = eve::as_integer_t<we_t>;
    auto card = eve::expected_cardinal_v<e_t>;
    wi_t idx([](auto i,  auto){return i; });
    auto shft = idx*4;
    std::cout << "card " << card << std::endl;
    auto tic =  std::chrono::steady_clock::now();
    for(auto fi = f; fi < fn ; fi += card*4)
    {
      auto ff0 = eve::gather(fi+0, shft);
      auto ff1 = eve::gather(fi+1, shft);
      auto ff2 = eve::gather(fi+2, shft);
      auto ff3 = eve::gather(fi+3, shft);
//       std::cout << ff0 << std::endl;
//       std::cout << ff1 << std::endl;
//       std::cout << ff2 << std::endl;
//       std::cout << ff3 << std::endl;
     df_4(ff0, ff1, ff2,  ff3);
      eve::scatter(fi+0, shft, ff0);
      eve::scatter(fi+1, shft, ff1);
      eve::scatter(fi+2, shft, ff2);
      eve::scatter(fi+3, shft, ff3);
    }
    auto toc =  std::chrono::steady_clock::now()-tic;
    std::cout << "simd " << std::chrono::duration<double>(toc).count()*1000 << std::endl;

//    for(i_t i=0; i <n ; ++i) std::cout << v[i] << " ";
//    std::cout << std::endl;
  }
  {
    for(i_t i=0; i <n ; ++i) v[i] = i;

    auto f  = &v[0];
    auto fn = f+n;
    auto tic =  std::chrono::steady_clock::now();
    for(auto *fi = f; fi < fn ; fi += 4)
    {
      df_4(fi);
    }
    auto toc =  std::chrono::steady_clock::now()-tic;
    std::cout << "scal " << std::chrono::duration<double>(toc).count()*1000 << std::endl;
//    for(i_t i=0; i <n ; ++i) std::cout << v[i] << " ";
//    std::cout << std::endl;
  }
  return 0;
}
