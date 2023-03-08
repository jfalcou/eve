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
#include <eve/module/core.hpp>
#include <eve/module/dd/dd.hpp>
#include <eve/module/dd/detail/utilities.hpp>
#include <eve/module/dd/detail/constants.hpp>
#include <eve/module/dd/detail/arithmetic.hpp>
#include <eve/module/dd/detail/math.hpp>
#include <eve/module/dd/detail/predicates.hpp>
#include <eve/traits/product_type.hpp>
#include <ostream>
#include <iomanip>
#include <boost/multiprecision/cpp_bin_float.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //================================================================================================
  //! @brief SIMD-compatible representation of dd numbers (i.e pair of floating scalars)
  //!
  //! **Required header:** `#include <eve/module/dd.hpp>`
  //!
  //! eve::dd is structure representing dd number and is meant to be used in
  //! conjunction with eve::wide.
  //!
  //! @tparam Type  Underlying floating point type
  //================================================================================================

  template<ordered_value Z>
  EVE_FORCEINLINE  auto to_double( Z const& z) noexcept
  requires(is_dd_v<Z>)
  {
    auto [h, l] = z;
    return float64(h)+float64(l);
  }

  template<ordered_value Z>
  EVE_FORCEINLINE  auto to_float128( Z const& z) noexcept
  requires(is_dd_v<Z>)
  {
    auto [h, l] = z;
    return  boost::multiprecision::cpp_bin_float_quad(h)+
            boost::multiprecision::cpp_bin_float_quad(l);
  }

  template<floating_scalar_value Type>
  struct dd : struct_support<dd<Type>, Type, Type>
  {
    using parent                = struct_support<dd<Type>, Type, Type>;

    /// Base  type
    using real_type = Type;

    /// Base underlyng type
    using underlying_type = underlying_type_t<Type>;

    /// Default constructor
              dd()               noexcept : parent{0,0} {}
    explicit  dd(Type h        ) noexcept : parent{h,0} {}
              dd(Type a, Type b) noexcept : parent{a,0}
    {

       *this += b; //ensures a two_add call to normalize high and low parts //TODO for simd
                   //this is guaranted to be commutative ie dd(a, b) is identical to dd(b, a)
    }

    dd(const char * s) noexcept : parent{0,0}
    {
      *this = read(s);
    }

    template <ordered_value T> // construction from a scalar of different type
    dd(T t)
    requires(!std::same_as<T, underlying_type> && plain_scalar_value<T>)
    {
      using u_t =  underlying_type;
      u_t h(t);
      auto self = two_add(h, u_t(t-T(h)));
      get<0>(*this) = get<0>(self);
      get<1>(*this) = get<1>(self);
    }

    /// Stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, like<dd> auto const& r)
    {
      auto h = high(r);
      auto l = low(r);
//      os << '(' << h << ')';
//      if(is_positive(l)) os << "+(" << l << ')'; else os << "-(" << -l << ')';
      os << std::hexfloat <<  "dd_t(" << h << ", " << l << ')';
      return os;
    }

    //==============================================================================================
    // Functions support
    //==============================================================================================
    template<typename Tag, like<dd> Z>
    EVE_FORCEINLINE friend auto tagged_dispatch(Tag const& tag, Z const& z) noexcept
        -> decltype(detail::dd_unary_dispatch(tag, z))
    {
      return detail::dd_unary_dispatch(tag, z);
    }

//     template<typename Tag, decorator D, like<dd> Z>
//     EVE_FORCEINLINE friend auto tagged_dispatch(Tag const& tag, D const& d, Z const& z) noexcept
//         -> decltype(detail::dd_unary_dispatch(tag, d, z))
//     {
//       return detail::dd_unary_dispatch(tag, d, z);
//     }

    template<typename Tag, like<dd> Z1, like<dd> Z2>
    EVE_FORCEINLINE friend auto tagged_dispatch(Tag const& tag, Z1 const& z1, Z2 const& z2) noexcept
        -> decltype(detail::dd_binary_dispatch(tag, z1, z2))
    {
      return detail::dd_binary_dispatch(tag, z1, z2);
    }

    template<typename Tag, like<dd> Z1, integral_value N>
    EVE_FORCEINLINE friend auto tagged_dispatch(Tag const& tag, Z1 const& z1, N const& n) noexcept
        -> decltype(detail::dd_n_binary_dispatch(tag, z1, n))
    {
      return detail::dd_n_binary_dispatch(tag, z1, n);
    }

//     template<decorator D, typename Tag, like<dd> Z1, like<dd> Z2>
//     EVE_FORCEINLINE
//     friend auto tagged_dispatch(Tag const& tag, D const& d, Z1 const& z1, Z2 const& z2) noexcept
//         -> decltype(detail::dd_binary_dispatch(tag, d, z1, z2))
//     {
//       return detail::dd_binary_dispatch(tag, d, z1, z2);
//     }

//     template<typename Tag, like<dd> Z1, like<dd> Z2, like<dd> Z3>
//     EVE_FORCEINLINE friend auto tagged_dispatch(Tag const& tag,
//                                                 Z1 const & z1,
//                                                 Z2 const & z2,
//                                                 Z3 const & z3) noexcept
//         -> decltype(detail::dd_ternary_dispatch(tag, z1, z2, z3))
//     {
//       return detail::dd_ternary_dispatch(tag, z1, z2, z3);
//     }

    template<typename Tag, like<dd> Z1, like<dd>... Zs>
    EVE_FORCEINLINE
    friend auto tagged_dispatch(Tag const& tag
                               , Z1 const& z1, Zs const&...zs) noexcept
        -> decltype(detail::dd_nary_dispatch(tag, z1, zs...))
    {
      return detail::dd_nary_dispatch(tag, z1, zs...);
    }

    template<decorator D, typename Tag, like<dd> Z1, like<dd>... Zs>
    EVE_FORCEINLINE
    friend auto tagged_dispatch(Tag const& tag, D const& d
                               , Z1 const& z1, Zs const&...zs) noexcept
        -> decltype(detail::dd_nary_dispatch(tag, d, z1, zs...))
    {
      return detail::dd_nary_dispatch(tag, d, z1, zs...);
    }

    //==============================================================================================
    // Constants support
    //==============================================================================================
    template<typename Tag, like<dd> Z>
    EVE_FORCEINLINE friend  auto  tagged_dispatch(Tag const& tag, as<Z> const&) noexcept
    {
      detail::callable_object<Tag> cst;
      if constexpr(std::same_as<Tag,tag::true__> || std::same_as<Tag,tag::false__>)
        return cst(as(high(Z{})));
      else
        return detail::dd_cts_dispatch(tag, as(Z()));//Z{ cst(as<Type>{}), Type{0}};
    }

    //==============================================================================================
    //  high/low Access
    //==============================================================================================
    EVE_FORCEINLINE friend decltype(auto) tagged_dispatch(eve::tag::high_, like<dd> auto&& z)
    {
      return get<0>(EVE_FWD(z));
    }

    EVE_FORCEINLINE friend decltype(auto) tagged_dispatch(eve::tag::low_, like<dd> auto && z)
    {
      return get<1>(EVE_FWD(z));
    }

    //==============================================================================================
    // Operators
    //==============================================================================================
    // -----  Operator +
    EVE_FORCEINLINE friend auto operator+(like<dd> auto const& z) noexcept { return z; }

    template<like<dd> Z1, like<dd> Z2>
    EVE_FORCEINLINE friend auto& operator+=(Z1& self, Z2 const& o) noexcept
    {
      if constexpr(std::same_as<underlying_type_t<Z1>, underlying_type_t<Z2>>)
      {
        auto & [x0, x1] = self;
        using e_t = decltype(x0);
        auto   [z0, s2] = two_add(x0, e_t(high(o)));
        x0 = z0;
        auto finitex0 = is_finite(x0);
        if (eve::none(finitex0)) x1 = zero(as(x1));
        else
        {
          auto [t1, t2] = two_add( x1, e_t(low(o)));
          auto [t3, t4] = two_add(s2, t1);
          x1 = t3;
          t4 += t2;
          kumi::tie(x0, x1, t4) = three_add(x0, x1, t4);
          x1 = if_else(finitex0, x1, zero);
        }
        return self;
      }
      else //o is scalar here
      {
        return self += make_dd(o, as<Z1>());
      }
    }



    // -----  Operator -=
    template<like<dd> Z> EVE_FORCEINLINE friend auto operator-(Z const& z) noexcept
    {
      return Z{-high(z), -low(z)};
    }

    template<like<dd> Z1, like<dd> Z2>
    EVE_FORCEINLINE friend auto& operator-=(Z1& self, Z2 const& o) noexcept
    {
      return self +=  -o;
    }

    // -----  Operator *=
    template<like<dd> Z1, like<dd> Z2>
    EVE_FORCEINLINE friend auto& operator*=(Z1& self, Z2 const& o) noexcept
    {
      if constexpr(std::same_as<underlying_type_t<Z1>, underlying_type_t<Z2>>)
      {
        auto & [x0, x1] = self;
        using e_t = decltype(x0);
        auto ohi = e_t(high(o));
        auto [p0, p1] = two_prod(x0, ohi);
        auto finitex0 = is_finite(x0);
        if (eve::none(finitex0)){
          x0 = p0;
          x1 = zero(as(x1));
        }
        else
        {
          auto olo = e_t(low(o));
          auto [p2, p4] = two_prod(x0, olo);
          auto [p3, p5] = two_prod(x1, ohi);
          auto p6 = x1*olo;
          kumi::tie(p1, p2, p3) = three_add(p1, p2, p3);
          p2 += p4 + p5 + p6;
          kumi::tie(p0, p1, p2) = three_add(p0, p1, p2);
          x0 = p0;
          x1 = p1;
        }
        return self;
      }
      else // o is scalar here
      {
        return self *= make_dd(o, as<Z1>());
      }
    }

    // -----  Operator /=
    template<like<dd> Z1, like<dd> Z2>
    EVE_FORCEINLINE friend auto& operator/=(Z1& self, Z2 const& o) noexcept
    {
      if constexpr(std::same_as<underlying_type_t<Z1>, underlying_type_t<Z2>> )
      {
        Z1 r(eve::rec(o));
        Z1 x(r);
        x += r*oneminus(o*r); //newton inverse of o
        return self *= x;
      }
      else // o is scalar here
      {
        return self /= make_dd(o, as<Z1>());
      }
    }

  private :

    // Reads in a dd from a string. */
    static dd read(const char *s) //TO DO rewrite it !
    {
      const char *p = s;
      char ch;
      int sign = 0;
      int point = -1;
      int nd = 0;
      int e = 0;
      bool done = false;
      dd r{};
      int nread;

      /* Skip any leading spaces */
      while (*p == ' ')  p++;
      while (!done && (ch = *p) != '\0') {
        if (ch >= '0' && ch <= '9') {
          Type d = ch - '0';
          r += d;
          r *= 10.0;
          nd++;
        } else {

          switch (ch) {

          case '.':
            if (point >= 0)
              return -1;
            point = nd;
            break;

          case '-':
          case '+':
            if (sign != 0 || nd > 0)
              return -1;
            sign = (ch == '-') ? -1 : 1;
            break;

          case 'E':
          case 'e':
            nread = std::sscanf(p+1, "%d", &e);
            done = true;
            if (nread != 1)
              return -1;
            break;

          default:
            return -1;
          }
        }

        p++;
      }
      --e;
      if (point >= 0) {
        e -= (nd - point);
      }

      if (e != 0) {
        r *= pow(10.0, e);
      }
      return (sign == -1) ? -r : r;
    }

  };

  template<typename Z, integral_value N>
  EVE_FORCEINLINE auto dd_n_binary_dispatch(tag::ldexp_, Z const& z1, N n) noexcept
  {
    return as_wide_as_t<Z, N>(ldexp(high(z1), n), ldexp(low(z1), n));
  }

  template<typename Z, typename Z1>
  EVE_FORCEINLINE auto dd_nary_dispatch(tag::ldexp_, Z const& z1, Z1 n) noexcept
  {
    EVE_ASSERT(eve::all(is_flint(n)), "some n are not flint");
    return as_wide_as_t<Z, Z1>(ldexp(high(z1), high(n)), ldexp(low(z1), high(n)));
  }

  template<ordered_value Z>
  EVE_FORCEINLINE   auto to_dd( Z const & v) noexcept
  {
    if constexpr(is_dd_v<Z>) return v;
    else    return as_dd_t<Z>(v, Z(0));
  }


  template<value Z1, value Z2>
  EVE_FORCEINLINE auto tagged_dispatch(eve::tag::if_else_,
                                              auto const& cond,
                                              Z1 const  & z1,
                                              Z2 const  & z2) noexcept
  requires(is_dd_v<Z1> != is_dd_v<Z2>)
  {
    return if_else(cond, to_dd(z1), to_dd(z2));
  }

  //================================================================================================
  //! @}
  //================================================================================================
}
