//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/logical.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/regular/convert.hpp>

#include <bit>

namespace eve::detail
{
  template <typename T>
  EVE_FORCEINLINE std::uint32_t every_2nd_byte_arm64(T const& v) noexcept
  {
    using u8_8  = typename T::template rebind<std::uint8_t,  eve::fixed<8>>;
    using u32_2 = typename T::template rebind<std::uint32_t, eve::fixed<2>>;

    auto bytes    = eve::bit_cast(v, eve::as<u8_8>{});
    auto selected = vtbl1_u8(bytes, u8_8(0, 2, 4, 6, 0, 0, 0, 0));
    auto dwords   = eve::bit_cast(selected, eve::as<u32_2>{});

    return vget_lane_u32(dwords, 0);
  }

  template<typename T>
  EVE_FORCEINLINE std::uint32_t every_4th_byte_arm128(T const& v) noexcept
  {
    using u8_8  = typename T::template rebind<std::uint8_t,  eve::fixed<8>>;
    using u8_16 = typename T::template rebind<std::uint8_t,  eve::fixed<16>>;
    using u32_2 = typename T::template rebind<std::uint32_t, eve::fixed<2>>;

    auto bytes = eve::bit_cast(v, eve::as<u8_16>{});

    uint8x8x2_t table = {{ vget_low_u8(bytes), vget_high_u8(bytes) }};
    u8_8     selected = vtbl2_u8(table, u8_8(0, 4, 8, 12, 0, 0, 0, 0));
    auto     dwords   = eve::bit_cast(selected, eve::as<u32_2>{});

    return vget_lane_u32(dwords, 0);
  }

  template<arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE auto movemask (logical<wide<T, N>> const &v) noexcept
    requires std::same_as<abi_t<T, N>, arm_64_>
  {
    using w_t = wide<T, N>;
    using u16_4 = typename w_t::template rebind<std::uint16_t, eve::fixed<4>>;
    using u32_2 = typename w_t::template rebind<std::uint32_t, eve::fixed<2>>;
    using u64_1 = typename w_t::template rebind<std::uint64_t, eve::fixed<1>>;

         if constexpr ( N() == 1 ) return std::pair{ (std::uint8_t) v.bits().get(0), eve::lane<8> };
    else if constexpr ( sizeof(T) == 1 && N() == 2 )
    {
      auto words = eve::bit_cast(v, eve::as<u16_4>{});
      return std::pair{ vget_lane_u16(words, 0), eve::lane<8> };
    }
    else if constexpr ( sizeof(T) * N() == 4)
    {
      auto dwords = eve::bit_cast(v, eve::as<u32_2>{});
      return std::pair{ vget_lane_u32(dwords, 0), eve::lane<sizeof(T) * 8> };
    }
    else if constexpr ( eve::current_api >= eve::asimd )
    {
      auto qword  = eve::bit_cast(v, eve::as<u64_1>{});
      return std::pair { vget_lane_u64(qword, 0), eve::lane<sizeof(T) * 8> };
    }
    else if constexpr ( sizeof(T) >= 2 )
    {
      return std::pair{ every_2nd_byte_arm64(v.bits()), eve::lane<sizeof(T) * 4> };
    }
    else   // chars
    {
      auto words = eve::bit_cast(v, eve::as<u16_4>{});
      words = vshr_n_u16(words, 4);

      return std::pair{ every_2nd_byte_arm64(words), eve::lane<sizeof(T) * 4> };
    }
  }

  template<arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE auto movemask (logical<wide<T, N>> const &v) noexcept
    requires std::same_as<abi_t<T, N>, arm_128_>
  {
    using w_t = wide<T, N>;
    using u8_8  = typename w_t::template rebind <std::uint8_t,  eve::fixed<8>>;
    using u16_8 = typename w_t::template rebind <std::uint16_t, eve::fixed<8>>;
    using u32_4 = typename w_t::template rebind <std::uint32_t, eve::fixed<4>>;
    using u64_1 = typename w_t::template rebind <std::uint64_t, eve::fixed<1>>;

    if constexpr ( eve::current_api >= eve::asimd && sizeof(T) >= 2 )
    {
      using half_e_t = make_integer_t<sizeof(T) / 2, unsigned>;
      auto halved = eve::convert(v, eve::as<eve::logical<half_e_t>>{});
      auto qword  = eve::bit_cast(halved, eve::as<u64_1>{});
      return std::pair { vget_lane_u64(qword, 0), eve::lane<sizeof(T) * 4> };
    }
    else if constexpr ( sizeof(T) >= 4 )
    {
      return std::pair{ every_4th_byte_arm128(v.bits()), eve::lane<sizeof(T) * 2> };
    }
    else if constexpr ( sizeof(T) == 2 )
    {
      // pack 2 shorts into byte
      auto dwords = eve::bit_cast(v, eve::as<u32_4>{});
      dwords = vshrq_n_u32(dwords, 12);

      return std::pair{ every_4th_byte_arm128(dwords), eve::lane<sizeof(T) * 2> };
    }
    else  // bytes
    {
      // Couldn't figure out anything nice.
      // We will have to suck up the 64 bit emulation on arm-v7, which is not ideal.

      auto words_16 = eve::bit_cast(v, eve::as<u16_8>{});
      words_16 = vshrq_n_u16(words_16, 4);

      // drop top byte
      u8_8  bytes_8  = vmovn_u16(words_16);
      u64_1 qword = eve::bit_cast(bytes_8, eve::as<u64_1>{});

      return std::pair{ vget_lane_u64(qword, 0), eve::lane<4> };
    }
  }
}
