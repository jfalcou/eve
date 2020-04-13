//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2020 Jean-Thierry LAPRESTE
   Copyright 2020 Joel FALCOU

   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_IFREXP_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_IFREXP_HPP_INCLUDED


#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/add.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_notand.hpp>
#include <eve/function/bit_shr.hpp>
#include <eve/function/is_denormal.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/logical_notand.hpp>
#include <eve/function/sub.hpp>
#include <eve/constant/limitexponent.hpp>
#include <eve/constant/maxexponentm1.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <eve/constant/expobits_mask.hpp>
/// #include <eve/function/bit_cast.hpp>
// #include <eve/function/bit_shr.hpp>
// #include <eve/function/bit_and.hpp>
// #include <eve/function/bit_andnot.hpp>
// #include <eve/function/bit_cast.hpp>
// #include <eve/function/bit_notand.hpp>
// #include <eve/function/bit_or.hpp>
// #include <eve/function/combine.hpp>
// #include <eve/function/if_else.hpp>
// #include <eve/function/is_eqz.hpp>
// #include <eve/function/is_denormal.hpp>
// #include <eve/function/is_not_finite.hpp>
// #include <eve/function/logical_notand.hpp>
// #include <eve/constant/limitexponent.hpp>
// #include <eve/constant/maxexponent.hpp>
// #include <eve/constant/maxexponentm1.hpp>
// #include <eve/constant/nbmantissabits.hpp>
// #include <eve/constant/expobits_mask.hpp>
// #include <eve/constant/half.hpp>
// #include <eve/constant/twotonmb.hpp>
// #include <eve/function/pedantic.hpp>
// #include <eve/function/regular.hpp>
// #include <eve/function/raw.hpp>
// #include <eve/detail/meta.hpp>
// #include <eve/platform.hpp>
// #include <type_traits>
#include <tuple>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
//   template<floating_real_value T,  typename D>
//   EVE_FORCEINLINE constexpr auto ifrexp_(EVE_SUPPORTS(cpu_)
//                                         , D const &
//                                         , T a0) noexcept
//   //  Requires( std::tuple<wide<T, N>, as_integer_t<wide<T, N>, signed>>, floating_point<T>)
//   {
//     if constexpr(native<T>)
//     {
//       using elt_t =  element_type_t<T>;
//       using i_t = as_integer_t<T, signed>;
//       i_t r1   = bit_and(Expobits_mask<T>(), a0);//extract exp.
//       auto x    = bit_notand(Expobits_mask<T>(), a0);
//       auto m =  bit_or(Half<T>(), x);
//       auto e =  bit_shr(r1,Nbmantissabits<elt_t>()) - Maxexponentm1<elt_t>();
//       if constexpr(std::is_same_v<D, raw_type>)
//       {
//         return std::make_tuple(m, e);
//       }
//       auto test0 = is_nez(a0);
//       i_t t(0);
//       if constexpr(std::is_same_v<D, regular_type>)
//       {
//         if constexpr(scalar_value<T>)
//         {
//           if (test0) return std::make_tuple(T(0),t);
//         }
//         else return std::make_tuple(if_else(test0, m, eve::zero_), if_else(test0, e, eve::zero_));
//       }
//       if constexpr(std::is_same_v<D, pedantic_type>)
//       {
//         if constexpr(scalar_value<T>)
//         {
//           if (a0 == 0 || is_not_finite(a0)) return std::make_tuple(a0, t);
//         }

//         if constexpr(eve::platform::supports_denormals)
//         {
//           auto test = is_eqz(e);  //denormal
//           t = if_else(test,Nbmantissabits<elt_t>(), eve::zero_);
//           a0 = if_else(test, Twotonmb<elt_t>()*a0, a0);
//         }
//         auto test0 = is_nez(a0);
//         auto test1 = is_greater(e,Limitexponent<T>());
//         if constexpr(scalar_value<T>)
//         {
//           if (!test1 && test0) e = Zero(as(e));
//         }
//         else e = if_else(logical_notand(test1, test0), e, eve::zero_);
//         if constexpr(eve::platform::supports_denormals) e -= t;
//         return std::make_tuple( if_else(test0, add[test1](m, a0), eve::zero_), e);
//       }
//     }
//     else return apply_over2(D()(ifrexp), a0);
//   }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto ifrexp_(EVE_SUPPORTS(cpu_)
                                        , raw_type const &
                                        , T a0) noexcept

  {
    if constexpr(native<T>)
    {
      using elt_t = element_type_t<T>;
      auto r1   = bit_and(Expobits_mask<T>(), a0);
      auto x    = bit_notand(Expobits_mask<T>(), a0);
      return  std::make_tuple( bit_or(Half<T>(), x), bit_shr(r1,Nbmantissabits<elt_t>()) - Maxexponentm1<elt_t>());
    }
    else  return apply_over2(raw_(ifrexp), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto ifrexp_(EVE_SUPPORTS(cpu_)
                                        , T a0) noexcept

  {
    if constexpr(native<T>)
    {
      auto [m, e] =  raw_(ifrexp)(a0);
      auto a0eqz = is_eqz(a0);
      if constexpr(scalar_value<T>)
      {
        using i_t = as_integer_t<T>;
        if (a0eqz) return std::make_tuple(T(0),i_t(0));
      }
      return std::make_tuple(if_else(a0eqz, eve::zero_, m)
                            , if_else(a0eqz, eve::zero_, e));
    }
    else  return apply_over2(raw_(ifrexp), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto ifrexp_(EVE_SUPPORTS(cpu_)
                                        , pedantic_type const &
                                        , T a0) noexcept

  {
    if constexpr(native<T>)
    {
       using i_t = as_integer_t<T, signed>;
      if constexpr(simd_value<T>)
      {
         using elt_t =  element_type_t<T>;
        i_t t(0);
        if constexpr(eve::platform::supports_denormals)
        {
          auto test = is_denormal(a0);
          t = if_else(test,Nbmantissabits<T>(), eve::zero_);
          a0 = if_else(test, Twotonmb<T>()*a0, a0);
        }
        auto e = bit_and(Expobits_mask<T>(), a0); //extract exp.
        auto x  = bit_notand(Expobits_mask<T>(), a0);
        e = bit_shr(e,Nbmantissabits<elt_t>()) - Maxexponentm1<elt_t>();
        auto r0 = bit_or(Half<T>(), x);
        auto test0 = is_nez(a0);
        auto test1 = is_greater(e,Limitexponent<T>());
        e = if_else(logical_notand(test1, test0), e, eve::zero_);

        if constexpr(eve::platform::supports_denormals)
        {
          e -= t ;
        }
        return std::make_tuple( if_else(test0, add[test1](r0,a0), eve::zero_), e);

      }
      else  if constexpr(scalar_value<T>)
      {
        if (a0 == 0 || is_not_finite(a0))
        {
          return std::make_tuple(a0, i_t(0));
        }
        else if constexpr(scalar_value<T>)
        {
          auto const nmb  = Nbmantissabits<T>();
          i_t e    = bit_and(Expobits_mask<T>(), a0);  // extract exp.
          if constexpr(eve::platform::supports_denormals)
          {
            i_t t = i_t(0);
            if(is_eqz(e)) // denormal
            {
              a0 *= Twotonmb<T>();
              e  = bit_and(Expobits_mask<T>(), a0);  // extract exp. again
              t   = nmb;
            }
            T x  = bit_andnot(a0, Expobits_mask<T>());        // clear exp. in a0
            e = bit_shr(e,nmb)- Maxexponentm1<T>();         // compute exp.
            if (e > Limitexponent<T>()) return std::make_tuple(a0, i_t(0));
            e -= t;
            return std::make_tuple(bit_or(x,Half<T>()), e);
          }
          else
          {
            T x  = bit_andnot(a0, Expobits_mask<T>());        // clear exp. in a0
            e = bit_shr(e,nmb)- Maxexponentm1<T>();         // compute exp.
            if (e > Limitexponent<T>()) return {a0, i_t(0)};
            return std::make_tuple(bit_or(x,Half<T>()), e);
          }
        }
      }
    }
    else  return apply_over2(raw_(ifrexp), a0);
  }


}

#endif
