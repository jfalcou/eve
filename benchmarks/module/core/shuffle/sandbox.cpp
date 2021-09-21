//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/wide.hpp>

namespace eve
{
  //  inline constexpr auto zip_        = shuffler([](int i, int c ) { auto s = c/2; return i/s +
  //  (i%s)*c; });

  // template<int N, typename P>
  // inline auto extent_pattern(shuffler_t<P> const& p)
  // {
  //   return shuffler_t([p](int i, int c) { return i<N ? p(i,c) : i ;});
  // }

  // template<typename P>
  // inline auto remove_zeros(shuffler_t<P> const& p)
  // {
  //   return shuffler_t([p](int i, int c) { auto j = p(i,c); return j == na_ ? i : j;});
  // }

  // template<int N, typename Pattern>
  // constexpr bool is_all_lhs(shuffler_t<Pattern> const& p) noexcept
  // {
  //   for(std::size_t i=0;i<N;++i)
  //     if(p(i,N) >= N)
  //       return false;

  //   return true;
  // }

  // template<int N, typename Pattern>
  // constexpr bool is_all_rhs(shuffler_t<Pattern> const& p) noexcept
  // {
  //   for(std::size_t i=0;i<N;++i)
  //     if(p(i,N) < N)
  //       return false;

  //   return true;
  // }

  // template<int N, typename Pattern>
  // constexpr bool is_mixed(shuffler_t<Pattern> const& p) noexcept
  // {
  //   return !is_all_rhs<N>(p) && !is_all_lhs<N>(p);
  // }
}

TTS_CASE("shuffle sandbox")
{
  using eve::logical;
  using eve::wide;
  using EVE_TYPE = float;
  using T    = eve::fixed<4>;

  wide<EVE_TYPE, T> arg([](auto i, auto) { return 10 * (1 + i); });
  std::cout << "arg: " << arg << "\n";

  std::cout << arg[ eve::identity ] << "\n";
  std::cout << arg[ eve::pattern<-1, -1, 0, 1> ] << "\n";
  std::cout << arg[ eve::pattern<0, 1, -1, -1> ] << "\n";
  std::cout << arg[ eve::pattern<-1, -1, 2, 3> ] << "\n";
  std::cout << arg[ eve::pattern<2, 3, -1, -1> ] << "\n";
  std::cout << arg[ eve::pattern<-1, -1, -1, -1> ] << "\n";
  std::cout << arg[ eve::pattern<3, 0, 1, 2> ] << "\n";
  std::cout << arg[ eve::pattern<0, 1> ] << "\n";
  std::cout << arg[ eve::pattern<2, 3> ] << "\n";
  std::cout << arg[ eve::pattern<-1, -1> ] << "\n";
  std::cout << arg[ eve::pattern<3, 0> ] << "\n";
  std::cout << arg[ eve::broadcast<1> ] << "\n";
  std::cout << arg[ eve::reverse ] << "\n";
  std::cout << arg[ eve::pattern<0, 0> ] << "\n";
  std::cout << arg[ eve::pattern<0, 1, 2, 3, 0, 1, 2, 3> ] << "\n\n";

  logical<wide<EVE_TYPE, T>> larg([](auto i, auto) { return 10 * (1 + i) % 3; });
  std::cout << "\nlarg: " << larg << "\n";
  std::cout << larg[ eve::identity ] << "\n";
  std::cout << larg[ eve::pattern<-1, -1, 0, 1> ] << "\n";
  std::cout << larg[ eve::pattern<0, 1, -1, -1> ] << "\n";
  std::cout << larg[ eve::pattern<-1, -1, 2, 3> ] << "\n";
  std::cout << larg[ eve::pattern<2, 3, -1, -1> ] << "\n";
  std::cout << larg[ eve::pattern<-1, -1, -1, -1> ] << "\n";
  std::cout << larg[ eve::pattern<3, 0, 1, 2> ] << "\n";
  std::cout << larg[ eve::pattern<0, 1> ] << "\n";
  std::cout << larg[ eve::pattern<2, 3> ] << "\n";
  std::cout << larg[ eve::pattern<-1, -1> ] << "\n";
  std::cout << larg[ eve::pattern<3, 0> ] << "\n";
  std::cout << larg[ eve::broadcast<2> ] << "\n";
  std::cout << larg[ eve::reverse ] << "\n";
  std::cout << larg[ eve::pattern<0, 0> ] << "\n";
  std::cout << larg[ eve::pattern<0, 0, 1, 1, 2, 2, 3, 3> ] << "\n\n";
}
