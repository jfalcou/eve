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
#include <eve/detail/top_bits.hpp>

namespace eve::detail
{
  template <typename T, typename N, typename C>
  EVE_FORCEINLINE bool any_arm_impl(logical<wide<T, N, arm_64_>> v0, C const & cond)
  {
    using l_t = logical<wide<T, N, arm_64_>>;
    using u32_2 = typename wide<T, N, arm_64_>::template rebind<std::uint32_t, eve::fixed<2>>;
    using u64_1 = typename wide<T, N, arm_64_>::template rebind<std::uint64_t, eve::fixed<1>>;

         if constexpr ( C::is_complete && !C::is_inverted ) return false;
    else if constexpr ( N() == 1 || N() * sizeof(T) <= 4 )  return any(top_bits{v0, cond});
    else if constexpr ( eve::current_api >= eve::asimd )
    {
      if constexpr ( !C::is_complete ) return any(top_bits{v0, cond});
      else
      {
        // We can use u32 max but I don't see why not just use u64?
        auto qword = eve::bit_cast(v0, eve::as_<u64_1>{});
        return vget_lane_u64(qword, 0);
      }
    }
    else
    {
      if constexpr ( !C::is_complete ) v0 = v0 && cond.mask(eve::as_<l_t>{});
      auto dwords = eve::bit_cast(v0, eve::as_<u32_2>{});

      if constexpr( sizeof(T) * N() > 4u ) dwords = vpmax_u32(dwords, dwords);
      return vget_lane_u32(dwords, 0);
    }
  }

  template <typename T, typename N, typename C>
  EVE_FORCEINLINE bool any_arm_impl(logical<wide<T, N, arm_128_>> v0, C const & cond)
  {
    using l_t = logical<wide<T, N, arm_128_>>;
    using u32_4 = typename wide<T, N, arm_128_>::template rebind<std::uint32_t, eve::fixed<4>>;

         if constexpr ( C::is_complete && !C::is_inverted ) return false;
    else if constexpr ( eve::current_api >= eve::asimd )
    {
      if constexpr ( !C::is_complete ) return any(top_bits{v0, cond});
      else
      {
        // There is no vmaxvq_u64, so we use vmaxvq_u32
        auto dwords = eve::bit_cast(v0, eve::as_<u32_4>{});
        return vmaxvq_u32(dwords);
      }
    }
    else if constexpr ( sizeof( T ) >= 2 )
    {
      using half_e_t = make_integer_t<sizeof(T) / 2, unsigned>;
      auto halved = eve::convert(v0, eve::as_<eve::logical<half_e_t>>{});
      return any_arm_impl(halved, cond);
    }
    else
    {
      if constexpr ( !C::is_complete ) v0 = v0 && cond.mask(eve::as_<l_t>{});

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
