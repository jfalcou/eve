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
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N, typename I>
  EVE_FORCEINLINE auto
  shl_(EVE_SUPPORTS(vmx_), wide<T, N, ppc_> const &v0, wide<I, N, ppc_> const &v1) noexcept
  requires(wide<T, N, ppc_>, Integral<I>)
  {
    using t_t = wide<T, N, ppc_>;
    EVE_ASSERT( detail::assert_good_shift<t_t>(v1)
              , "eve::shl - At least one of " << v1 << "elements is out of the range [0, "
                                                    << sizeof(T)*8 << "[."
              );

    using i_t = wide<as_integer_t<T,unsigned>,N>;

    if constexpr( std::is_arithmetic_v<T> )
    {
      if constexpr( std::is_integral_v<T> )
        return vec_sl(v0.storage(), bitwise_cast<i_t>(v1).storage());

      if constexpr( std::is_floating_point_v<T> )
      {
        using f_t = wide<as_integer_t<T>,N>;
        auto b = bitwise_cast<f_t>(v0).storage();
        auto i = bitwise_cast<i_t>(v1).storage();
        return bitwise_cast<wide<T, N, ppc_>>(vec_sl( b, i));
      }
    }
    else
    {
      static_assert ( std::is_arithmetic_v<T>,
                     "eve::shl - No support for logical values"
                    );
    }
  }

  template<typename T, typename N, typename I>
  EVE_FORCEINLINE auto
  shl_(EVE_SUPPORTS(vmx_), wide<T, N, ppc_> const &v0, I v1) noexcept
  requires(wide<T, N, ppc_>, Integral<I>)
  {
    using i_t = wide<as_integer_t<T,unsigned>,N>;
    return eve::shl(v0, i_t(v1));
  }
}

#endif
