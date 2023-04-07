//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <vector>
#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <eve/module/complex.hpp>
#include <eve/concept/range.hpp>
#include <type_traits>
#include <eve/pattern.hpp>

// namespace eve::detail
// {

//   template<scalar_value T, integral_scalar_value N>
//   auto perm( std::vector<T> const & v,  std::vector<N> const & v) noexcept
//   {
//     std::vector g(v.size());
//     for(int i = 0,  i < v.size();  ++i) g[i] = f[ind[i]);
//     return g;
//   }
//     constexpr auto C = cardinal_v<T>;
//     if constexpr(C <=  2) return x;
//     else if constexpr(C == 4 )
//     {
//       return shuffle(x, pattern<0, 2, 1, 3>);
//     }
//     else if constexpr(C == 8 )
//     {
//       return shuffle(x,pattern<0, 4, 2, 6, 1, 5, 3, 7>);
//     }
//     else if constexpr(C == 16 )
//     {
//       return shuffle(x, pattern< 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15>);
//     }
//     else if constexpr(C == 32 )
//     {
//       return shuffle(x, pattern<0, 16, 8, 24, 4, 20, 12, 28, 2, 18, 10, 26, 6, 22, 14, 30 , 1, 17, 9, 25, 5, 21, 13, 29, 3, 19, 11, 27, 7, 23, 15, 31>);
//     }
//     else if constexpr(C == 64 )
//     {
//       return shuffle(x, pattern<0, 32, 16, 48, 8, 40, 24, 56, 4, 36, 20, 52, 11, 44, 28, 60, 2, 34, 18, 50, 10, 42, 26, 58, 6, 38, 22, 54, 14, 46, 30, 62, 1, 33, 17, 49, 9, 41, 25, 57, 5, 37, 21, 53, 13, 45, 29, 81, 3, 35, 19, 51, 11, 43, 27, 59, 7, 39, 23, 55, 15, 47, 31, 63>);
//     }
//   }

//   template<value T>
//   EVE_FORCEINLINE constexpr auto
//   revbin_(EVE_SUPPORTS(cpu_), T const & x) noexcept
//   //  requires (scalar_value<T1>)
//   {
//     constexpr auto C = cardinal_v<T>;
//     if constexpr(C <=  2) return x;
//     else if constexpr(C == 4 )
//     {
//       return shuffle(x, pattern<0, 2, 1, 3>);
//     }
//     else if constexpr(C == 8 )
//     {
//       return shuffle(x,pattern<0, 4, 2, 6, 1, 5, 3, 7>);
//     }
//     else if constexpr(C == 16 )
//     {
//       return shuffle(x, pattern< 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15>);
//     }
//     else if constexpr(C == 32 )
//     {
//       return shuffle(x, pattern<0, 16, 8, 24, 4, 20, 12, 28, 2, 18, 10, 26, 6, 22, 14, 30 , 1, 17, 9, 25, 5, 21, 13, 29, 3, 19, 11, 27, 7, 23, 15, 31>);
//     }
//     else if constexpr(C == 64 )
//     {
//       return shuffle(x, pattern<0, 32, 16, 48, 8, 40, 24, 56, 4, 36, 20, 52, 11, 44, 28, 60, 2, 34, 18, 50, 10, 42, 26, 58, 6, 38, 22, 54, 14, 46, 30, 62, 1, 33, 17, 49, 9, 41, 25, 57, 5, 37, 21, 53, 13, 45, 29, 81, 3, 35, 19, 51, 11, 43, 27, 59, 7, 39, 23, 55, 15, 47, 31, 63>);
//     }
//   }

//}
