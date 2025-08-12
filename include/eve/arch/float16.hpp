//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/spy.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/traits/translation.hpp>

#include <bit>
#include <cmath>
#include <cstdint>
#include <compare>
#include <limits>
#include <iostream>
namespace eve
{
  namespace detail
  {
    constexpr float emulated_fp16_to_fp32(uint16_t raw) noexcept
    {
      std::uint32_t sign = (raw & 0x8000) << 16;
      std::uint32_t exp = (raw & 0x7C00) >> 10;
      std::uint32_t mantissa = raw & 0x03FF;

      if (exp == 0) {
        if (mantissa == 0) {
          return std::bit_cast<float>(sign);
        } else {
          // Subnormal - convert to normalized float32
          int shift = 0;
          while ((mantissa & 0x0400) == 0) {
            mantissa <<= 1;
            shift++;
          }
          mantissa &= 0x03FF;
          exp = 127 - 15 - shift + 1;
          return std::bit_cast<float>(sign | (exp << 23) | (mantissa << 13));
        }
      } else if (exp == 31) {
        // Infinity or NaN
        if (mantissa == 0) {
          return std::bit_cast<float>(sign | 0x7F800000);
        } else {
          return std::numeric_limits<float>::quiet_NaN();
        }
      } else {
        // Normal case, adjust exponent bias
        exp = exp - 15 + 127;
        return std::bit_cast<float>(sign | (exp << 23) | (mantissa << 13));
      }
    }

    template <std::floating_point T>
    constexpr std::uint16_t emulated_fp_to_fp16(T value) noexcept
    {
      const uint32_t u32 = std::bit_cast<uint32_t>(static_cast<float>(value));
      const uint16_t sign = (u32 >> 16) & 0x8000;

      if (std::isnan(value)) {
        return 0xFFFF;
      }

      if (std::isinf(value)) {
        return sign | 0x7C00;
      }

      const int32_t biased_exp32 = ((u32 >> 23) & 0xFF) - 127;
      const uint32_t mantissa32 = u32 & 0x7FFFFF;

      // Case 1: The number is too large and will overflow to float16 infinity.
      // The maximum exponent for a normal float16 is 15.
      if (biased_exp32 > 15) {
          return sign | 0x7C00;
      }

      // Case 2: The number will be a normalized float16.
      // The exponent range for normal float16s is [-14, 15].
      if (biased_exp32 >= -14) {
          // Re-bias the exponent for the 5-bit float16 format (bias of 15).
          uint16_t exp16 = static_cast<uint16_t>(biased_exp32 + 15);

          // Round the 23-bit mantissa to 10 bits. The shift is 13 bits.
          // Add half of the least significant bit of the target mantissa for rounding.
          uint32_t rounded_mant = mantissa32 + (1u << 12);
          uint16_t mantissa16 = rounded_mant >> 13;

          // Check if rounding caused the mantissa to overflow.
          if (rounded_mant & 0x800000) {
              mantissa16 = 0; // Mantissa becomes zero
              exp16++;        // Exponent is incremented
          }

          // If rounding caused the exponent to overflow, the result is infinity.
          if (exp16 > 30) {
              return sign | 0x7C00;
          }

          return sign | (exp16 << 10) | mantissa16;
      }

      // Case 3: The number will become a subnormal float16 or underflow to zero.
      // The smallest float16 subnormal has an effective exponent of -24.
      if (biased_exp32 < -24) {
          return sign; // Underflow to signed zero.
      }

      // Handle subnormal conversion for exponents in range [-24, -15].
      // The float32 value is (1.mantissa32) * 2^biased_exp32.
      // We want to represent this as (0.mantissa16) * 2^-14.
      // This requires a right-shift of the significand.
      const uint32_t significand32 = mantissa32 | 0x800000;

      // The shift amount is derived from the goal of aligning the exponents.
      // shift = - (exponent + 1)
      const int shift = -(biased_exp32 + 1);

      // Implement round-to-nearest-even.
      uint32_t truncated_part = significand32 & ((1u << shift) - 1);
      uint16_t mantissa16 = significand32 >> shift;

      // Check the guard bit (the MSB of the truncated part).
      if ((truncated_part > (1u << (shift - 1))) || // Greater than halfway
          ((truncated_part == (1u << (shift - 1))) && ((mantissa16 & 1) != 0))) { // Exactly halfway, round to even
          mantissa16++;
      }

      // A subnormal number could round up to become the smallest normal number.
      if (mantissa16 >= 0x400) {
          return sign | 0x0400; // Smallest normal f16
      }

      return sign | mantissa16;
    }

    template <std::integral T>
    constexpr std::uint16_t emulated_int_to_fp16(T value) noexcept
    {
      return emulated_fp_to_fp16(static_cast<float>(value));
    }

    constexpr std::partial_ordering emulated_fp16_compare(std::uint16_t a_bits, std::uint16_t b_bits) noexcept
    {
      bool a_is_nan = ((a_bits & 0x7C00) == 0x7C00) && ((a_bits & 0x03FF) != 0);
      bool b_is_nan = ((b_bits & 0x7C00) == 0x7C00) && ((b_bits & 0x03FF) != 0);

      if (a_is_nan || b_is_nan) {
        return std::partial_ordering::unordered;
      }

      bool a_sign = (a_bits & 0x8000) != 0;
      bool b_sign = (b_bits & 0x8000) != 0;

      if (a_sign != b_sign) {
        bool a_is_zero = (a_bits & 0x7FFF) == 0;
        bool b_is_zero = (b_bits & 0x7FFF) == 0;

        if (a_is_zero && b_is_zero) return std::partial_ordering::equivalent;

        return a_sign ? std::partial_ordering::less : std::partial_ordering::greater;
      }

      uint16_t a_mag = a_bits & 0x7FFF;
      uint16_t b_mag = b_bits & 0x7FFF;

      if (a_mag == b_mag) return std::partial_ordering::equivalent;

      if (a_sign) {
        return (a_mag > b_mag) ? std::partial_ordering::less : std::partial_ordering::greater;
      } else {
        return (a_mag < b_mag) ? std::partial_ordering::less : std::partial_ordering::greater;
      }
    }

    struct fp16_supports_info
    {
  #if defined(EVE_NO_NATIVE_FP16)
      static constexpr bool type = false;
      static constexpr bool scalar_ops = false;
      static constexpr bool vector_ops = false;
  #else
      static constexpr bool type = spy::supports::fp16::type;
      static constexpr bool scalar_ops = spy::supports::fp16::scalar_ops;
      static constexpr bool vector_ops = spy::supports::fp16::vector_ops;
  #endif
    };
  }

  namespace
  {
    struct from_underlying { };
  }

  template<typename Underlying>
  struct basic_float16
  {
    private:
      Underlying data;

      constexpr explicit basic_float16(from_underlying, Underlying value) noexcept
        : data(value) {}

      template <std::floating_point T>
      constexpr static Underlying make(T value) noexcept;

      template <std::integral T>
      constexpr static Underlying make(T value) noexcept;

      template <typename T>
      constexpr T into() const noexcept
      {
        if constexpr (supports::type) return static_cast<T>(data);
        else                          return static_cast<T>(detail::emulated_fp16_to_fp32(data));
      }

    public:
      using supports = detail::fp16_supports_info;

      constexpr basic_float16() noexcept = default;
      constexpr basic_float16(basic_float16 const&) noexcept = default;

      constexpr explicit basic_float16(std::integral auto value) noexcept
        : data(make(value)) {}

      constexpr explicit basic_float16(std::floating_point auto value) noexcept
        : data(make(value)) {}

      constexpr EVE_FORCEINLINE static basic_float16 from_bits(std::uint16_t bits) noexcept
      {
        return basic_float16{ from_underlying{}, std::bit_cast<Underlying>(bits) };
      }

      constexpr EVE_FORCEINLINE std::uint16_t bits() const noexcept
      {
        return std::bit_cast<std::uint16_t>(data);
      }

      constexpr EVE_FORCEINLINE operator float()              const noexcept { return into<float>(); }
      constexpr EVE_FORCEINLINE operator double()             const noexcept { return into<double>(); }

      constexpr EVE_FORCEINLINE operator char()               const noexcept { return into<char>(); }
      constexpr EVE_FORCEINLINE operator signed char()        const noexcept { return into<signed char>(); }
      constexpr EVE_FORCEINLINE operator unsigned char()      const noexcept { return into<unsigned char>(); }
      constexpr EVE_FORCEINLINE operator short()              const noexcept { return into<short>(); }
      constexpr EVE_FORCEINLINE operator unsigned short()     const noexcept { return into<unsigned short>(); }
      constexpr EVE_FORCEINLINE operator int()                const noexcept { return into<int>(); }
      constexpr EVE_FORCEINLINE operator unsigned int()       const noexcept { return into<unsigned int>(); }
      constexpr EVE_FORCEINLINE operator long()               const noexcept { return into<long>(); }
      constexpr EVE_FORCEINLINE operator unsigned long()      const noexcept { return into<unsigned long>(); }
      constexpr EVE_FORCEINLINE operator long long()          const noexcept { return into<long long>(); }
      constexpr EVE_FORCEINLINE operator unsigned long long() const noexcept { return into<unsigned long long>(); }

      // Arithmetic operators
      constexpr EVE_FORCEINLINE basic_float16 operator+(basic_float16 const& other) const noexcept
      {
        if constexpr (supports::type) return basic_float16{from_underlying{}, data + other.data};
        else                          return basic_float16{into<float>() + static_cast<float>(other)};
      }

      constexpr EVE_FORCEINLINE basic_float16 operator-(basic_float16 const& other) const noexcept
      {
        if constexpr (supports::type) return basic_float16{from_underlying{}, data - other.data};
        else                          return basic_float16{into<float>() - static_cast<float>(other)};
      }

      constexpr EVE_FORCEINLINE basic_float16 operator*(basic_float16 const& other) const noexcept
      {
        if constexpr (supports::type) return basic_float16{from_underlying{}, data * other.data};
        else                          return basic_float16{into<float>() * static_cast<float>(other)};
      }

      constexpr EVE_FORCEINLINE basic_float16 operator/(basic_float16 const& other) const noexcept
      {
        if constexpr (supports::type) return basic_float16{from_underlying{}, data / other.data};
        else                          return basic_float16{into<float>() / static_cast<float>(other)};
      }

      constexpr EVE_FORCEINLINE basic_float16 operator-() const noexcept
      {
        if constexpr (supports::type) return basic_float16{from_underlying{}, -data};
        else                          return basic_float16{-into<float>()};
      }

      constexpr EVE_FORCEINLINE basic_float16& operator+=(basic_float16 const& other) noexcept
      {
        return *this = *this + other;
      }

      constexpr EVE_FORCEINLINE basic_float16& operator-=(basic_float16 const& other) noexcept
      {
        return *this = *this - other;
      }

      constexpr EVE_FORCEINLINE basic_float16& operator*=(basic_float16 const& other) noexcept
      {
        return *this = *this * other;
      }

      constexpr EVE_FORCEINLINE basic_float16& operator/=(basic_float16 const& other) noexcept
      {
        return *this = *this / other;
      }

      constexpr EVE_FORCEINLINE basic_float16& operator++() noexcept
      {
        *this += basic_float16{1.0f};
        return *this;
      }

      constexpr EVE_FORCEINLINE basic_float16 operator++(int) noexcept
      {
        basic_float16 tmp = *this;
        ++(*this);
        return tmp;
      }

      constexpr EVE_FORCEINLINE basic_float16& operator--() noexcept
      {
        *this -= basic_float16{1.0f};
        return *this;
      }

      constexpr EVE_FORCEINLINE basic_float16 operator--(int) noexcept
      {
        basic_float16 tmp = *this;
        --(*this);
        return tmp;
      }

      constexpr EVE_FORCEINLINE std::partial_ordering operator<=>(basic_float16 const& other) const noexcept
      {
        if constexpr (supports::type) return data <=> other.data;
        else                          return detail::emulated_fp16_compare(data, other.data);
      }
  };

#if defined(SPY_SUPPORTS_FP16_TYPE) && !defined(EVE_NO_NATIVE_FP16)
  using float16 = basic_float16<_Float16>;

  template<>
  struct translation_of<float16>
  {
    using type = _Float16;
  };
#else
  using float16 = basic_float16<std::uint16_t>;
#endif

  namespace detail
  {
    using f16 = translate_t<float16>;

    constexpr f16 f16_from_bits(std::uint16_t bits) noexcept
    {
      return std::bit_cast<f16>(bits);
    }
  }

  template<typename Underlying>
  template<std::floating_point T>
  constexpr Underlying basic_float16<Underlying>::make(T value) noexcept
  {
    if constexpr (basic_float16<Underlying>::supports::type) return static_cast<Underlying>(value);
    else                                                     return detail::emulated_fp_to_fp16(value);
  }

  template<typename Underlying>
  template<std::integral T>
  constexpr Underlying basic_float16<Underlying>::make(T value) noexcept
  {
    if constexpr (basic_float16<Underlying>::supports::type) return static_cast<Underlying>(value);
    else                                                     return detail::emulated_int_to_fp16(value);
  }
}
