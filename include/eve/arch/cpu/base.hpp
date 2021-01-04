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

#include <eve/concept/vectorizable.hpp>
#include <eve/detail/function/slice.hpp>
#include <eve/detail/function/subscript.hpp>

namespace eve::detail
{
  template<typename Size> struct wide_cardinal
  {
    using cardinal_type = Size;
    using size_type     = std::ptrdiff_t;

    static constexpr size_type  static_size  = Size::value;

    static EVE_FORCEINLINE constexpr size_type size()     noexcept { return static_size; }
    static EVE_FORCEINLINE constexpr size_type max_size() noexcept { return static_size; }
    static EVE_FORCEINLINE constexpr bool      empty()    noexcept { return false; }
  };

  template<typename Derived> struct wide_ops
  {
    EVE_FORCEINLINE auto slice() const requires(Derived::size() > 1)
    {
      return detail::slice(self());
    }

    EVE_FORCEINLINE auto slice(auto s) const requires(Derived::size() > 1)
    {
      return detail::slice(self(), s);
    }

    EVE_FORCEINLINE void set(std::size_t i, scalar_value auto v) noexcept
    {
      detail::insert(self(), i, v);
    }

    EVE_FORCEINLINE auto operator[](std::size_t i) const noexcept
    {
      return detail::extract(self(), i);
    }

    EVE_FORCEINLINE auto back()  const noexcept { return (*this)[Derived::size()-1]; }
    EVE_FORCEINLINE auto front() const noexcept { return (*this)[0]; }

    private:
    EVE_FORCEINLINE Derived&        self()        { return static_cast<Derived&>(*this); }
    EVE_FORCEINLINE Derived const&  self() const  { return static_cast<Derived const&>(*this); }
  };
}
