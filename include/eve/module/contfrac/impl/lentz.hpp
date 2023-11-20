//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{

  template <typename T>
  struct is_pair : public std::false_type{};

  template <typename T, typename U>
  struct is_pair<kumi::tuple<T,U>> : public std::true_type{};

//   template <typename T> inline constexpr bool  is_pair_v = is_pair<T>::value;

//   template <typename T> concept pure_pair = is_pair_v<T> && is_pair_v<eve::underlying_type<T>>;

  template <typename Gen>
  struct fraction_traits_simple
  {
    using result_type = typename Gen::result_type;
    using  value_type = typename Gen::result_type;

    static result_type a(const value_type&) noexcept
    {
      return result_type(1);
    }
    static result_type b(const value_type& v) noexcept
    {
      return v;
    }
  };

  template <typename Gen>
  struct fraction_traits_pair
  {
    using  value_type = typename Gen::result_type;
    using result_type = kumi::element_t<0, value_type>;

    static auto a(const value_type& v) noexcept
    {
      return get<0>(v);
    }
    static auto b(const value_type& v) noexcept
    {
      return get<1>(v);
    }
  };

  template <typename Gen>
  struct fraction_traits
    : public std::conditional<
    is_pair<typename Gen::result_type>::value,
    fraction_traits_pair<Gen>,
    fraction_traits_simple<Gen>>::type
  {};

//   template <typename T>
//   struct tiny_value
//   {
//     using u_t = eve::underlying_type<T>;
//     static T get() { return 16*eve::smallestposval(as<T>()); }
//   };

  //
  // continued_fraction_b
  // Evaluates:
  //
  // b0 +       a1
  //      ---------------
  //      b1 +     a2
  //           ----------
  //           b2 +   a3
  //                -----
  //                b3 + ...
  //
  // Note that the first a0 returned by generator Gen is discarded.
  //

  template <typename Gen, typename U>
  EVE_FORCEINLINE constexpr auto lentz_b_(EVE_SUPPORTS(cpu_), Gen g, const U& eps, size_t max_terms)
    noexcept
  {
    using traits = detail::fraction_traits<Gen>;
    using result_type = typename traits::result_type;
    using scalar_type = eve::underlying_type_t<result_type>;
    using u_t =  scalar_type;
    using eve::abs;

    u_t tiny = 16*eve::smallestposval(eve::as<u_t>()) ;
    u_t terminator(eps);

    auto v = g();

    auto f = traits::b(v);
    f = if_else(is_eqz(f), tiny, f);
    auto C = f;
    result_type D{};
    auto delta(D);
    size_t counter(max_terms);
    do{
      v = g();
      D = traits::b(v) + traits::a(v) * D;
      C = traits::b(v) + traits::a(v) / C;
      D = if_else(is_eqz(D), tiny, D);
      C = if_else(is_eqz(C), tiny, C);
      D = rec(D);
      delta = C*D;
      f *= delta;
    } while (eve::any(abs(dec(delta)) > terminator) && --counter);
    return f;
  }

  //
  // continued_fraction_a
  // Evaluates:
  //
  //            a1
  //      ---------------
  //      b1 +     a2
  //           ----------
  //           b2 +   a3
  //                -----
  //                b3 + ...
  //
  // Note that the first a1 and b1 returned by generator Gen are both used.
  //

  template <typename Gen, typename U>
  EVE_FORCEINLINE auto lentz_a_(EVE_SUPPORTS(cpu_), Gen g, const U& eps, size_t max_terms)  noexcept
  {
    using traits = detail::fraction_traits<Gen>;
    using result_type = typename traits::result_type;
    using scalar_type = typename eve::underlying_type_t<result_type>;
    using u_t =  scalar_type;
    using eve::abs;

    u_t tiny = 16*eve::smallestposval(eve::as<u_t>()) ;
    u_t terminator(eps);

    auto v = g();

    auto f  = traits::b(v);
    f = if_else(is_eqz(f), tiny, f);
    auto a0 = traits::a(v);
    auto C = f;
    result_type D{};
    auto delta(D);
    size_t counter(max_terms);
    do{
      v = g();
      D = traits::b(v) + traits::a(v) * D;
      C = traits::b(v) + traits::a(v) / C;
      D = if_else(is_eqz(D), tiny, D);
      C = if_else(is_eqz(C), tiny, C);
      D = rec(D);
      delta = C*D;
      f *= delta;
    } while (eve::any(abs(dec(delta)) > terminator) && --counter);
    return a0/f;
  }
}
