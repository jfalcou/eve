//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_SSE2_IS_LTZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_SSE2_IS_LTZ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <cstdlib>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // sse2
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  is_ltz_(EVE_SUPPORTS(sse2_), wide<std::int64_t, N, sse_> const &v0) noexcept
  {
    using i64type = wide<std::int64_t, N, sse_>; 
    using i32type = wide<std::int32_t, fixed<2*N::value>, sse_>;
    i32type that = _mm_shuffle_epi32( is_ltz(bitwise_cast<i32type>(v0))
                                    , _MM_SHUFFLE(3,3,1,1)
                                    );
    return  bitwise_cast<i64type>(that);
  }
}

#endif
