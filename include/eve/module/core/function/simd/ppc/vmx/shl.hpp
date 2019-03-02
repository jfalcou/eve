//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_VMX_SHL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_VMX_SHL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/forward.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename I>
  EVE_FORCEINLINE auto
  shl_(EVE_SUPPORTS(vmx_), wide<T, N, ppc_> const &v0, wide<I, N, ppc_> const &v1) noexcept
  requires(wide<T, N, ppc_>, Integral<I>, Integral<T>)
  {
    using t_t = wide<T, N, ppc_>;
    EVE_ASSERT( detail::assert_good_shift<t_t>(v1)
              , "[eve::shl ppc] - At least one of " << v1 << "elements is out of the range [0, "
                                                    << sizeof(T)*8 << "[."
              );

    using i_t = wide<as_integer_t<T,unsigned>,N>;

    return vec_sl(v0.storage(), bitwise_cast<i_t>(v1).storage());
  }

  template<typename T, typename N, typename I>
  EVE_FORCEINLINE auto
  shl_(EVE_SUPPORTS(vmx_), wide<T, N, ppc_> const &v0, I v1) noexcept
  requires(wide<T, N, ppc_>, Integral<I>, Integral<T>)
  {
    using i_t = wide<as_integer_t<T,unsigned>,N>;
    return eve::shl(v0, i_t(v1));
  }
}

#endif
