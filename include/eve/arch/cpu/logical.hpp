//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_CPU_LOGICAL_HPP_INCLUDED
#define EVE_ARCH_CPU_LOGICAL_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <iostream>
#include <cstring>

#if defined(EVE_COMP_IS_GNUC)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wuninitialized"
#  pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

namespace eve
{
  template<typename T>
  struct logical
  {
    using value_type                      = T;
    using bits_type                       = detail::as_integer_t<T, unsigned>;
    static constexpr bits_type true_mask  = ~bits_type{0};
    static constexpr bits_type false_mask = bits_type{0};

    /// Default constructor
    EVE_FORCEINLINE constexpr logical() noexcept {}

    /// Constructor from boolean value
    EVE_FORCEINLINE constexpr logical(bool v) noexcept
        : value_(v ? true_mask : false_mask)
    {
    }

    /// Constructor from non-boolean value
    template<typename U>
    EVE_FORCEINLINE explicit constexpr logical(U const& v) noexcept : logical(v != 0)
    {
    }

    // Assignment operator from bool
    EVE_FORCEINLINE constexpr logical &operator=(bool v) noexcept
    {
      value_ = v ? true_mask : false_mask;
      return *this;
    }

    /// Convert a logical value to bool
    EVE_FORCEINLINE constexpr operator bool() const noexcept { return !!value_; }

    /// Explicitly convert a logical value to bool
    EVE_FORCEINLINE constexpr bool value() const noexcept { return !!value_; }

    /// Explicitly convert a logical value to bool negation
    EVE_FORCEINLINE constexpr bool not_value() const noexcept { return !value_; }

    /// Convert a logical to its internal representation value
    EVE_FORCEINLINE constexpr auto bits() const noexcept { return value_; }

    /// Convert a logical to a typed mask value
    EVE_FORCEINLINE constexpr T mask() const noexcept
    {
      value_type that;
      std::memcpy(&that, &value_, sizeof(value_type));
      return that;
    }

  private:
    bits_type value_;
  };

  /// Stream insertion operator
  template<typename T>
  EVE_FORCEINLINE std::ostream &operator<<(std::ostream &os, logical<T> const &v)
  {
    return os << (v.value() ? "true" : "false");
  }
}

#if defined(EVE_COMP_IS_GNUC)
#  pragma GCC diagnostic pop
#endif

#endif
