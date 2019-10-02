//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_ALL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_ALL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(vmx_), logical<wide<T, N, ppc_>> const &v0) noexcept
  {
    auto m = v0.bits();

    if constexpr( N::value == 1)
    {
      return static_cast<bool>(m[0]);
    }
    else if constexpr( N::value == expected_cardinal<T,ppc_>::value )
    {
      return vec_all_eq( m.storage(), True(as(v0)).storage() );
    }
    else
    {
      using type = decltype(m);
      auto mm = apply<N::value>( [](auto... I) { return type{ (I<N::value)... }; });
      return vec_all_eq( (m & mm).storage(), mm.storage() );
    }
  }
}

#endif
