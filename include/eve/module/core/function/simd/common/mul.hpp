//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MUL_HPP_INCLUDED
#  define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MUL_HPP_INCLUDED

#  include <eve/detail/overload.hpp>
#  include <eve/detail/skeleton.hpp>
#  include <eve/detail/is_native.hpp>
#  include <eve/detail/meta.hpp>
#  include <eve/detail/abi.hpp>
#  include <eve/concept/vectorized.hpp>
#  include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto mul_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires(
      std::conditional_t<is_vectorized_v<T>, T, U>,
      detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>)
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;

    if constexpr(is_emulated_v<t_abi> || is_emulated_v<u_abi>)
    { return map(eve::mul, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b)); }
    else if constexpr(is_aggregated_v<t_abi> || is_aggregated_v<u_abi>)
    {
      return aggregate(eve::mul, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b));
    }
    else if constexpr(is_vectorized_v<T> && is_vectorized_v<U>)
    {
      static_assert(std::is_same_v<T, U>, "[eve::mul] - no support for current simd api");
      return {};
    }
    else // if constexpr( is_vectorized_v<T> || is_vectorized_v<U> )
    {
      return eve::mul(abi_cast<U>(a), abi_cast<T>(b));
    }
  }
}

namespace eve
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto operator*(T const &v0, U const &v1) noexcept -> decltype(eve::mul(v0, v1))
  {
    return eve::mul(v0, v1);
  }
}

#endif

#include "if_mul.hpp"
