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
#include <eve/module/complex.hpp>
#include <eve/module/quaternion/regular/traits.hpp>
#include <eve/module/quaternion/detail/arithmetic.hpp>
#include <eve/module/quaternion/detail/math.hpp>
#include <eve/module/quaternion/detail/predicates.hpp>
#include <eve/traits/product_type.hpp>
#include <ostream>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //================================================================================================
  //! @brief SIMD-compatible representation of complex numbers
  //!
  //! **Required header:** `#include <eve/module/quaternion.hpp>`
  //!
  //! eve::quaternion is structure representing quaternion number and is meant to be used in
  //! conjunction with eve::wide.
  //!
  //! @tparam Type  Underlying floating point type
  //================================================================================================
  template<floating_scalar_value Type>
  struct quaternion : struct_support<quaternion<Type>, Type, Type, Type, Type>
  {
    using eve_disable_ordering  = void;
    using parent                = struct_support<quaternion<Type>, Type, Type, Type, Type>;
    using c_t = eve::complex<Type>;
    using q_t = eve::quaternion<Type>;

    /// Base value type
    using value_type = Type;

    /// Base value type
    using underlying_type = underlying_type_t<Type>;

    /// Default constructor
              quaternion(                              ) noexcept : parent{0,0,0,0} {}
    explicit  quaternion(Type r                        ) noexcept : parent{r,0,0,0} {}
              quaternion(Type r, Type i, Type j, Type k) noexcept : parent{r,i,j,k} {}
              quaternion(c_t r0, c_t r1                ) noexcept : parent{real(r0), imag(r0), real(r1), imag(r1)} {}

    /// Stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, like<quaternion> auto const& z)
    {
      os << real(z);
      auto i = ipart(z);
      auto j = jpart(z);
      auto k = kpart(z);
      if(is_positive(i)){ os << '+' << i;} else {os << '-' << -i; };  os << "i";
      if(is_positive(j)){ os << '+' << j;} else {os << '-' << -j; };  os << "j";
      if(is_positive(k)){ os << '+' << k;} else {os << '-' << -k; };  os << "k";
      return os;
    }

    //==============================================================================================
    //  Real/part Access
    //==============================================================================================
    EVE_FORCEINLINE friend decltype(auto) tagged_dispatch(eve::tag::real_, like<quaternion> auto&& z)
    {
      return get<0>(EVE_FWD(z));
    }

    EVE_FORCEINLINE friend decltype(auto) tagged_dispatch(eve::tag::ipart_, like<quaternion> auto && z)
    {
      return get<1>(EVE_FWD(z));
    }

    EVE_FORCEINLINE friend decltype(auto) tagged_dispatch(eve::tag::jpart_, like<quaternion> auto && z)
    {
      return get<2>(EVE_FWD(z));
    }

    EVE_FORCEINLINE friend decltype(auto) tagged_dispatch(eve::tag::kpart_, like<quaternion> auto && z)
    {
      return get<3>(EVE_FWD(z));
    }

    EVE_FORCEINLINE friend decltype(auto) tagged_dispatch(eve::tag::pure_, like<quaternion> auto && z )
    {
      using u_t =  std::remove_reference_t<decltype(real(z))>;
      auto z1 = z;
      real(z1) = u_t(0);
      return z1;
    }

    //==============================================================================================
    // Operators
    //==============================================================================================
    // -----  Operator +
    EVE_FORCEINLINE friend auto operator+(like<quaternion> auto const& z) noexcept { return z; }

    template<like<quaternion> Z1, like<quaternion> Z2>
    EVE_FORCEINLINE friend auto& operator+=(Z1& self, Z2 const& o) noexcept
    {
      real(self) += real(o);
      if constexpr(is_quaternion_v<Z2>)
      {
        ipart(self) += ipart(o);
        jpart(self) += jpart(o);
        kpart(self) += kpart(o);
      }
      return self;
    }

    EVE_FORCEINLINE friend auto& operator+=(like<quaternion> auto& self, callable_i_ const&) noexcept
    {
      ipart(self)++;
      return self;
    }

    // -----  Operator -
    template<like<quaternion> Z> EVE_FORCEINLINE friend auto operator-(Z const& z) noexcept
    {
      return Z{-real(z),-ipart(z),-jpart(z),-kpart(z)};
    }

    template<like<quaternion> Z1, like<quaternion> Z2>
    EVE_FORCEINLINE friend auto& operator-=(Z1& self, Z2 const& o) noexcept
    {
      real(self) -= real(o);
      if constexpr(is_quaternion_v<Z2>)
      {
        ipart(self) -= ipart(o);
        jpart(self) -= jpart(o);
        kpart(self) -= kpart(o);
      }
      return self;
    }

    EVE_FORCEINLINE friend auto& operator-=(like<quaternion> auto& self, callable_i_ const&) noexcept
    {
      ipart(self)--;
      return self;
    }

    // -----  Operator *
    template<like<quaternion> Z1, like<quaternion> Z2>
    EVE_FORCEINLINE friend auto& operator*=(Z1& self, Z2 const& e) noexcept
    {
      auto [a, b, c, d] = self;
      if constexpr(is_complex_v<Z2>)
      {
        auto [ae, be] = e;
        real(self)  = a*ae - b*be;
        ipart(self) = a*be + b*ae;
        jpart(self) = c*ae + d*be;
        kpart(self) = d*ae - c*be;
      }
      else if constexpr(is_quaternion_v<Z2>)
      {
        auto [ae, be, ce, de] = e;
        real(self)  = a*ae - b*be - c*ce - d*de;
        ipart(self) = a*be + b*ae + c*de - d*ce;
        jpart(self) = a*ce - b*de + c*ae + d*be;
        kpart(self) = a*de + b*ce - c*be + d*ae;
      }
      else
      {
        real(self)  = a*e;
        ipart(self) = b*e;
        jpart(self) = c*e;
        kpart(self) = d*e;
      }
      return self;
    }

    EVE_FORCEINLINE friend auto& operator*=(like<quaternion> auto& self, callable_i_ const&) noexcept
    {
      auto[a, b, c, d] = self;
      real(self)  = -b;
      ipart(self) = a;
      jpart(self) = d;
      kpart(self) = -c;
      return self;
    }

    // -----  Operator /
    template<like<quaternion> Z1, like<quaternion> Z2>
    EVE_FORCEINLINE friend auto& operator/= (Z1& self, Z2 const& o) noexcept
    {
      self = self*conj(o);
      self = self*rec(sqr_abs(o));
      return self; //*= conj(o)*rec(sqr_abs(o));
    }

    EVE_FORCEINLINE friend auto& operator/=(like<quaternion> auto& self, callable_i_ const&) noexcept
    {
      auto[a, b, c, d] = self;
      real(self)  = b;
      ipart(self) = -a;
      jpart(self) = -d;
      kpart(self) = c;
      return self;
    }

    //==============================================================================================
    // Functions support
    //==============================================================================================
    template<typename Tag, like<quaternion> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch(Tag const& tag, Z const& z) noexcept
        -> decltype(detail::quaternion_unary_dispatch(tag, z))
    {
      return detail::quaternion_unary_dispatch(tag, z);
    }

//     template<typename Tag, decorator D, like<quaternion> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch(Tag const& tag, D const& d, Z const& z) noexcept
//         -> decltype(detail::quaternion_unary_dispatch(tag, d, z))
//     {
//       return detail::quaternion_unary_dispatch(tag, d, z);
//     }

    template<typename Tag, like<quaternion> Z1, like<quaternion> Z2>
    EVE_FORCEINLINE friend auto tagged_dispatch(Tag const& tag, Z1 const& z1, Z2 const& z2) noexcept
        -> decltype(detail::quaternion_binary_dispatch(tag, z1, z2))
    {
      return detail::quaternion_binary_dispatch(tag, z1, z2);
    }

//     template<decorator D, typename Tag, like<quaternion> Z1, like<quaternion> Z2>
//     EVE_FORCEINLINE
//     friend auto tagged_dispatch(Tag const& tag, D const& d, Z1 const& z1, Z2 const& z2) noexcept
//         -> decltype(detail::quaternion_binary_dispatch(tag, d, z1, z2))
//     {
//       return detail::quaternion_binary_dispatch(tag, d, z1, z2);
//     }

    template<typename Tag, like<quaternion> Z1, like<quaternion> Z2, like<quaternion> Z3>
    EVE_FORCEINLINE friend auto tagged_dispatch(Tag const& tag,
                                                Z1 const & z1,
                                                Z2 const & z2,
                                                Z3 const & z3) noexcept
        -> decltype(detail::quaternion_ternary_dispatch(tag, z1, z2, z3))
    {
      return detail::quaternion_ternary_dispatch(tag, z1, z2, z3);
    }

    template<typename Tag, like<quaternion> Z1, like<quaternion>... Zs>
    EVE_FORCEINLINE
    friend auto tagged_dispatch(Tag const& tag, Z1 const& z1, Zs const&...zs) noexcept
        -> decltype(detail::quaternion_nary_dispatch(tag, z1, zs...))
    {
      return detail::quaternion_nary_dispatch(tag, z1, zs...);
    }

    //==============================================================================================
    // Constants support
    //==============================================================================================
    template<typename Tag, like<quaternion> Z>
    requires( !detail::one_of<Tag, tag::i_> )
    EVE_FORCEINLINE friend  auto  tagged_dispatch(Tag const&, as<Z> const&) noexcept
    {
      detail::callable_object<Tag> cst;
      if constexpr(std::same_as<Tag,tag::true__> || std::same_as<Tag,tag::false__>)
        return cst(as(real(Z{})));
      else
        return Z{ cst(as<Type>{}), Type{0}, Type{0}, Type{0}};
    }
  };

  template<ordered_value Z>
  EVE_FORCEINLINE   auto to_quaternion( Z const & v) noexcept
  -> decltype(as_quaternion_t<Z>(v, 0, 0, 0))
  {
    return as_quaternion_t<Z>(v, 0, 0, 0);
  }

  template<value Z>
  EVE_FORCEINLINE auto to_quaternion(Z const & v) noexcept
  {
    return v;
  }

  template<value Z1, value Z2>
  EVE_FORCEINLINE auto tagged_dispatch(eve::tag::if_else_,
                                              auto const& cond,
                                              Z1 const  & z1,
                                              Z2 const  & z2) noexcept
  requires(is_quaternion_v<Z1> != is_quaternion_v<Z2>)
  {
    return if_else(cond, to_quaternion(z1), to_quaternion(z2));
  }

  //================================================================================================
  //! @}
  //================================================================================================
}
