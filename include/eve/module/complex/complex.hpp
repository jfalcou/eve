//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/vectorizable.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/complex/regular/complex.hpp>
#include <eve/module/complex/regular/detail/arithmetic.hpp>
#include <eve/module/complex/regular/detail/math.hpp>
#include <eve/module/complex/regular/detail/predicates.hpp>
#include <eve/product_type.hpp>
#include "eve/module/core/constant/one.hpp"
#include <ostream>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //================================================================================================
  //! @brief SIMD-compatible representation of complex numbers
  //!
  //! **Required header:** `#include <eve/module/complex.hpp>`
  //!
  //! eve::complex is structure representing complex number and is meant to be used in
  //! conjunction with eve::wide.
  //!
  //! @tparam Type  Underlying floating point type
  //================================================================================================
  template<floating_scalar_value Type>
  struct complex : struct_support<complex<Type>, Type, Type>
  {
    using eve_disable_ordering  = void;
    using parent                = struct_support<complex<Type>, Type, Type>;

    /// Underlying type
    using value_type = Type;

    /// Default constructor
    explicit  complex(Type r = 0)     noexcept : parent{r,0} {}
              complex(Type r, Type i) noexcept : parent{r,i} {}

    /// Stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, like<complex> auto const& z)
    {
      os << real(z);
      auto i = imag(z);
      if(i >= 0) os << '+' << i; else os << '-' << -i;
      return os << 'i';
    }

    //==============================================================================================
    //  Real/Imag Access
    //==============================================================================================
    EVE_FORCEINLINE friend decltype(auto) tagged_dispatch(eve::tag::real_, like<complex> auto&& z)
    {
      return get<0>(EVE_FWD(z));
    }

    EVE_FORCEINLINE friend decltype(auto) tagged_dispatch(eve::tag::imag_, like<complex> auto && z)
    {
      return get<1>(EVE_FWD(z));
    }

    //==============================================================================================
    // Functions support
    //==============================================================================================
    template<typename Tag, like<complex> Z>
    EVE_FORCEINLINE friend  auto  tagged_dispatch(Tag const& tag, Z const& z) noexcept
                            ->    decltype(detail::complex_unary_dispatch(tag, z))
    {
      return detail::complex_unary_dispatch(tag, z);
    }

    template<typename Tag, decorator D, like<complex> Z>
    EVE_FORCEINLINE friend  auto  tagged_dispatch(Tag const& tag, D const& d, Z const& z) noexcept
                            ->    decltype(detail::complex_unary_dispatch(tag, d, z))
    {
      return detail::complex_unary_dispatch(tag, d, z);
    }

    template<typename Tag, typename Z1, typename Z2>
    requires(like<Z1,complex> || like<Z2,complex>)
    EVE_FORCEINLINE friend  auto  tagged_dispatch ( Tag const& tag
                                                  , Z1 const& z1, Z2 const& z2
                                                  ) noexcept
                            ->    decltype(detail::complex_binary_dispatch(tag, z1, z2))
    {
      return detail::complex_binary_dispatch(tag, z1, z2);
    }

    //==============================================================================================
    // Operator +
    //==============================================================================================
    EVE_FORCEINLINE friend auto operator+(like<complex> auto const& z) noexcept { return z; }

    template<like<complex> Z1, like<complex> Z2>
    EVE_FORCEINLINE friend auto& operator+= (Z1& self, Z2 const& o) noexcept
    {
      real(self) += real(o);
      imag(self) += imag(o);
      return self;
    }

    EVE_FORCEINLINE friend auto& operator+=(like<complex> auto& self, callable_i_ const&) noexcept
    {
      imag(self)++;
      return self;
    }

    template<typename Z>
    EVE_FORCEINLINE friend auto& operator+=(like<complex> auto& self, Z o) noexcept
    requires(like<Z,Type> || std::convertible_to<Z,Type>)
    {
      real(self) += o;
      return self;
    }

    template<like<complex> Z1, real_value Z2>
    EVE_FORCEINLINE friend  auto operator+(Z1 const& x, Z2 const& y) noexcept
    requires(requires(as_wide_as_t<Z1,Z2> t) { t += y; })
    {
      as_wide_as_t<Z1,Z2> that{x};
      return that += y;
    }

    template<real_value Z1, like<complex> Z2>
    EVE_FORCEINLINE friend  auto operator+(Z1 const& x, Z2 const& y) noexcept
    requires(requires(as_wide_as_t<Z2,Z1> t) { t += x; })
    {
      return y + x;
    }

    //==============================================================================================
    // Operator -
    //==============================================================================================
    template<like<complex> Z> EVE_FORCEINLINE friend auto operator-(Z const& z) noexcept
    {
      return Z{-real(z), -imag(z)};
    }

    template<like<complex> Z1, like<complex> Z2>
    EVE_FORCEINLINE friend auto& operator-= (Z1& self, Z2 const& o) noexcept
    {
      real(self) -= real(o);
      imag(self) -= imag(o);
      return self;
    }

    EVE_FORCEINLINE friend auto& operator-=(like<complex> auto& self, callable_i_ const&) noexcept
    {
      imag(self)--;
        return self;
    }

    template<typename Z>
    EVE_FORCEINLINE friend auto& operator-=(like<complex> auto& self, Z o) noexcept
    requires(like<Z,Type> || std::convertible_to<Z,Type>)
    {
      real(self) -= o;
      return self;
    }

    template<like<complex> Z1, real_value Z2>
    EVE_FORCEINLINE friend  auto operator-(Z1 const& x, Z2 const& y) noexcept
    requires(requires(as_wide_as_t<Z1,Z2> t) { t -= y; })
    {
      as_wide_as_t<Z1,Z2> that(x);
      return that -= y;
    }

    template<real_value Z1, like<complex> Z2>
    EVE_FORCEINLINE friend  auto operator-(Z1 const& x, Z2 const& y) noexcept
    requires(requires(as_wide_as_t<Z2,Z1> t) { t -= y; })
    {
      as_wide_as_t<Z2,Z1> that(x,0);
      return that -= y;
    }

    //==============================================================================================
    // Operator *
    //==============================================================================================
    template<like<complex> Z1, like<complex> Z2>
    EVE_FORCEINLINE friend auto& operator*= (Z1& self, Z2 const& o) noexcept
    {
      auto [a, b] = self;
      auto [c, d] = o;
      real(self) = diff_of_prod(a, c, b, d);
      imag(self) = sum_of_prod(a, d, b, c);
      return self;
    }

    EVE_FORCEINLINE friend auto& operator*=(like<complex> auto& self, callable_i_ const&) noexcept
    {
      auto[r,i] = self;
      real(self) = -i;
      imag(self) =  r;
      return self;
    }

    template<typename Z>
    EVE_FORCEINLINE friend auto& operator*=(like<complex> auto& self, Z o) noexcept
    requires(like<Z,Type> || std::convertible_to<Z,Type>)
    {
      real(self) *= o;
      imag(self) *= o;
      return self;
    }

    template<like<complex> Z1, real_value Z2>
    EVE_FORCEINLINE friend  auto operator*(Z1 const& x, Z2 const& y) noexcept
    requires(requires(as_wide_as_t<Z1,Z2> t) { t *= y; })
    {
      as_wide_as_t<Z1,Z2> that(x);
      return that *= y;
    }

    template<real_value Z1, like<complex> Z2>
    EVE_FORCEINLINE friend  auto operator*(Z1 const& x, Z2 const& y) noexcept
    requires(requires(as_wide_as_t<Z2,Z1> t) { t *= y; })
    {
      as_wide_as_t<Z2,Z1> that(x,0);
      return that *= y;
    }

    //==============================================================================================
    // Operator /
    //==============================================================================================
    template<like<complex> Z1, like<complex> Z2>
    EVE_FORCEINLINE friend auto& operator/= (Z1& self, Z2 const& o) noexcept
    {
      auto rr =  eve::abs(real(self));
      auto ii =  eve::abs(imag(self));
      auto e  = -if_else((rr < ii), exponent(ii), exponent(rr));
      auto oo(eve::ldexp(o, e));
      auto denom =  sqr_abs(oo);
      self *= conj(oo);
      self /= denom;
      self = ldexp(self, e);
      return self;
    }

    EVE_FORCEINLINE friend auto& operator/=(like<complex> auto& self, callable_i_ const&) noexcept
    {
      auto[r,i] = self;
      real(self) = i;
      imag(self) = -r;
      return self;
    }

    template<typename Z>
    EVE_FORCEINLINE friend auto& operator/=(like<complex> auto& self, Z o) noexcept
    requires(like<Z,Type> || std::convertible_to<Z,Type>)
    {
      real(self) /= o;
      imag(self) /= o;
      return self;
    }

    template<like<complex> Z1, real_value Z2>
    EVE_FORCEINLINE friend  auto operator/(Z1 const& x, Z2 const& y) noexcept
    requires(requires(as_wide_as_t<Z1,Z2> t) { t /= y; })
    {
      as_wide_as_t<Z1,Z2> that(x);
      return that /= y;
    }

    template<real_value Z1, like<complex> Z2>
    EVE_FORCEINLINE friend  auto operator/(Z1 const& x, Z2 const& y) noexcept
    requires(requires(as_wide_as_t<Z2,Z1> t) { t /= y; })
    {
      auto[r,i] = y;
      auto m = x/(r*r+i*i);
      return as_wide_as_t<Z2,Z1>(m*r,-m*i);
    }
  };
}
