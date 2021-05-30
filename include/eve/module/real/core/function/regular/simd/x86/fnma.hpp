//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>
#include <eve/function/fma.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> fnma_(EVE_SUPPORTS(avx2_),
                                         wide<T, N> const &a,
                                         wide<T, N> const &b,
                                         wide<T, N> const &c) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    if constexpr ( std::is_same_v<T, double> )
    {
           if constexpr ( std::same_as<abi_t<T, N>, x86_512_>                  ) return _mm512_fnmadd_pd(a, b, c);
      else if constexpr ( std::same_as<abi_t<T, N>, x86_256_> && supports_fma4 ) return _mm256_fnmadd_pd(a, b, c);
      else if constexpr ( std::same_as<abi_t<T, N>, x86_128_> && supports_fma3 ) return _mm_fnmadd_pd   (a, b, c);
      else                                                                       return fnma_           (EVE_RETARGET(cpu_), a, b, c);
    }
    else
    {
           if constexpr ( std::same_as<abi_t<T, N>, x86_512_>                  ) return _mm512_fnmadd_ps(a, b, c);
      else if constexpr ( std::same_as<abi_t<T, N>, x86_256_> && supports_fma4 ) return _mm256_fnmadd_ps(a, b, c);
      else if constexpr ( std::same_as<abi_t<T, N>, x86_128_> && supports_fma3 ) return _mm_fnmadd_ps   (a, b, c);
      else                                                                       return fnma_           (EVE_RETARGET(cpu_), a, b, c);
    }
  }
}
