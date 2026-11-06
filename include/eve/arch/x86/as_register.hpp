//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/x86/predef.hpp>
#include <eve/types/float16.hpp>
#include <algorithm>
#include <compare>
#include <concepts>
#include <cstddef>
#include <iosfwd>

namespace eve::_
{
  // ---------------------------------------------------------------------------------------------
  // x86 128
  template<typename T> extern no_register<void> x86_128_register;

  template<std::same_as<double> T>                                                extern __m128d x86_128_register<T>;
  template<std::same_as<float> T>                                                 extern __m128  x86_128_register<T>;
  template<std::same_as<eve::float16_t> T> requires( _::supports_fp16_vector_ops) extern __m128h x86_128_register<T>;
  template<std::same_as<eve::float16_t> T> requires(!_::supports_fp16_vector_ops) extern __m128i x86_128_register<T>;
  template<std::integral T>                                                       extern __m128i x86_128_register<T>;

  template<typename T, width_type N> requires(sizeof(T) * N <= 16)
  extern decltype(x86_128_register<T>) as_register<T, N, eve::x86_128_>;

  // ---------------------------------------------------------------------------------------------
  // x86 256
  template<typename T> extern no_register<void> x86_256_register;

  template<std::same_as<double> T>                                                extern __m256d x86_256_register<T>;
  template<std::same_as<float> T>                                                 extern __m256  x86_256_register<T>;
  template<std::same_as<eve::float16_t> T> requires( _::supports_fp16_vector_ops) extern __m256h x86_256_register<T>;
  template<std::same_as<eve::float16_t> T> requires(!_::supports_fp16_vector_ops) extern __m256i x86_256_register<T>;
  template<std::integral T>                                                       extern __m256i x86_256_register<T>;

  template<typename T, width_type N> requires(sizeof(T) * N <= 32)
  extern decltype(x86_256_register<T>) as_register<T, N, eve::x86_256_>;

  // ---------------------------------------------------------------------------------------------
  // x86 512
  template<typename T> extern no_register<void> x86_512_register;

  template<std::same_as<double> T>                                                extern __m512d x86_512_register<T>;
  template<std::same_as<float> T>                                                 extern __m512  x86_512_register<T>;
  template<std::same_as<eve::float16_t> T> requires( _::supports_fp16_vector_ops) extern __m512h x86_512_register<T>;
  template<std::same_as<eve::float16_t> T> requires(!_::supports_fp16_vector_ops) extern __m512i x86_512_register<T>;
  template<std::integral T>                                                       extern __m512i x86_512_register<T>;

  template<typename T, width_type N> requires(sizeof(T) * N <= 64)
  extern decltype(x86_512_register<T>) as_register<T, N, eve::x86_512_>;

  // ---------------------------------------------------------------------------------------------
  // Masks
  template<int N> extern no_register<void> inner_mask;

  template<int N> requires(N ==  8) extern  __mmask8 inner_mask<N>;
  template<int N> requires(N == 16) extern __mmask16 inner_mask<N>;
  template<int N> requires(N == 32) extern __mmask32 inner_mask<N>;
  template<int N> requires(N == 64) extern __mmask64 inner_mask<N>;

  template<int N>
  struct mask_n
  {
    using type = std::remove_cvref_t<decltype(std::declval<decltype(inner_mask<N>)>())>;
    static constexpr int bits = N;

    explicit constexpr operator type() const { return value; }
    explicit constexpr operator bool() const { return (bool) value; }

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

    template<typename C, typename Ct>
    friend auto& operator<<(std::basic_ostream<C, Ct>& out, const mask_n& m) { return out << m.value; }

    type value;
  };

  using mask8  = mask_n<8>;
  using mask16 = mask_n<16>;
  using mask32 = mask_n<32>;
  using mask64 = mask_n<64>;

  // ---------------------------------------------------------------------------------------------
  // Logical registers
# if defined(SPY_SIMD_IS_X86_AVX512)
  // logical uses different registers in AVX512: a mask whose size depends on the scalar size.
  // The first parameter of the tables is only there to make each row a partial specialization.
  template<typename T, std::size_t Size> extern no_register<void> x86_128_logical_register;
  template<typename T> extern _::mask16 x86_128_logical_register<T, 1>;
  template<typename T> extern _::mask8  x86_128_logical_register<T, 2>;
  template<typename T> extern _::mask8  x86_128_logical_register<T, 4>;
  template<typename T> extern _::mask8  x86_128_logical_register<T, 8>;

  template<typename T, std::size_t Size> extern no_register<void> x86_256_logical_register;
  template<typename T> extern _::mask32 x86_256_logical_register<T, 1>;
  template<typename T> extern _::mask16 x86_256_logical_register<T, 2>;
  template<typename T> extern _::mask8  x86_256_logical_register<T, 4>;
  template<typename T> extern _::mask8  x86_256_logical_register<T, 8>;

  template<typename T, std::size_t Size> extern no_register<void> x86_512_logical_register;
  template<typename T> extern _::mask64 x86_512_logical_register<T, 1>;
  template<typename T> extern _::mask32 x86_512_logical_register<T, 2>;
  template<typename T> extern _::mask16 x86_512_logical_register<T, 4>;
  template<typename T> extern _::mask8  x86_512_logical_register<T, 8>;

  template<typename T, width_type N> requires(sizeof(T) * N <= 16)
  extern decltype(x86_128_logical_register<T, sizeof(T)>) as_logical_register<T, N, eve::x86_128_>;

  template<typename T, width_type N> requires(sizeof(T) * N == 32)
  extern decltype(x86_256_logical_register<T, sizeof(T)>) as_logical_register<T, N, eve::x86_256_>;

  template<typename T, width_type N> requires(sizeof(T) * N == 64)
  extern decltype(x86_512_logical_register<T, sizeof(T)>) as_logical_register<T, N, eve::x86_512_>;
# else
  // logical uses same registers
  template<typename T, width_type N, x86_abi ABI>
  extern decltype(as_register<T, N, ABI>) as_logical_register<T, N, ABI>;
# endif
}
