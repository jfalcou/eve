//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_CLAMP_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_CLAMP_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/min.hpp>
#include <eve/function/max.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE auto
  clamp_(EVE_SUPPORTS(cpu_), T const &x, U const &lo, V const &hi) noexcept requires(
      std::conditional_t<!is_vectorized_v<T>, std::conditional_t<is_vectorized_v<U>, U, V>, T>,
      detail::Either<is_vectorized_v<T>, is_vectorized_v<U>, is_vectorized_v<V>>)
  {
    static constexpr auto vT = is_vectorized_v<T>;
    static constexpr auto vU = is_vectorized_v<U>;
    static constexpr auto vV = is_vectorized_v<V>;

    if constexpr(vT && !vU && !vV)
      return clamp(x, T{lo}, T{hi});
    else if constexpr(vT && vU && !vV)
      return clamp(x, lo, T{hi});
    else if constexpr(vT && !vU && vV)
      return clamp(x, T{lo}, hi);
    else if constexpr(!vT && vU && !vV)
      return clamp(U{x}, lo, U{hi});
    else if constexpr(!vT && vU && vV)
      return clamp(U{x}, lo, hi);
    else if constexpr(!vT && !vU && vV)
      return clamp(V{x}, V{lo}, hi);
    else
    {
      if constexpr(std::is_same_v<T, U> && std::is_same_v<T, V>)
      {
        using abi_t = typename T::abi_type;
        if constexpr(is_aggregated_v<abi_t>)
          return aggregate(eve::clamp, x, lo, hi);
        else if constexpr(is_emulated_v<abi_t>)
          return map(eve::clamp, x, lo, hi);
        else
        {
          EVE_ASSERT(assert_all(is_less_equal(lo, hi)), "lo is not less or equal to hi");
          return eve::min(eve::max(x, lo), hi);
        }
      }
      else
      {
        static_assert(std::is_same_v<T, U> && std::is_same_v<T, V>,
                      "[eve::fms] - Incompatible types.");
        return {};
      }
    }
  }
}

#endif
