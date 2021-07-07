//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/concepts.hpp>
#include <eve/traits/support.hpp>

namespace eve
{
  template<std::floating_point T>
  struct complex : additive<complex<T>>, comparable<complex<T>>
  {
    using value_type      = T;
    using is_product_type = void;

    constexpr complex(T r = {}, T i = {}) : real_{r}, imag_{i} {}

    template<same_value_type<complex> V, same_value_type<complex> U>
    friend constexpr V& operator*=(V& self, U other) noexcept
    {
      auto r0 = real(self);
      auto r1 = real(other);
      auto i0 = imag(self);
      auto i1 = imag(other);

      real(self) = r0*r1 - i0*i1;
      imag(self) = r0*i1 + r1*i0;

      return self;
    }

    template<same_value_type<complex> V, same_value_type<T> U>
    friend constexpr V& operator*=(V& self, U other) noexcept
    {
      real(self) *= other;
      imag(self) *= other;

      return self;
    }

    template<same_value_type<complex> V>
    friend constexpr decltype(auto) real(V&& z) noexcept
    {
      return eve::content<0>(std::forward<V>(z));
    }

    template<same_value_type<complex> V>
    friend constexpr decltype(auto) imag(V&& z) noexcept
    {
      return eve::content<1>(std::forward<V>(z));
    }

    template<same_value_type<complex> Z>
    friend std::ostream& operator<<( std::ostream& os, Z const& z)
    {
      return os << real(z) << " + i*" << imag(z);
    }

    T real_;
    T imag_;
  };

  template<std::size_t I, typename T> constexpr T& get( complex<T>& c) noexcept
  {
    if constexpr(I==0) return c.real_;
    if constexpr(I==1) return c.imag_;
  }

  template<std::size_t I, typename T> constexpr T get( complex<T> const& c) noexcept
  {
    if constexpr(I==0) return c.real_;
    if constexpr(I==1) return c.imag_;
  }
}

namespace std
{
  template<std::size_t I, typename T>
  struct tuple_element<I, eve::complex<T>> { using type = T; };

  template<typename T>
  struct tuple_size<eve::complex<T>> : std::integral_constant<std::size_t, 2> {};
}

