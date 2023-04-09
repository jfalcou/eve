//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"
#include "../complex/measures.hpp"
#include <eve/module/fft.hpp>

TTS_CASE_WITH("Check behavior of idx_swap",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(0, 8), tts::logicals(0, 3)))
  <typename T, typename M>(T const& , M const& /*mask*/)
{
  auto pr = [](auto name, auto v){
    std::cout << name << " = (";
    for(size_t i=0; i < v.size() ; ++i) std::cout << +v[i] << " ";
    std::cout << ")\n";
  };

//  std::cout << idx1    << std::endl;
//  std::cout << mask  << std::endl;
  int n = 128;
  std::vector<int32_t> vi(n); //, orig(n);
  for(int i=0; i < n ; ++i) vi[i] = i;
  pr("vi     ", vi);
  T idx1([](auto i,  auto ){return i ; });
  T idx2([](auto i,  auto c){return c-i-1; });
  std::cout << "idx1 " << +idx1    << std::endl;
  std::cout << "idx2 " << +idx2    << std::endl;
  eve::idx_swap(vi, idx1 <  idx2, idx1, idx2);
  pr("swapped", vi);
  eve::idx_swap(vi, idx1 <  idx2, idx1, idx2);
  pr("reswapped", vi);



  TTS_EQUAL(0, 0);
};
//TTS_CASE_TPL("Check revbin_permute", eve::test::simd::unsigned_integers)
// <typename T>(tts::type<T>)
// {
//   if constexpr(std::same_as<eve::element_type_t<T>, std::uint8_t> && eve::cardinal_v<T> == 1)
//   {
//     auto pr = [](auto name, auto v){
//       std::cout << name << " = (";
//       for(size_t i=0; i < v.size() ; ++i) std::cout << v[i] << " ";
//       std::cout << ")\n";
//     };

//     int n =  64;
//     std::vector<int32_t> vi(n), orig(n);

//     for(int n=2; n < 32; n <<= 1)
//     {
//       std::vector<int32_t> vi(n), orig(n);
//       for(int i=0; i < n ; ++i) vi[i] = i;
// //      pr("vi ", vi);
//       std::cout << " =============================== " << n<< std::endl;
//       vi = eve::revbin_permute(vi);
//       pr("vi  ", vi);
//       vi = eve::revbin_permute(vi);
// //      pr("rvi ", vi);
//       std::cout << " ------------------------------- " << std::endl;
//       for(int i = 0; i < n; i++) TTS_EQUAL(vi[i], i);
//     }
//   }
// };
