//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/dd/regular/traits.hpp>
#include <eve/module/dd/detail/utilities.hpp>


namespace eve::detail
{

  template<typename Ts...>
  EVE_FORCEINLINE constexpr auto
  trivial_dd_converter(Tag const & tag, T const& ...zs) noexcept
  {
    detail::callable_object<Tag> func;
    if constexpr(is_dd_v<T>)
      return func(zs...);
    else if(floating_ordered_value<T>)
      return func(as_dd_t(zs...));
   }
  
  //rec
  template<value T>
  EVE_FORCEINLINE constexpr auto
  rec_(EVE_SUPPORTS(cpu_), eve::domain::dd_converter const&, T const& z) noexcept
  {
    return trivial_dd_converter(eve::tag::rec_, z); 
//     if constexpr(is_dd_v<T>)
//       return rec(z);
//     else if(floating_ordered_value<T>)
//       return rec(as_dd_t(z));
   }


//   template<typename Z>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::frexp_, Z const& z) noexcept
//   {
//     auto [h, n] = frexp(high(z));
//     auto l = ldexp(low(z), -n);
//     return kumi::tuple{Z(h, l), n};
//   }

//   //================================================================================================
//   //  unary functions
//   //================================================================================================


//   template<typename Z1>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::next_, Z1 const& z1) noexcept
//   {
//     auto nz1  = make_dd(high(z1), next(low(z1)));
//     auto pnz1 = make_dd(high(nz1), prev(low(nz1)));

//     return if_else(pnz1> z1, pnz1, nz1);
//   }

//   template<typename Z1>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::prev_, Z1 const& z1) noexcept
//   {
//     auto pz1 = make_dd(high(z1), prev(low(z1)));
//     auto nnz1= make_dd(high(pz1), next(low(pz1)));
//     return if_else(nnz1 < z1, nnz1, pz1);
//   }

  template<value T>
  EVE_FORCEINLINE constexpr auto
  sqr_(EVE_SUPPORTS(cpu_), eve::domain::dd_converter const&, T const& z) noexcept
  {
    if constexpr(is_dd_v<T>)
      return sqr(z);
    else if(floating_ordered_value<T>)
      return Z(two_sqr(z, z)); 
  }
  
//   template<typename Z>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::sqr_, Z const& a) noexcept
//   {
//     auto [ahi, alo] = a;
//     auto[p1, p2] = two_sqr(ahi);
//     p2 += 2 * ahi * alo;
//     p2 += sqr(alo);
//     auto [ s1, s2] = quick_two_add(p1, p2);
//     return Z{s1, s2};
//   }

//   template<typename Z>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::sqrt_, Z const& a) noexcept
//   {
//     Z r(sqrt(high(a)));
//     r +=  (a-sqr(r))/(2*r);
//     return r;
//  //    auto err = low(a)/(2*high(r));
// //     return add(err, r);
// //    return r + (half(as(low(a)))*low(a))*rec(2*r);
//   }

//   template<typename Z>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::trunc_, Z const& z) noexcept
//   {
//     return if_else(is_positive(high(z)), floor(z), ceil(z));
//   }


//   //================================================================================================
//   //  Binary functions
//   //================================================================================================

//   EVE_FORCEINLINE auto
//   dd_binary_dispatch(eve::tag::add_, auto const& z1, auto const& z2) noexcept
//   {
//     return z1 + z2;
//   }

//   EVE_FORCEINLINE auto
//   dd_binary_dispatch(eve::tag::mul_, auto const& z1, auto const& z2) noexcept
//   {
//     return z1 * z2;
//   }

//   EVE_FORCEINLINE auto
//   dd_binary_dispatch(eve::tag::sub_, auto const& z1, auto const& z2) noexcept
//   {
//     return z1 - z2;
//   }

//    EVE_FORCEINLINE auto
//   dd_binary_dispatch(eve::tag::div_, auto const& z1, auto const& z2) noexcept
//   {
//     return z1 / z2;
//   }

//   EVE_FORCEINLINE auto
//   dd_binary_dispatch(eve::tag::negate_, auto const& z1, auto const& z2) noexcept
//   {
//     return z1 * sign(high(z2));
//   }

//   template<typename Z1, typename Z2>
//   EVE_FORCEINLINE auto
//   dd_binary_dispatch(eve::tag::negatenz_, Z1 const& z1, Z2 const& z2) noexcept
//   {
//     return z1 * signnz(high(z2));
//   }


//   //================================================================================================
//   //  Binary functions with integral second parameter
//   //================================================================================================
//   template<typename Z1, integral_value N> //TODO this doesnot work see prev.cpp
//   EVE_FORCEINLINE auto
//   dd_n_binary_dispatch(eve::tag::prev_, Z1 const& z1, N const& n) noexcept;

//   template<typename Z1, integral_value N> //TODO this doesnot work see next.cpp
//   EVE_FORCEINLINE auto
//   dd_n_binary_dispatch(eve::tag::next_, Z1 const& z1, N const& n) noexcept
//   {
//     using r_t = as_wide_as_t<Z1, N>;
//     auto nz1 = r_t(high(z1), next(low(z1), n));
//     auto pnz1 = r_t(high(nz1), prev(low(z1), n));
//     auto e =pnz1; //prev(pnz1, n);
//     return if_else(e > z1, pnz1, nz1);
//   }

//   template<typename Z1, integral_value N> //TODO this doesnot work see prev.cpp
//   EVE_FORCEINLINE auto
//   dd_n_binary_dispatch(eve::tag::next_, Z1 const& z1, N const& n) noexcept;

//   template<typename Z1, integral_value N> //TODO this doesnot work see prev.cpp
//   EVE_FORCEINLINE auto
//   dd_n_binary_dispatch(eve::tag::prev_, Z1 const& z1, N const& n) noexcept
//   {
//     using r_t = as_wide_as_t<Z1, N>;
//     auto pz1 = r_t(high(z1), prev(low(z1), n));
//     auto npz1 =  r_t(high(pz1), next(low(z1)));
//     auto e = next(npz1, n);
//     return if_else(e < z1, npz1, pz1);
//   }

//   template<typename Z, integral_value N>
//   EVE_FORCEINLINE auto dd_n_binary_dispatch(tag::ldexp_, Z const& z1, N n) noexcept
//   {
//     auto [zh, zl] = z1;
//     auto h = ldexp(zh, n);
//     auto l = ldexp(zl, n);
//     return make_dd(h, l);
//   }

//   template<typename Z, typename Z1>
//   EVE_FORCEINLINE auto dd_nary_dispatch(tag::ldexp_, Z const& z1, Z1 n) noexcept
//   {
//     EVE_ASSERT(eve::all(is_flint(n)), "some n are not flint");
//     return as_wide_as_t<Z, Z1>(ldexp(high(z1), high(n)), ldexp(low(z1), high(n)));
//   }

//   template<typename Z1, typename Z2>
//   EVE_FORCEINLINE auto dd_nary_dispatch(tag::ulpdist_, Z1 const& a0, Z2 const & a1) noexcept
//   {
//       auto [ m1, e1] = frexp(a0);
//       auto [ m2, e2] = frexp(a1);
//       auto expo = -max(e1, e2);
//       auto e = eve::abs(if_else( e1 == e2
//                                , m1-m2
//                                , ldexp(a0, expo)-ldexp(a1, expo)
//                                )
//                        );
//       return if_else ( (is_nan(a0) && is_nan(a1)) || (a0 == a1)
//                      , zero
//                      , e/eve::eps(eve::as(a0))
//                      );
//   }


//   //================================================================================================
//   //  ternary functions
//   //================================================================================================
//   template<decorator D, typename Z1, typename Z2, typename Z3>
//   EVE_FORCEINLINE auto
//   dd_nary_dispatch(eve::tag::fma_, D const &, Z1 a, Z2  b, Z3 c) noexcept
//   -> decltype(a*b+c)
//   {
//     using r_t = decltype(a*b+c);
//     auto p = qd_mul(r_t(a), r_t(b));
//     auto [q0, q1, q2, q3] = qd_add(p, r_t(c));
//     auto [a0, a1] = two_add(q0, q1 + q2 + q3);
//     return r_t(a0, a1);
//   }
}
