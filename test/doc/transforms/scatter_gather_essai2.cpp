#include <eve/module/core.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/algo.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <vector>
#include <eve/module/transforms/utils.hpp>
#include <chrono>
#include <tts/tts.hpp>

EVE_FORCEINLINE constexpr void
df_16(auto f) noexcept // 16 elements
{
  using e_t = eve::underlying_type_t<std::remove_reference_t<decltype(f[0])>>;
  using c_t =  eve::complex<e_t>;
  const auto  invsqrt2 = eve::invsqrt_2(eve::as<e_t>());
  const auto  sqrt2    = eve::sqrt_2(eve::as<e_t>());
  using eve::detail::sd;
  e_t f0, f1, f2, f3;
  sd(f[0], f[8], f0, f1);
  sd(f[4], f[12], f2, f3);
  sd(f0, f2, f[0], f[4]);
  sd(f1, f3, f[8], f[12]);

  sd(f[2], f[10], f0, f1);
  sd(f[6], f[14], f2, f3);
  sd(f0, f2, f[2], f[6]);
  sd(f1, f3, f[10], f[14]);

  sd(f[1], f[9], f0, f1);
  sd(f[5], f[13], f2, f3);
  sd(f0, f2, f[1], f[5]);
  sd(f1, f3, f[9], f[13]);

  sd(f[3], f[11], f0, f1);
  sd(f[7], f[15], f2, f3);
  sd(f0, f2, f[3], f[7]);
  sd(f1, f3, f[11], f[15]);

  sd(f[0], f[2], f0, f1);
  sd(f[1], f[3], f2, f3);
  sd(f0, f2, f[0], f[1]);
  sd(f1, f3, f[2], f[3]);

  sd(f[4], f[6], f0, f1);
  f3 = sqrt2 * f[7];
  f2 = sqrt2 * f[5];
  sd(f0, f2, f[4], f[5]);
  sd(f1, f3, f[6], f[7]);

  e_t a, b, g0, g1, g2, g3;
  sd(f[10], f[14], a, b);
  a *= invsqrt2;
  b *= invsqrt2;
  sd(f[8], a, f0, f1);
  sd(f[12], b, g0, g1);
  sd(f[11], f[15], a, b);
  a *= invsqrt2;
  b *= invsqrt2;
  sd(f[9], a, f2, f3);
  sd(f[13], b, g2, g3);
  const e_t c1 = eve::cos_pio_8(eve::as<e_t>());
  const e_t s1 = eve::sin_pio_8(eve::as<e_t>());
  kumi::tie(b, a) = c_t(s1, c1)*c_t(f2, g3);
  sd(f0, a, f[8], f[9]);
  sd(g1, b, f[14], f[15]);
  kumi::tie(b, a) = c_t(c1, s1)*c_t(g2, f3);
  sd(g0, a, f[12], f[13]);
  sd(f1, b, f[10], f[11]);
}


EVE_FORCEINLINE constexpr void
df_16(auto& ff0, auto & ff1,  auto & ff2,  auto & ff3
     , auto& ff4, auto & ff5,  auto & ff6,  auto & ff7
     , auto& ff8, auto & ff9,  auto & ff10,  auto & ff11
     , auto & ff12,  auto & ff13, auto& ff14, auto & ff15 ) noexcept // 16 elements
{
  using t_t = std::remove_reference_t<decltype(ff0)>;
  using e_t = eve::underlying_type_t<std::remove_reference_t<decltype(ff0)>>;
  using c_t =  eve::complex<e_t>;
  using cw_t = eve::as_complex<t_t>;
  std::cout << tts::typename_<c_t> << std::endl;
  std::cout << tts::typename_<cw_t> << std::endl;

  using eve::detail::sd;
  const auto  invsqrt2 = eve::invsqrt_2(eve::as<e_t>());
  const auto  sqrt2    = eve::sqrt_2(eve::as<e_t>());
  t_t f0, f1, f2, f3;
  sd(ff0, ff8, f0, f1);
  sd(ff4, ff12, f2, f3);
  sd(f0, f2, ff0, ff4);
  sd(f1, f3, ff8, ff12);

  sd(ff2, ff10, f0, f1);
  sd(ff6, ff14, f2, f3);
  sd(f0, f2, ff2, ff6);
  sd(f1, f3, ff10, ff14);

  sd(ff1, ff9, f0, f1);
  sd(ff5, ff13, f2, f3);
  sd(f0, f2, ff1, ff5);
  sd(f1, f3, ff9, ff13);

  sd(ff3, ff11, f0, f1);
  sd(ff7, ff15, f2, f3);
  sd(f0, f2, ff3, ff7);
  sd(f1, f3, ff11, ff15);

  sd(ff0, ff2, f0, f1);
  sd(ff1, ff3, f2, f3);
  sd(f0, f2, ff0, ff1);
  sd(f1, f3, ff2, ff3);

  sd(ff4, ff6, f0, f1);
  f3 = sqrt2 * ff7;
  f2 = sqrt2 * ff5;
  sd(f0, f2, ff4, ff5);
  sd(f1, f3, ff6, ff7);

  t_t a, b, g0, g1, g2, g3;
  sd(ff10, ff14, a, b);
  a *= invsqrt2;
  b *= invsqrt2;
  sd(ff8, a, f0, f1);
  sd(ff12, b, g0, g1);
  sd(ff11, ff15, a, b);
  a *= invsqrt2;
  b *= invsqrt2;
  sd(ff9, a, f2, f3);
  sd(ff13, b, g2, g3);
   const e_t c1 = eve::cos_pio_8(eve::as<e_t>());
   const e_t s1 = eve::sin_pio_8(eve::as<e_t>());
//    auto s1c1 = c_t(s1, c1);
//    std::cout << s1c1 << std::endl;
//    auto f2g3 = eve::as_complex_t<t_t>(f2, g3);


//    std::cout << f2g3 << std::endl;
//    std::cout << f2   << std::endl;
//    std::cout << g3   << std::endl;
   //  exit(1);
   kumi::tie(b, a) = kumi::to_tuple(c_t(s1, c1)*eve::as_complex_t<t_t>(f2, g3));
  sd(f0, a, ff8, ff9);
  sd(g1, b, ff14, ff15);
  kumi::tie(b, a) = kumi::to_tuple(c_t(c1, s1)*eve::as_complex_t<t_t>(g2, f3));
  sd(g0, a, ff12, ff13);
  sd(f1, b, ff10, ff11);
}


int main()
{
  using e_t = float;
  using i_t = eve::as_integer_t<e_t>;
  i_t n = 1 << 7;
  std::vector<e_t> v(n);

  {
    for(i_t i=0; i <n ; ++i) v[i] = i;

    auto f  = &v[0];
    auto fn = f+n;
    using we_t = eve::wide<e_t>;
    using wi_t = eve::as_integer_t<we_t>;
    auto card = eve::expected_cardinal_v<e_t>;
    wi_t idx([](auto i,  auto){return i; });
    auto shft = idx*16;
    std::cout << "card " << card << std::endl;
    auto tic =  std::chrono::steady_clock::now();
//    i_t i = 0;
    for(auto fi = f; fi < fn ; fi += card*16)
    {
//      std::cout << i++ << std::endl;
      auto ff0 = eve::gather(fi+0, shft);
      auto ff1 = eve::gather(fi+1, shft);
      auto ff2 = eve::gather(fi+2, shft);
      auto ff3 = eve::gather(fi+3, shft);
      auto ff4 = eve::gather(fi+4, shft);
      auto ff5 = eve::gather(fi+5, shft);
      auto ff6 = eve::gather(fi+6, shft);
      auto ff7 = eve::gather(fi+7, shft);
      auto ff8 = eve::gather(fi+8, shft);
      auto ff9 = eve::gather(fi+9, shft);
      auto ff10 = eve::gather(fi+10, shft);
      auto ff11 = eve::gather(fi+11, shft);
      auto ff12 = eve::gather(fi+12, shft);
      auto ff13 = eve::gather(fi+13, shft);
      auto ff14 = eve::gather(fi+14, shft);
      auto ff15 = eve::gather(fi+15, shft);
//       std::cout << ff0 << std::endl;
//       std::cout << ff1 << std::endl;
//       std::cout << ff2 << std::endl;
//       std::cout << ff3 << std::endl;
     df_16(ff0, ff1, ff2,  ff3, ff4, ff5, ff6,  ff7
         , ff8, ff9, ff10, ff11, ff12, ff13, ff14,  ff15 );
      eve::scatter(fi+0, shft, ff0);
      eve::scatter(fi+1, shft, ff1);
      eve::scatter(fi+2, shft, ff2);
      eve::scatter(fi+3, shft, ff3);
      eve::scatter(fi+4, shft, ff4);
      eve::scatter(fi+5, shft, ff5);
      eve::scatter(fi+6, shft, ff6);
      eve::scatter(fi+7, shft, ff7);
      eve::scatter(fi+8, shft, ff8);
      eve::scatter(fi+9, shft, ff9);
      eve::scatter(fi+10, shft, ff10);
      eve::scatter(fi+11, shft, ff11);
      eve::scatter(fi+12, shft, ff12);
      eve::scatter(fi+13, shft, ff13);
      eve::scatter(fi+14, shft, ff14);
      eve::scatter(fi+15, shft, ff15);
    }
    auto toc =  std::chrono::steady_clock::now()-tic;
    std::cout << "simd " << std::chrono::duration<double>(toc).count()*1000 << std::endl;

    for(i_t i=0; i <n ; ++i) std::cout << v[i] << " ";
    std::cout << std::endl;
  }
  {
    for(i_t i=0; i <n ; ++i) v[i] = i;

    auto f  = &v[0];
    auto fn = f+n;
    auto tic =  std::chrono::steady_clock::now();
//    i_t i = 0;
    for(auto *fi = f; fi < fn ; fi += 16)
    {
//       std::cout << i++ << std::endl;
      df_16(fi);
    }
    auto toc =  std::chrono::steady_clock::now()-tic;
    std::cout << "scal " << std::chrono::duration<double>(toc).count()*1000 << std::endl;
    for(i_t i=0; i <n ; ++i) std::cout << v[i] << " ";
    std::cout << std::endl;
  }
  return 0;
}
