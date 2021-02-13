//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/convert.hpp>

namespace eve::detail
{
  template <typename T, typename N, typename C>
  EVE_FORCEINLINE bool any_arm_impl(logical<wide<T, N, arm_64_>> v0, C const & cond)
  {
    using l_t = logical<wide<T, N, arm_64_>>;
    if constexpr ( C::is_complete && !C::is_inverted ) return false;
    else
    {
      if constexpr ( !C::is_complete ) v0 = v0 && cond.mask(eve::as_<l_t>{});
      using wide_u32 = typename wide<T, N, arm_64_>::template rebind<std::uint32_t, eve::fixed<2>>;
      auto as_uint32 = eve::bit_cast(v0, eve::as_<eve::logical<wide_u32>>{});

      if constexpr( sizeof(T) * N() > 4u ) as_uint32 = vpmax_u32(as_uint32, as_uint32);
      return vget_lane_u32(as_uint32, 0);
    }
  }

  template <typename T, typename N, typename C>
  EVE_FORCEINLINE bool any_arm_impl(logical<wide<T, N, arm_128_>> v0, C const & cond)
  {
    using l_t = logical<wide<T, N, arm_128_>>;

         if constexpr ( C::is_complete && !C::is_inverted ) return false;
    else if constexpr ( sizeof( T ) >= 2 )
    {
      using half_e_t = make_integer_t<sizeof(T) / 2, unsigned>;
      auto halved = eve::convert(v0, eve::as_<eve::logical<half_e_t>>{});
      return any_arm_impl(halved, cond);
    }
    else
    {
      if constexpr ( !C::is_complete ) v0 = v0 && cond.mask(eve::as_<l_t>{});

      using u32_4 = typename wide<T, N, arm_128_>::template rebind<std::uint32_t, eve::fixed<4>>;

      auto dwords = eve::bit_cast(v0, eve::as<u32_4>());
      return any_arm_impl(detail::to_logical(dwords), ignore_none);
    }
  }

  template<real_scalar_value T, typename N, arm_abi ABI, relative_conditional_expr C>
  EVE_FORCEINLINE bool any_(EVE_SUPPORTS(neon128_), C const &cond, logical<wide<T,N,ABI>> const &v0) noexcept
  {
     return any_arm_impl(v0, cond);
  }

  template<real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE bool any_(EVE_SUPPORTS(neon128_), logical<wide<T,N,ABI>> const &v0) noexcept
  {
    return any_arm_impl(v0, ignore_none);
  }
}
