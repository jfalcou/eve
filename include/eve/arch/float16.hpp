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

namespace eve
{
  namespace detail
  {
    // taken from https://github.com/QiJune/majel/blob/master/float16_t.h
    static constexpr int32_t fp16_shift = 13;
    static constexpr int32_t fp16_shiftSign = 16;
    static constexpr int32_t fp16_infN = 0x7F800000;
    // the following constant is set to 65519 instead of 56504 to emulate the rounding behaviour observed on real hw.
    static constexpr int32_t fp16_maxN = 0x477FEF00; //max flt16 as flt32
    static constexpr int32_t fp16_minN = 0x38800000; //min flt16 normal as flt32
    static constexpr int32_t fp16_sigN = 0x80000000; //sign bit
    static constexpr int32_t fp16_infC = fp16_infN >> fp16_shift;
    static constexpr int32_t fp16_nanN = (fp16_infC + 1) << fp16_shift; //minimum flt16 nan as float32
    static constexpr int32_t fp16_maxC = fp16_maxN >> fp16_shift;
    static constexpr int32_t fp16_minC = fp16_minN >> fp16_shift;
    static constexpr int32_t fp16_sigC = fp16_sigN >> fp16_shiftSign;
    static constexpr int32_t fp16_mulN = 0x52000000; //(1 << 23) / minN
    static constexpr int32_t fp16_mulC = 0x33800000; //minN / (1 << (23 - shift))
    static constexpr int32_t fp16_subC = 0x003FF; //max flt32 subnormal downshifted
    static constexpr int32_t fp16_norC = 0x00400; //min flt32 normal downshifted
    static constexpr int32_t fp16_maxD = fp16_infC - fp16_maxC - 1;
    static constexpr int32_t fp16_minD = fp16_minC - fp16_subC - 1;

    union Bits {
        float f;
        int32_t si;
        uint32_t ui;
    };

    constexpr float emulated_fp16_to_fp32(uint16_t raw) noexcept
    {
      Bits v;
      v.ui = raw;
      int32_t sign = v.si & fp16_sigC;
      v.si ^= sign;
      sign <<= fp16_shiftSign;
      v.si ^= ((v.si + fp16_minD) ^ v.si) & -(v.si > fp16_subC);
      v.si ^= ((v.si + fp16_maxD) ^ v.si) & -(v.si > fp16_maxC);
      Bits s;
      s.si = fp16_mulC;
      s.f *= v.si;
      int32_t mask = -(fp16_norC > v.si);
      v.si <<= fp16_shift;
      v.si ^= (s.si ^ v.si) & mask;
      v.si |= sign;
      return v.f;
    }

    template <std::floating_point T>
    constexpr std::uint16_t emulated_fp_to_fp16(T value) noexcept
    {
      const float f = static_cast<float>(value);

      Bits v, s;
      v.f = f;
      uint32_t sign = v.si & fp16_sigN;
      v.si ^= sign;
      sign >>= fp16_shiftSign; // logical shift
      s.si = fp16_mulN;
      s.si = s.f * v.f; // correct subnormals
      v.si ^= (s.si ^ v.si) & -(fp16_minN > v.si);
      v.si ^= (fp16_infN ^ v.si) & -((fp16_infN > v.si) & (v.si > fp16_maxN));
      v.si ^= (fp16_nanN ^ v.si) & -((fp16_nanN > v.si) & (v.si > fp16_infN));
      v.ui >>= fp16_shift; // logical shift
      v.si ^= ((v.si - fp16_maxD) ^ v.si) & -(v.si > fp16_maxC);
      v.si ^= ((v.si - fp16_minD) ^ v.si) & -(v.si > fp16_subC);
      return v.ui | sign;
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

  #if defined(SPY_SUPPORTS_FP16_TYPE) && !defined(EVE_NO_NATIVE_FP16)
    namespace detail
    {
      static constexpr bool supports_fp16_native_type = spy::supports::fp16::type;
      static constexpr bool supports_fp16_scalar_ops = spy::supports::fp16::scalar_ops;
      static constexpr bool supports_fp16_vector_ops = spy::supports::fp16::vector_ops;
    }

    using float16_t = _Float16;
  #else
    namespace detail
    {
      static constexpr bool supports_fp16_native_type = false;
      static constexpr bool supports_fp16_scalar_ops = false;
      static constexpr bool supports_fp16_vector_ops = false;
    }

    struct float16_t {
      private:
        uint16_t data;

        template <typename T>
        constexpr T into() const noexcept
        {
          return static_cast<T>(detail::emulated_fp16_to_fp32(data));
        }

      public:
        constexpr float16_t() = default;
        constexpr explicit float16_t(std::integral auto v): data(detail::emulated_int_to_fp16(v)) { }
        constexpr explicit float16_t(std::floating_point auto v): data(detail::emulated_fp_to_fp16(v)) { }


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

        constexpr EVE_FORCEINLINE float16_t& operator+=(float16_t const& other) noexcept
        {
          *this = float16_t(into<float>() + static_cast<float>(other));
          return *this;
        }

        constexpr EVE_FORCEINLINE float16_t& operator-=(float16_t const& other) noexcept
        {
          *this = float16_t(into<float>() - static_cast<float>(other));
          return *this;
        }

        constexpr EVE_FORCEINLINE float16_t& operator*=(float16_t const& other) noexcept
        {
          *this = float16_t(into<float>() * static_cast<float>(other));
          return *this;
        }

        constexpr EVE_FORCEINLINE float16_t& operator/=(float16_t const& other) noexcept
        {
          *this = float16_t(into<float>() / static_cast<float>(other));
          return *this;
        }

        constexpr EVE_FORCEINLINE float16_t operator+(float16_t const& other) const noexcept
        {
          return float16_t(*this) += other;
        }

        constexpr EVE_FORCEINLINE float16_t operator-(float16_t const& other) const noexcept
        {
          return float16_t(*this) -= other;
        }

        constexpr EVE_FORCEINLINE float16_t operator*(float16_t const& other) const noexcept
        {
          return float16_t(*this) *= other;
        }

        constexpr EVE_FORCEINLINE float16_t operator/(float16_t const& other) const noexcept
        {
          return float16_t(*this) /= other;
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
    };
  #endif

  namespace detail
  {
    constexpr static eve::float16_t float16_from_bits(std::uint16_t bits) noexcept
    {
      return std::bit_cast<eve::float16_t>(bits);
    }
  }
}
