//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/concept/vectorizable.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/complex/complex.hpp>
#include <eve/module/complex/detail/arithmetic.hpp>
#include <eve/module/complex/detail/math.hpp>
#include <eve/module/complex/detail/special.hpp>
#include <eve/module/complex/detail/predicates.hpp>
#include <eve/product_type.hpp>
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

    /// Base value type
    using value_type = Type;

    /// Base value type
    using underlying_type = underlying_type_t<Type>;

    /// Default constructor
              complex()               noexcept : parent{0,0} {}
    explicit  complex(Type r        ) noexcept : parent{r,0} {}
              complex(Type r, Type i) noexcept : parent{r,i} {}

    /// Stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, like<complex> auto const& z)
    {
      os << real(z);
      auto i = imag(z);
      if(is_positive(i)) os << '+' << i; else os << '-' << -i;
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
    // Operators
    //==============================================================================================
    // -----  Operator +
    EVE_FORCEINLINE friend auto operator+(like<complex> auto const& z) noexcept { return z; }

    template<like<complex> Z1, like<complex> Z2>
    EVE_FORCEINLINE friend auto& operator+=(Z1& self, Z2 const& o) noexcept
    {
      real(self) += real(o);
      if constexpr(is_complex_v<Z2>) imag(self) += imag(o);
      return self;
    }

    EVE_FORCEINLINE friend auto& operator+=(like<complex> auto& self, callable_i_ const&) noexcept
    {
      imag(self)++;
      return self;
    }

    // -----  Operator -
    template<like<complex> Z> EVE_FORCEINLINE friend auto operator-(Z const& z) noexcept
    {
      return Z{-real(z), -imag(z)};
    }

    template<like<complex> Z1, like<complex> Z2>
    EVE_FORCEINLINE friend auto& operator-=(Z1& self, Z2 const& o) noexcept
    {
      real(self) -= real(o);
      if constexpr(is_complex_v<Z2>) imag(self) -= imag(o);
      return self;
    }

    EVE_FORCEINLINE friend auto& operator-=(like<complex> auto& self, callable_i_ const&) noexcept
    {
      imag(self)--;
      return self;
    }

    // -----  Operator *
    template<like<complex> Z1, like<complex> Z2>
    EVE_FORCEINLINE friend auto& operator*=(Z1& self, Z2 const& o) noexcept
    {
      auto [a, b] = self;
      auto c = real(o);

      if constexpr(is_complex_v<Z2>)
      {
        auto d = imag(o);
        real(self) = a*c-b*d;
        imag(self) = a*d+b*c;
      }
      else
      {
        real(self) = a*c;
        imag(self) = b*c;
      }

      return self;
    }

    EVE_FORCEINLINE friend auto& operator*=(like<complex> auto& self, callable_i_ const&) noexcept
    {
      auto[r,i] = self;
      real(self) = -i;
      imag(self) =  r;
      return self;
    }

    // -----  Operator /
    template<like<complex> Z1, like<complex> Z2>
    EVE_FORCEINLINE friend auto& operator/= (Z1& self, Z2 const& o) noexcept
    {
      auto [a, b] = self;
      auto c = real(o);

      if constexpr(is_complex_v<Z2>)
      {
        auto d = imag(o);
        auto n = c*c+d*d;
        real(self) = (a*c+b*d)/n;
        imag(self) = (b*c-a*d)/n;
      }
      else
      {
        real(self) = a/c;
        imag(self) = b/c;
      }

      return self;
    }

    EVE_FORCEINLINE friend auto& operator/=(like<complex> auto& self, callable_i_ const&) noexcept
    {
      auto[r,i] = self;
      real(self) = i;
      imag(self) = -r;
      return self;
    }

    //==============================================================================================
    // Functions support
    //==============================================================================================
    template<typename Tag, like<complex> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch(Tag const& tag, Z const& z) noexcept
        -> decltype(detail::complex_unary_dispatch(tag, z))
    {
      return detail::complex_unary_dispatch(tag, z);
    }

    template<typename Tag, decorator D, like<complex> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch(Tag const& tag, D const& d, Z const& z) noexcept
        -> decltype(detail::complex_unary_dispatch(tag, d, z))
    {
      return detail::complex_unary_dispatch(tag, d, z);
    }

    template<typename Tag, like<complex> Z1, like<complex> Z2>
    EVE_FORCEINLINE friend auto tagged_dispatch(Tag const& tag, Z1 const& z1, Z2 const& z2) noexcept
        -> decltype(detail::complex_binary_dispatch(tag, z1, z2))
    {
      return detail::complex_binary_dispatch(tag, z1, z2);
    }

    template<decorator D, typename Tag, like<complex> Z1, like<complex> Z2>
    EVE_FORCEINLINE
    friend auto tagged_dispatch(Tag const& tag, D const& d, Z1 const& z1, Z2 const& z2) noexcept
        -> decltype(detail::complex_binary_dispatch(tag, d, z1, z2))
    {
      return detail::complex_binary_dispatch(tag, d, z1, z2);
    }

    template<typename Tag, like<complex> Z1, like<complex> Z2, like<complex> Z3>
    EVE_FORCEINLINE friend auto tagged_dispatch(Tag const& tag,
                                                Z1 const & z1,
                                                Z2 const & z2,
                                                Z3 const & z3) noexcept
        -> decltype(detail::complex_ternary_dispatch(tag, z1, z2, z3))
    {
      return detail::complex_ternary_dispatch(tag, z1, z2, z3);
    }

    template<typename Tag, like<complex> Z1, like<complex>... Zs>
    EVE_FORCEINLINE
    friend auto tagged_dispatch(Tag const& tag, Z1 const& z1, Zs const&...zs) noexcept
        -> decltype(detail::complex_nary_dispatch(tag, z1, zs...))
    {
      return detail::complex_nary_dispatch(tag, z1, zs...);
    }

    //==============================================================================================
    // Constants support
    //==============================================================================================
    template<typename Tag, like<complex> Z>
    requires( !detail::one_of<Tag, tag::i_> )
    EVE_FORCEINLINE friend  auto  tagged_dispatch(Tag const&, as<Z> const&) noexcept
    {
      detail::callable_object<Tag> cst;
      if constexpr(std::same_as<Tag,tag::true__> || std::same_as<Tag,tag::false__>)
        return cst(as(real(Z{})));
      else
        return Z{ cst(as<Type>{}), Type{0}};
    }

    //==============================================================================================
    // Specific function support
    //==============================================================================================
    template<like<complex> Z, integral_value N>
    EVE_FORCEINLINE friend auto tagged_dispatch(tag::ldexp_, Z const& z1, N n) noexcept
    {
      return as_wide_as_t<Z, N>(ldexp(real(z1), n), ldexp(imag(z1), n));
    }
  };

  template<ordered_value Z>
  EVE_FORCEINLINE   auto to_complex( Z const & v) noexcept
  -> decltype(as_complex_t<Z>(v, 0))
  {
    return as_complex_t<Z>(v, 0);
  }

  template<value Z>
  EVE_FORCEINLINE auto to_complex(Z const & v) noexcept
  {
    return v;
  }

  template<value Z1, value Z2>
  EVE_FORCEINLINE auto tagged_dispatch(eve::tag::if_else_,
                                              auto const& cond,
                                              Z1 const  & z1,
                                              Z2 const  & z2) noexcept
  requires(is_complex_v<Z1> != is_complex_v<Z2>)
  {
    return if_else(cond, to_complex(z1), to_complex(z2));
  }

  //================================================================================================
  //! @}
  //================================================================================================
}
