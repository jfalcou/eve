//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/spy.hpp>
#include <eve/detail/abi.hpp>
#include <eve/traits/translation.hpp>
#include <eve/as.hpp>

#include <bit>
#include <cstdint>
#include <compare>
#include <limits>
#include <concepts>

namespace eve
{
  namespace detail
  {
    constexpr float emulated_fp16_to_fp32(uint16_t raw) noexcept
    {
      uint32_t sign     = (raw & 0x8000u) << 16;
      uint32_t exponent = (raw & 0x7C00u) >> 10;
      uint32_t mantissa = (raw & 0x03FFu);

      uint32_t result;

      if (exponent == 0)
      {
        if (mantissa == 0) return std::bit_cast<float>(sign);
        int shift = std::countl_zero(mantissa) - 21;

        mantissa <<= shift;
        mantissa &= 0x03FFu;
        uint32_t exp32 = 113 - shift;
        result = sign | (exp32 << 23) | (mantissa << 13);
      }
      else if (exponent == 31)
      {
        result = sign | 0x7F800000u | (mantissa << 13);

        if (mantissa != 0) {
            result |= 0x400000u;
        }
      }
      else
      {
        result = sign | ((exponent + 112) << 23) | (mantissa << 13);
      }

      return std::bit_cast<float>(result);
    }

    constexpr uint16_t emulated_fp_to_fp16(float value) noexcept
    {
        uint32_t bits = std::bit_cast<uint32_t>(value);
        uint32_t sign = (bits & 0x80000000u) >> 16;
        int32_t exponent = int32_t((bits >> 23) & 0xFF) - 127;
        uint32_t mantissa = bits & 0x7FFFFFu;

        if ((bits & 0x7F800000u) == 0x7F800000u)
        {
          if (mantissa != 0)
          {
            uint16_t nan = uint16_t((mantissa >> 13) ? (mantissa >> 13) : 1);
            return uint16_t(sign | 0x7C00u | nan);
          }

          return uint16_t(sign | 0x7C00u);
        }

        if (exponent > 15)
        {
          return uint16_t(sign | 0x7C00u);
        }

        if (exponent <= -15)
        {
          if (exponent < -25) return uint16_t(sign);
          uint32_t mant_with_hidden = mantissa | 0x800000u;
          int shift = -exponent - 1;
          if (shift > 24) shift = 24;

          uint32_t rounded = mant_with_hidden >> shift;
          uint32_t remainder = mant_with_hidden & ((1u << shift) - 1);
          uint32_t threshold = 1u << (shift - 1);

          if (remainder > threshold || (remainder == threshold && (rounded & 1)))
          {
            rounded++;
          }

          return uint16_t(sign | rounded);
        }

        uint32_t fp16_exp = uint32_t(exponent + 15) << 10;
        uint32_t mant_rounded = mantissa >> 13;
        uint32_t round_bits = mantissa & 0x1FFFu;

        if (round_bits > 0x1000u || (round_bits == 0x1000u && (mant_rounded & 1u)))
        {
          mant_rounded++;
          if (mant_rounded == 0x400u)
          {
            mant_rounded = 0;
            fp16_exp += 0x0400u;

            if ((fp16_exp >> 10) >= 31u)
            {
              return uint16_t(sign | 0x7C00u);
            }
          }
        }

        return uint16_t(sign | fp16_exp | (mant_rounded & 0x3FFu));
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
  }

  #if defined(SPY_SUPPORTS_FP16_TYPE) && !defined(EVE_NO_NATIVE_FP16)
    namespace detail
    {
      static constexpr bool supports_fp16_native_type = spy::supports::fp16::type;
      static constexpr bool supports_fp16_scalar_ops = spy::supports::fp16::scalar_ops;
      static constexpr bool supports_fp16_vector_ops = spy::supports::fp16::vector_ops;
      static constexpr bool supports_fp16_vector_conversion = spy::supports::fp16::vector_conversion;
    }

    using float16_t = _Float16;
  #else
    namespace detail
    {
      static constexpr bool supports_fp16_native_type = false;
      static constexpr bool supports_fp16_scalar_ops = false;
      static constexpr bool supports_fp16_vector_ops = false;
      static constexpr bool supports_fp16_vector_conversion = false;
    }

    struct float16_t {
      private:
        uint16_t data;

        template <typename T>
        constexpr T into() const noexcept
        {
          if constexpr (std::same_as<T, bool>)
          {
            return (data != 0) && (data != 0x8000);
          }
          else
          {
            return static_cast<T>(detail::emulated_fp16_to_fp32(data));
          }
        }

      public:
        constexpr float16_t() = default;
        constexpr float16_t(std::integral auto v): data(detail::emulated_int_to_fp16(v)) { }
        constexpr float16_t(std::floating_point auto v): data(detail::emulated_fp_to_fp16(v)) { }

        constexpr EVE_FORCEINLINE explicit operator bool()               const noexcept { return into<bool>(); }

        constexpr EVE_FORCEINLINE explicit operator float()              const noexcept { return into<float>(); }
        constexpr EVE_FORCEINLINE explicit operator double()             const noexcept { return into<double>(); }

        constexpr EVE_FORCEINLINE explicit operator char()               const noexcept { return into<char>(); }
        constexpr EVE_FORCEINLINE explicit operator signed char()        const noexcept { return into<signed char>(); }
        constexpr EVE_FORCEINLINE explicit operator unsigned char()      const noexcept { return into<unsigned char>(); }
        constexpr EVE_FORCEINLINE explicit operator short()              const noexcept { return into<short>(); }
        constexpr EVE_FORCEINLINE explicit operator unsigned short()     const noexcept { return into<unsigned short>(); }
        constexpr EVE_FORCEINLINE explicit operator int()                const noexcept { return into<int>(); }
        constexpr EVE_FORCEINLINE explicit operator unsigned int()       const noexcept { return into<unsigned int>(); }
        constexpr EVE_FORCEINLINE explicit operator long()               const noexcept { return into<long>(); }
        constexpr EVE_FORCEINLINE explicit operator unsigned long()      const noexcept { return into<unsigned long>(); }
        constexpr EVE_FORCEINLINE explicit operator long long()          const noexcept { return into<long long>(); }
        constexpr EVE_FORCEINLINE explicit operator unsigned long long() const noexcept { return into<unsigned long long>(); }

        constexpr EVE_FORCEINLINE float16_t& operator+=(float16_t const& other) noexcept
        {
          *this = float16_t{ into<float>() + static_cast<float>(other) };
          return *this;
        }

        constexpr EVE_FORCEINLINE float16_t& operator-=(float16_t const& other) noexcept
        {
          *this = float16_t{ into<float>() - static_cast<float>(other) };
          return *this;
        }

        constexpr EVE_FORCEINLINE float16_t& operator*=(float16_t const& other) noexcept
        {
          *this = float16_t{ into<float>() * static_cast<float>(other) };
          return *this;
        }

        constexpr EVE_FORCEINLINE float16_t& operator/=(float16_t const& other) noexcept
        {
          *this = float16_t{ into<float>() / static_cast<float>(other) };
          return *this;
        }

        constexpr EVE_FORCEINLINE float16_t operator+(float16_t const& other) const noexcept
        {
          return float16_t{ *this } += other;
        }

        constexpr EVE_FORCEINLINE float16_t operator-(float16_t const& other) const noexcept
        {
          return float16_t{ *this } -= other;
        }

        constexpr EVE_FORCEINLINE float16_t operator*(float16_t const& other) const noexcept
        {
          return float16_t{ *this } *= other;
        }

        constexpr EVE_FORCEINLINE float16_t operator/(float16_t const& other) const noexcept
        {
          return float16_t{ *this } /= other;
        }

        constexpr EVE_FORCEINLINE float16_t operator-() const noexcept
        {
          return float16_t{-into<float>()};
        }

        constexpr EVE_FORCEINLINE float16_t& operator++() noexcept
        {
          *this += float16_t{1.0f};
          return *this;
        }

        constexpr EVE_FORCEINLINE float16_t operator++(int) noexcept
        {
          float16_t tmp = *this;
          ++(*this);
          return tmp;
        }

        constexpr EVE_FORCEINLINE float16_t& operator--() noexcept
        {
          *this -= float16_t{1.0f};
          return *this;
        }

        constexpr EVE_FORCEINLINE float16_t operator--(int) noexcept
        {
          float16_t tmp = *this;
          --(*this);
          return tmp;
        }

        constexpr EVE_FORCEINLINE std::partial_ordering operator<=>(float16_t const& other) const noexcept
        {
          return detail::emulated_fp16_compare(data, other.data);
        }

        constexpr EVE_FORCEINLINE bool operator==(float16_t const& other) const noexcept
        {
          return detail::emulated_fp16_compare(data, other.data) == std::partial_ordering::equivalent;
        }
    };

    template <typename T>
    constexpr EVE_FORCEINLINE float16_t operator+(T const& lhs, float16_t const& rhs) noexcept
      requires (std::integral<T> || std::floating_point<T>)
    {
      return float16_t{ static_cast<float>(lhs) + static_cast<float>(rhs) };
    }

    template <typename T>
    constexpr EVE_FORCEINLINE float16_t operator-(T const& lhs, float16_t const& rhs) noexcept
      requires (std::integral<T> || std::floating_point<T>)
    {
      return float16_t{ static_cast<float>(lhs) - static_cast<float>(rhs) };
    }

    template <typename T>
    constexpr EVE_FORCEINLINE float16_t operator*(T const& lhs, float16_t const& rhs) noexcept
      requires (std::integral<T> || std::floating_point<T>)
    {
      return float16_t{ static_cast<float>(lhs) * static_cast<float>(rhs) };
    }

    template <typename T>
    constexpr EVE_FORCEINLINE float16_t operator/(T const& lhs, float16_t const& rhs) noexcept
      requires (std::integral<T> || std::floating_point<T>)
    {
      return float16_t{ static_cast<float>(lhs) / static_cast<float>(rhs) };
    }
  #endif

  namespace detail
  {
    constexpr static eve::float16_t float16_from_bits(std::uint16_t bits) noexcept
    {
      return std::bit_cast<eve::float16_t>(bits);
    }
  }
}
