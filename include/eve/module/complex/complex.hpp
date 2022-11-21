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
// #include <eve/module/core.hpp>
// #include <eve/module/math.hpp>
#include <eve/module/complex/regular/complex.hpp>
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

    template<decorator D, typename Tag, typename Z1, typename Z2>
    requires(like<Z1,complex> || like<Z2,complex>)
    EVE_FORCEINLINE friend  auto  tagged_dispatch ( Tag const& tag
                                                  , D const & d
                                                  , Z1 const& z1, Z2 const& z2
                                                  ) noexcept
                            ->    decltype(detail::complex_binary_dispatch(tag, d, z1, z2))
    {
      return detail::complex_binary_dispatch(tag, d, z1, z2);
    }

    template<typename Tag, typename Z1, typename Z2, typename Z3>
    requires(like<Z1,complex> || like<Z2,complex> || like<Z3,complex>)
    EVE_FORCEINLINE friend  auto  tagged_dispatch ( Tag const& tag
                                                  , Z1 const& z1, Z2 const& z2, Z3 const& z3
                                                  ) noexcept
                            ->    decltype(detail::complex_ternary_dispatch(tag, z1, z2, z3))
    {
      return detail::complex_ternary_dispatch(tag, z1, z2, z3);
    }

    template<typename Tag, typename Z1,  typename ...Zs>
    requires(like<Z1,complex> || (... || like<Zs,complex>))
    EVE_FORCEINLINE friend  auto  tagged_dispatch ( Tag const& tag
                                                  , Z1 const& z1, Zs const&... zs
                                                  ) noexcept
                            ->    decltype(detail::complex_nary_dispatch(tag, z1, zs...))
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

    template<typename R>
    EVE_FORCEINLINE friend auto& operator+=(like<complex> auto& self, R o) noexcept
    requires(like<R,Type> || std::convertible_to<R,Type>)
    {
      real(self) += o;
      return self;
    }

    template<typename Z1, typename Z2>
    EVE_FORCEINLINE friend auto operator+(Z1 const& x, Z2 const& y) noexcept
    requires(eve::like<Z1,complex> || eve::like<Z2,complex>)
    {
      return eve::add(x, y);
    }

    //==============================================================================================
    // Operator -
    //==============================================================================================
    template<like<complex> Z> EVE_FORCEINLINE friend auto operator-(Z const& z) noexcept
    {
      return Z{-real(z), -imag(z)};
    }

    EVE_FORCEINLINE friend auto& operator-= (like<complex> auto& self
                                            ,like<complex> auto const & o) noexcept
    {
      real(self) -= real(o);
      imag(self) -= imag(o);
      return self;
    }

    EVE_FORCEINLINE friend auto& operator-=(like<complex> auto& self
                                           , callable_i_ const&) noexcept
    {
      imag(self)--;
      return self;
    }

    template<typename R>
    EVE_FORCEINLINE friend auto& operator-=(like<complex> auto& self
                                           , R o) noexcept
    requires(like<R,Type> || std::convertible_to<R,Type>)
    {
      real(self) -= o;
      return self;
    }

    template<typename Z1, typename Z2>
    EVE_FORCEINLINE friend auto operator-(Z1 const& x, Z2 const& y) noexcept
    requires(eve::like<Z1,complex> || eve::like<Z2,complex>)
    {
      return eve::sub(x, y);
    }

    //==============================================================================================
    // Operator *
    //==============================================================================================
    template<like<complex> Z1, like<complex> Z2>
    EVE_FORCEINLINE friend auto& operator*= (Z1& self, Z2 const& o) noexcept
    {
      auto [a, b] = self;
      auto [c, d] = o;
      real(self) = a*c-b*d;
      imag(self) = a*d+b*c;
    return self;
    }

    EVE_FORCEINLINE friend auto& operator*=(like<complex> auto& self, callable_i_ const&) noexcept
    {
      auto[r,i] = self;
      real(self) = -i;
      imag(self) =  r;
      return self;
    }

    template<typename R>
    EVE_FORCEINLINE friend auto& operator*=(like<complex> auto& self, R o) noexcept
    requires(like<R,Type> || std::convertible_to<R,Type>)
    {
      real(self) *= o;
      imag(self) *= o;
      return self;
    }

    template<typename Z1, typename Z2>
    EVE_FORCEINLINE friend auto operator*(Z1 const& x, Z2 const& y) noexcept
    requires(eve::like<Z1,complex> || eve::like<Z2,complex>)
    {
      return eve::mul(x, y);
    }

//     template<like<complex> Z1, like<complex> Z2>
//     friend auto
//     tagged_dispatch(eve::tag::add_, pedantic_type const &, Z1 const& z1, Z2  const& z2) noexcept
//     {
//       return z1+z2;
//    }

//     template<like<complex> Z1, like<complex> Z2>
//     EVE_FORCEINLINE friend auto
//     tagged_dispatch(eve::tag::mul_, raw_type const&, Z1 const& z1, Z2 const& z2) noexcept
//     {
//       using Z   = decltype(z1*z2);
//       auto [a, b] = z1;
//       auto [c, d] = z2;
//       return Z {raw(diff_of_prod)(a, c, b, d), raw(sum_of_prod)(a, d, b, c)};
//     }

    //==============================================================================================
    // Operator /
    //==============================================================================================
    template<like<complex> Z1, like<complex> Z2>
    EVE_FORCEINLINE friend auto& operator/= (Z1& self, Z2 const& o) noexcept
    {
      return self *= conj(o)*rec(sqr_abs(o));
    }

    EVE_FORCEINLINE friend auto& operator/=(like<complex> auto& self, callable_i_ const&) noexcept
    {
      auto[r,i] = self;
      real(self) = i;
      imag(self) = -r;
      return self;
    }

    template<typename R>
    EVE_FORCEINLINE friend auto& operator/=(like<complex> auto& self, R o) noexcept
    requires(like<R,Type> || std::convertible_to<R,Type>)
    {
      auto invo = rec(o);
      real(self) *= invo;
      imag(self) *= invo;
      return self;
    }

    template<typename Z1, typename Z2>
    EVE_FORCEINLINE friend auto operator/(Z1 const& x, Z2 const& y) noexcept
    requires(eve::like<Z1,complex> || eve::like<Z2,complex>)
    {
      return eve::div(x, y);
    }

  };

  template<typename Z>
  EVE_FORCEINLINE   auto to_complex( Z const & v) noexcept
  requires (real_value<Z>)
  {
    return as_complex_t<Z>(v, 0);
  }

  template<typename Z>
  EVE_FORCEINLINE   auto to_complex(Z const & v) noexcept
  requires (eve::is_complex_v<Z>)
  {
    return v;
  }
}
