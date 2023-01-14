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
#include <tts/tts.hpp>

namespace eve::detail
{
  template<typename Tag, typename T>
  EVE_FORCEINLINE constexpr auto dd_cts_dispatch(Tag, as<T> const&) noexcept
  {
    detail::callable_object<Tag> cst;
    using t_t = underlying_type_t<T>;
    return T(cst(as<t_t>{}));
  }

  template<typename Tag, typename T>
  EVE_FORCEINLINE constexpr auto dd_mk_cts(Tag const &, as<T> const&
                                          , double const & hi,  double const & lo) noexcept
  {
    detail::callable_object<Tag> cst;
    using t_t = underlying_type_t<T>;
    using e_t = dd<t_t>;
    if constexpr( std::is_same_v<t_t, float> ) return T(e_t(cst(as<double>())));
    else if constexpr( std::is_same_v<t_t, double> ) return T(e_t(hi, lo));
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto dd_cts_dispatch(eve::tag::euler_, as<T> const&) noexcept
  { return dd_mk_cts(eve::tag::euler_{}, as<T>(), 2.718281828459045091e+00, 1.445646891729250158e-16); }

  template<typename T>
  EVE_FORCEINLINE constexpr auto dd_cts_dispatch(eve::tag::log_10_, as<T> const&) noexcept
  { return dd_mk_cts(eve::tag::log_10_{}, as<T>(), 2.302585092994045901e+00, -2.170756223382249351e-16); }

  template<typename T>
  EVE_FORCEINLINE constexpr auto dd_cts_dispatch(eve::tag::log_2_, as<T> const&) noexcept
  { return dd_mk_cts(eve::tag::log_2_{}, as<T>(), 6.931471805599452862e-01, 2.319046813846299558e-17); }

  template<typename T>
  EVE_FORCEINLINE constexpr auto dd_cts_dispatch(eve::tag::pi_, as<T> const&) noexcept
  { return dd_mk_cts(eve::tag::pi_{}, as<T>(), 3.141592653589793116e+00,1.224646799147353207e-16); }

  template<typename T>
  EVE_FORCEINLINE constexpr auto dd_cts_dispatch(eve::tag::pio_2_, as<T> const&) noexcept
  { return dd_mk_cts(eve::tag::pio_2_{}, as<T>(), 0.570796326794896558e+00, 6.123233995736766036e-17 ); }

  template<typename T>
  EVE_FORCEINLINE constexpr auto dd_cts_dispatch(eve::tag::pio_4_, as<T> const&) noexcept
  { return dd_mk_cts(eve::tag::pio_4_{}, as<T>(), 7.853981633974482790e-01, 3.061616997868383018e-17); }

  template<typename T>
  EVE_FORCEINLINE constexpr auto dd_cts_dispatch(eve::tag::three_pio_4_, as<T> const&) noexcept
  { return dd_mk_cts(eve::tag::three_pio_4_{}, as<T>(), 2.356194490192344837e+00, 9.1848509936051484375e-17); }

  template<typename T>
  EVE_FORCEINLINE constexpr auto dd_cts_dispatch(eve::tag::two_pi_, as<T> const&) noexcept
  { return dd_mk_cts(eve::tag::two_pi_{}, as<T>(), 6.283185307179586232e+00, 2.449293598294706414e-16); }

//   template<typename T>
//   EVE_FORCEINLINE constexpr auto dd_cts_dispatch(eve::tag::_, as<T> const&) noexcept
//   { return dd_mk_cts(eve::tag::_{}, as<T>(), ); }


  // special cases
  template<ordered_value T>
  EVE_FORCEINLINE constexpr auto epsilon_(EVE_SUPPORTS(cpu_), as<dd<T>> const&) noexcept
  {
    using t_t = element_type_t<T>;
    using e_t = dd<t_t>;
    if constexpr( std::is_same_v<t_t, float> ) return T(e_t(Constant<T, 0x28800000>()));
    else if constexpr( std::is_same_v<t_t, double> ) return T(e_t(Constant<T, 0x3970000000000000ll>()));
  }

// const double dd_real::_min_normalized = 2.0041683600089728e-292;  // = 2^(-1022 + 53)
// const dd_real dd_real::_max =
//     dd_real(1.79769313486231570815e+308, 9.97920154767359795037e+291);
// const dd_real dd_real::_safe_max =
//     dd_real(1.7976931080746007281e+308, 9.97920154767359795037e+291);
// const int dd_real::_ndigits = 31;


}
