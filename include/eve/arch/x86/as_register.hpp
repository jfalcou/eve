//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/x86/predef.hpp>
#include <compare>
#include <type_traits>
#include <ostream>

namespace eve
{
  template<typename T>
  struct logical;
  struct x86_128_;
  struct x86_256_;
}

#if defined(EVE_HW_X86)

namespace eve
{
  template<typename Type, typename Size>
  struct as_register<Type, Size, eve::x86_128_>
  {
    static constexpr auto find()
    {
      constexpr auto width = sizeof(Type)*Size::value;
      if constexpr(width <= 16)
      {
              if constexpr(std::is_same_v<Type,double> ) return  __m128d{};
        else  if constexpr(std::is_same_v<Type,float > ) return  __m128{};
        else  if constexpr(std::is_integral_v<Type>    ) return  __m128i{};
      }
    }

    using type = decltype(find());
    static_assert( !std::is_void_v<type>, "[eve x86] - Type is not usable in a SIMD register");
  };

  template<typename Type, typename Size>
  struct as_register<Type, Size, eve::x86_256_>
  {
    static constexpr auto find()
    {
      constexpr auto width = sizeof(Type)*Size::value;
      if constexpr(width == 32)
      {
              if constexpr(std::is_same_v<Type,double> ) return __m256d{};
        else  if constexpr(std::is_same_v<Type,float > ) return __m256{};
        else  if constexpr(std::is_integral_v<Type>    ) return __m256i{};
      }
    }

    using type = decltype(find());
    static_assert( !std::is_void_v<type>, "[eve x86] - Type is not usable in a SIMD register");
  };

  template<typename Type, typename Size>
  struct as_register<Type, Size, eve::x86_512_>
  {
    static constexpr auto find()
    {
      constexpr auto width = sizeof(Type)*Size::value;
      if constexpr(width == 64)
      {
              if constexpr(std::is_same_v<Type,double> ) return __m512d{};
        else  if constexpr(std::is_same_v<Type,float > ) return __m512{};
        else  if constexpr(std::is_integral_v<Type>    ) return __m512i{};
      }
    }

    using type = decltype(find());
    static_assert( !std::is_void_v<type>, "[eve x86] - Type is not usable in a SIMD register");
  };

  namespace detail
  {
    template<int N> struct as_mask;

    template<int N> struct inner_mask;

    template<> struct inner_mask<8>   { using type = __mmask8;  };
    template<> struct inner_mask<16>  { using type = __mmask16; };
    template<> struct inner_mask<32>  { using type = __mmask32; };
    template<> struct inner_mask<64>  { using type = __mmask64; };

    template<int N> struct mask_n
    {
      using type = typename inner_mask<N>::type;
      static constexpr int bits = N;

      explicit constexpr operator type() const { return value; }
      explicit constexpr operator bool() const { return (bool)value; }

      // != and reverse are generated.
      // <=> didn't work for some reason for ==
      friend bool operator== (mask_n m, type n) { return m == mask_n{n}; }
      friend bool operator== (mask_n  , mask_n) = default;
      friend auto operator<=>(mask_n  , mask_n) = default;

      friend constexpr mask_n operator~(mask_n m) { return mask_n{ static_cast<type>(~m.value) }; }

      friend constexpr mask_n& operator&=(mask_n& m, mask_n n) { m.value &= n.value; return m;     }
      friend constexpr mask_n& operator&=(mask_n& m, type   n) { m.value &= n;       return m;     }
      friend constexpr mask_n  operator& (mask_n  m, mask_n n) { mask_n t{m}; return t &= n; }
      friend constexpr mask_n  operator& (mask_n  m, type   n) { mask_n t{n}; return t &= m;       }
      friend constexpr mask_n  operator& (type    m, mask_n n) { mask_n t{m}; return t &= n;       }

      friend constexpr mask_n& operator|=(mask_n& m, mask_n n) { m.value |= n.value; return m;     }
      friend constexpr mask_n& operator|=(mask_n& m, type   n) { m.value |= n;       return m;     }
      friend constexpr mask_n  operator| (mask_n  m, mask_n n) { mask_n t{m}; return t |= n; }
      friend constexpr mask_n  operator| (mask_n  m, type   n) { mask_n t{n}; return t |= m;       }
      friend constexpr mask_n  operator| (type    m, mask_n n) { mask_n t{m}; return t |= n;       }

      friend constexpr mask_n& operator^=(mask_n& m, mask_n n) { m.value ^= n.value; return m;     }
      friend constexpr mask_n& operator^=(mask_n& m, type   n) { m.value ^= n;       return m;     }
      friend constexpr mask_n  operator^ (mask_n  m, mask_n n) { mask_n t{m.value}; return t ^= n; }
      friend constexpr mask_n  operator^ (mask_n  m, type   n) { mask_n t{n}; return t ^= m;       }
      friend constexpr mask_n  operator^ (type    m, mask_n n) { mask_n t{m}; return t ^= n;       }

      friend constexpr mask_n&  operator<<=(mask_n& m, std::ptrdiff_t s) { m.value <<= s; return m; }
      friend constexpr mask_n   operator<< (mask_n  m, std::ptrdiff_t s) { mask_n t{m.value}; return t <<= s; }
      friend constexpr mask_n&  operator>>=(mask_n& m, std::ptrdiff_t s) { m.value >>= s; return m; }
      friend constexpr mask_n   operator>> (mask_n  m, std::ptrdiff_t s) { mask_n t{m}; return t >>= s; }

      friend std::ostream& operator<<(std::ostream& out, const mask_n& m) { return out << m.value; }

      type value;
    };

    using mask8  = mask_n<8>;
    using mask16 = mask_n<16>;
    using mask32 = mask_n<32>;
    using mask64 = mask_n<64>;

    template<> struct as_mask<8>  { using type = mask8; };
    template<> struct as_mask<16> { using type = mask16; };
    template<> struct as_mask<32> { using type = mask32; };
    template<> struct as_mask<64> { using type = mask64; };

    template<int N> using as_mask_t = typename as_mask<std::max(8,N)>::type;
  }

  // logical uses different registers in AVX512
  template<typename Type, typename Size>
  struct as_logical_register<Type, Size, eve::x86_512_>
  {
    static constexpr auto find()
    {
      constexpr auto width = sizeof(Type)*Size::value;
      if constexpr(width == 64) return detail::as_mask_t<64/sizeof(Type)>{};
    }

    using type = decltype(find());
    static_assert( !std::is_void_v<type>, "[eve x86] - Type is not usable in a SIMD register");
  };

# if defined(SPY_SIMD_IS_X86_AVX512)
  template<typename Type, typename Size>
  struct as_logical_register<Type, Size, eve::x86_128_>
  {
    static constexpr auto find()
    {
      constexpr auto width = sizeof(Type)*Size::value;
      if constexpr(width <= 16)
      {
        if constexpr(sizeof(Type) == 1) return detail::mask16{};
        else                            return detail::mask8{};
      }
    }

    using type = decltype(find());
    static_assert( !std::is_void_v<type>, "[eve x86] - Type is not usable in a SIMD register");
  };

  template<typename Type, typename Size>
  struct as_logical_register<Type, Size, eve::x86_256_>
  {
    static constexpr auto find()
    {
      constexpr auto width = sizeof(Type)*Size::value;
      if constexpr(width == 32)
      {
        if constexpr(Size::value <= 8 )  return detail::mask8{};
        if constexpr(Size::value == 16)  return detail::mask16{};
        if constexpr(Size::value == 32)  return detail::mask32{};
      }
    }

    using type = decltype(find());
    static_assert( !std::is_void_v<type>, "[eve x86] - Type is not usable in a SIMD register");
  };

# else
  // logical uses same registers
  template<typename T, typename Size>
  struct as_logical_register<T, Size, eve::x86_128_> : as_register<T, Size, eve::x86_128_>
  {
  };

  template<typename T, typename Size>
  struct as_logical_register<T, Size, eve::x86_256_> : as_register<T, Size, eve::x86_256_>
  {
  };

# endif
}

#endif
