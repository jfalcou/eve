//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_TYPE_LOGICAL_HPP_INCLUDED
#define EVE_MODULE_CORE_TYPE_LOGICAL_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <iostream>

namespace eve
{
  template<typename T> struct logical
  {
    using value_type  = T;
    using bits        = detail::as_integer_t<T,unsigned>;
    static constexpr bits true_mask  = ~bits{0};
    static constexpr bits false_mask =  bits{0};

    /// Default constructor
    EVE_FORCEINLINE constexpr logical() noexcept {}

    /// Constructor from boolean value
    EVE_FORCEINLINE constexpr logical(bool v) noexcept : value_(v ? true_mask : false_mask) {}

    /// Constructor from non-boolean value
    template<typename U> EVE_FORCEINLINE
    explicit constexpr logical(U&& v) noexcept : value_(v ? true_mask : false_mask) {}

    // Assignment operator from bool
    EVE_FORCEINLINE constexpr logical& operator=(bool v) noexcept
    {
      value_ = v ? true_mask : false_mask;
      return *this;
    }

    /// Bitwise complement operator
    EVE_FORCEINLINE constexpr logical operator ~() const noexcept { return {~value_}; }

    /// Logical not operator
    EVE_FORCEINLINE constexpr logical operator !() const noexcept { return {~value_}; }

    /// Unary + operator
    EVE_FORCEINLINE constexpr logical operator +() const noexcept { return *this; }

    /// Convert a logical value to bool
    EVE_FORCEINLINE constexpr operator bool() const noexcept { return !!value_; }

    /// Explicitly convert a logical value to bool
    EVE_FORCEINLINE constexpr bool value() const noexcept {return !!value_; }

    private:
    bits  value_;
  };

  /// Stream insertion operator
  template<typename T>
  EVE_FORCEINLINE std::ostream& operator<<(std::ostream& os, logical<T> const& v )
  {
    return os << (v.value() ? "true" : "false");
  }

  /// Equality comparison operator
  template<typename T> EVE_FORCEINLINE
  constexpr logical<T> operator ==(logical<T> const& a, logical<T> const& b) noexcept
  {
    return a.value() == b.value();
  }

  /// Inequality comparison operator
  template<typename T> EVE_FORCEINLINE
  constexpr logical<T> operator !=(logical<T> const& a, logical<T> const& b) noexcept
  {
    return a.value() != b.value();
  }

  /// Equality comparison operator
  template<typename T> EVE_FORCEINLINE
  constexpr logical<T> operator &&(logical<T> const& a, logical<T> const& b) noexcept
  {
    return a.value() && b.value();
  }

  /// Inequality comparison operator
  template<typename T> EVE_FORCEINLINE
  constexpr logical<T> operator ||(logical<T> const& a, logical<T> const& b) noexcept
  {
    return a.value() || b.value();
  }
}

#endif
