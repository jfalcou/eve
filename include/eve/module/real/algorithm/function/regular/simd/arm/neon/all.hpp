//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/conditional.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/convert.hpp>
#include <eve/detail/top_bits.hpp>

namespace eve::detail
{
  template<logical_simd_value T, relative_conditional_expr C>
  EVE_FORCEINLINE bool all_ignore_top_bits_impl(T const &v, C const& cond) noexcept
  {
    eve::detail::top_bits mmask{v};
    eve::detail::top_bits<T> ignore_mmask{cond};

    mmask |= ~ignore_mmask; // we need 1 in ignored elements;

    return eve::detail::all(mmask);
  }

  template <typename T, typename N, typename C>
  EVE_FORCEINLINE bool all_arm_impl(logical<wide<T, N, arm_64_>> v0, C const & cond)
  {
    using l_t = logical<wide<T, N, arm_64_>>;
    using u64_1 = typename wide<T, N, arm_64_>::template rebind<std::uint64_t, eve::fixed<1>>;

         if constexpr ( C::is_complete && !C::is_inverted ) return true;
    else if constexpr ( N() == 1 || N() * sizeof(T) <= 4 )  return all_ignore_top_bits_impl(v0, cond);
    else if constexpr ( eve::current_api >= eve::asimd )
    {
      if constexpr ( !C::is_complete ) return all_ignore_top_bits_impl(v0, cond);
      else
      {
        // I thought about using min here, unlike any (since we do otherwise 2 tests)
        // But
        //   a) I don't have the measurements
        //   b) I suspect when this pops up, compiler might just load u64 directly.
        auto qword = eve::bit_cast(v0, eve::as_<u64_1>{});
        return !~vget_lane_u64(qword, 0);
      }
    }
    else
    {
      if constexpr ( !C::is_complete ) v0 = v0 || cond.mask_inverted(eve::as_<l_t>{});

      if constexpr( N::value == 1 ) return v0.get(0);
      else
      {
        using u32_2 = typename wide<T, N, arm_64_>::template rebind<std::uint32_t, eve::fixed<2>>;
        auto dwords = eve::bit_cast(v0.bits(), eve::as_<u32_2> {});

        if constexpr( sizeof(T) * N() > 4u ) dwords = vpmin_u32(dwords, dwords);

        std::uint32_t combined = vget_lane_u32(dwords, 0);

              if constexpr ( sizeof(T) >= 4 )       return (bool)combined;
        else  if constexpr ( sizeof(T) * N() == 8 ) return !~combined;
        else
        {
          std::uint32_t expected = [] {
            std::uint64_t res = 1;
            res <<= sizeof(T) * N() * 8;
            res -= 1;
            return res;
          }();

          return (combined & expected) == expected;
        }
      }
    }
  }

  template <typename T, typename N, typename C>
  EVE_FORCEINLINE bool all_arm_impl(logical<wide<T, N, arm_128_>> v0, C const & cond)
  {
    using l_t = logical<wide<T, N, arm_128_>>;
    using u32_4 = typename wide<T, N, arm_128_>::template rebind<std::uint32_t, eve::fixed<4>>;

         if constexpr ( C::is_complete && !C::is_inverted ) return true;
    else if constexpr ( eve::current_api >= eve::asimd )
    {
           if constexpr ( !C::is_complete ) return all_ignore_top_bits_impl(v0, cond);
      else if constexpr ( sizeof(T) == 1 )  return vminvq_u8(v0.bits());
      else if constexpr ( sizeof(T) == 2 )  return vminvq_u16(v0.bits());
      else
      {
        // There is no vminvq_u64, so we use vminvq_u32 for everything bigger.
        auto dwords = eve::bit_cast(v0, eve::as_<u32_4>{});
        return vminvq_u32(dwords);
      }
    }
    else if constexpr ( sizeof( T ) >= 2 )
    {
      using half_e_t = make_integer_t<sizeof(T) / 2, unsigned>;
      auto halved = eve::convert(v0, eve::as_<eve::logical<half_e_t>>{});
      return all_arm_impl(halved, cond);
    }
    else
    {
      if constexpr ( !C::is_complete ) v0 = v0 || cond.mask_inverted(eve::as_<l_t>{});

      using u32_4 = typename wide<T, N, arm_128_>::template rebind<std::uint32_t, eve::fixed<4>>;
      auto dwords = eve::bit_cast(v0, eve::as<u32_4>());

      // not the same logic as for uint_32 plain so duplicated.
      return all_arm_impl(dwords == static_cast<std::uint32_t>(-1), ignore_none);
    }
  }

  template<real_scalar_value T, typename N, arm_abi ABI, relative_conditional_expr C>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(neon128_), C const &cond, logical<wide<T, N, ABI>> const &v0) noexcept
  {
    return all_arm_impl(v0, cond);
  }

  template<real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(neon128_), logical<wide<T, N, ABI>> const &v0) noexcept
  {
    return all_arm_impl(v0, ignore_none);
  }
}
