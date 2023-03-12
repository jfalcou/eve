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
#include <eve/module/doublereal/regular/traits.hpp>

namespace eve::detail
{
  ////////////////////////////////////////////////////////////////////////////////////////////
  /// if low part is 0
  ////////////////////////////////////////////////////////////////////////////////////////////
  template<typename Tag, typename T>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(Tag, as<T> const&) noexcept
  {
    detail::callable_object<Tag> cst;
    using t_t = underlying_type_t<T>;
    return T(cst(as<t_t>{}));
  }

  ////////////////////////////////////////////////////////////////////////////////////////////
  /// if upward and downward coincide
  ////////////////////////////////////////////////////////////////////////////////////////////
  template<typename Tag, typename T, decorator D>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(Tag, D const &, as<T> const&) noexcept
  {
    return  doublereal_cts_dispatch(Tag(), as<T>());
  }

  ////////////////////////////////////////////////////////////////////////////////////////////
  /// helpers for general non-trivial cases
  ////////////////////////////////////////////////////////////////////////////////////////////
  template<typename Tag, typename T>
  EVE_FORCEINLINE constexpr auto doublereal_mk_cts(Tag const &, as<T> const&
                                          , double const & hi,  double const & lo) noexcept
  {
    detail::callable_object<Tag> cst;
    using t_t = underlying_type_t<T>;
    using e_t = doublereal<t_t>;
    if constexpr( std::is_same_v<t_t, float> ) return T(e_t(cst(as<double>())));//float-float from double
    else if constexpr( std::is_same_v<t_t, double> ) return T(e_t(hi, lo));//double-double from given pair
  }

  template<typename Tag, typename T, typename S, decorator D>
  EVE_FORCEINLINE constexpr auto doublereal_mk_cts(Tag const &, D const&, as<T> const&
                                          , S const & dw,  S const & hw) noexcept
  {
    detail::callable_object<Tag> cst;
    if constexpr( std::is_same_v<D, downward_type> ) return make_doublereal(dw, as<T>());
    else if constexpr( std::is_same_v<D, upward_type> ) return make_doublereal(hw, as<T>());
  }

  ////////////////////////////////////////////////////////////////////////////////////////////
  /// euler
  ////////////////////////////////////////////////////////////////////////////////////////////
  template<typename T>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::euler_, as<T> const&) noexcept
  {
    using u_t          =  underlying_type_t<T>;
    using doublereal_t =  doublereal<u_t>;
    if constexpr(std::same_as<u_t, double>)
      return T(doublereal_t(0x1.5bf0a8b145769p+1, 0x1.4d57ee2b1013ap-53));
    else if constexpr(std::same_as<u_t, float>)
      return  T(doublereal_t(0x1.5bf0a8p+1, 0x1.628aeep-24));
  }

  template<typename T, decorator D>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::euler_, D const &, as<T> const&) noexcept
  {
    using u_t          =  underlying_type_t<T>;
    using doublereal_t =  doublereal<u_t>;
    if constexpr(std::same_as<u_t, double>)
      return doublereal_mk_cts(eve::tag::euler_{}, as<T>()
                            , doublereal_t(0x1.5bf0a8b145769p+1, 0x1.4d57ee2b10139p-53)
                            , doublereal_t(0x1.5bf0a8b145769p+1, 0x1.4d57ee2b1013ap-53));
    else if constexpr(std::same_as<u_t, float>)
      return doublereal_mk_cts(eve::tag::euler_{}, as<T>()
                           , doublereal_t(0x1.5bf0a8p+1, 0x1.628aecp-24)
                           , doublereal_t(0x1.5bf0a8p+1, 0x1.628aeep-24));
  }

//   EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::euler_, as<T> const&) noexcept
//   { return doublereal_mk_cts(eve::tag::euler_{}, as<T>(), 2.718281828459045091e+00, 1.445646891729250158e-16); }

  ////////////////////////////////////////////////////////////////////////////////////////////
  /// invlog_10
  ////////////////////////////////////////////////////////////////////////////////////////////
  template<typename T>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::invlog_10_, as<T> const&) noexcept
  {
    using u_t          =  underlying_type_t<T>;
    using doublereal_t =  doublereal<u_t>;
    if constexpr(std::same_as<u_t, double>)
      return T(doublereal_t(0x1.bcb7b1526e50ep-2, 0x1.95355baaafad3p-57));
    else if constexpr(std::same_as<u_t, float>)
      return  T(doublereal_t(0x1.bcb7b2p-2, -0x1.5b235ep-27));
  }

  template<typename T, decorator D>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::invlog_10_, D const &, as<T> const&) noexcept
  {
    using u_t          =  underlying_type_t<T>;
    using doublereal_t =  doublereal<u_t>;
    if constexpr(std::same_as<u_t, double>)
      return doublereal_mk_cts(eve::tag::invlog_10_{}, as<T>()
                            , doublereal_t(0x1.bcb7b1526e50ep-2, 0x1.95355baaafad3p-57)
                            , doublereal_t(0x1.bcb7b1526e50ep-2, 0x1.95355baaafad4p-57));
    else if constexpr(std::same_as<u_t, float>)
      return doublereal_mk_cts(eve::tag::invlog_10_{}, as<T>()
                           , doublereal_t(0x1.bcb7b2p-2, -0x1.5b236p-27)
                           , doublereal_t(0x1.bcb7b2p-2, -0x1.5b235ep-27));
  }

  ////////////////////////////////////////////////////////////////////////////////////////////
  /// invlog_2
  ////////////////////////////////////////////////////////////////////////////////////////////
  template<typename T>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::invlog_2_, as<T> const&) noexcept
  { return doublereal_mk_cts(eve::tag::invlog_2_{}, as<T>(), 0x1.71547652b82fep+0, 0x1.777d0ffda0d24p-56); }

  template<typename T, decorator D>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::invlog_2_, D const &, as<T> const&) noexcept
  {
    using u_t          =  underlying_type_t<T>;
    using doublereal_t =  doublereal<u_t>;
    if constexpr(std::same_as<u_t, double>)
      return doublereal_mk_cts(eve::tag::invlog_2_{}, as<T>()
                            , doublereal_t(0x1.71547652b82fep+0, 0x1.777d0ffda0d23p-56)
                            , doublereal_t(0x1.71547652b82fep+0, 0x1.777d0ffda0d24p-56));
    else if constexpr(std::same_as<u_t, float>)
      return doublereal_mk_cts(eve::tag::invlog_2_{}, as<T>()
                           , doublereal_t(0x1.715476p+0, 0x1.4ae0bep-26)
                           , doublereal_t(0x1.715476p+0, 0x1.4ae0cp-26));
  }

  ////////////////////////////////////////////////////////////////////////////////////////////
  /// inv_pi
  ////////////////////////////////////////////////////////////////////////////////////////////
  template<typename T>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::inv_pi_, as<T> const&) noexcept
  {
    using u_t          =  underlying_type_t<T>;
    using doublereal_t =  doublereal<u_t>;
    if constexpr(std::same_as<u_t, double>)
      return T(doublereal_t(0x1.45f306dc9c883p-2, -0x1.6b01ec5417056p-56));
    else if constexpr(std::same_as<u_t, float>)
      return  T(doublereal_t(0x1.45f306p-2, 0x1.b9391p-27));
  }

  template<typename T, decorator D>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::inv_pi_, D const &, as<T> const&) noexcept
  {
    using u_t          =  underlying_type_t<T>;
    using doublereal_t =  doublereal<u_t>;
    if constexpr(std::same_as<u_t, double>)
      return doublereal_mk_cts(eve::tag::inv_pi_{}, as<T>()
                            , doublereal_t(0x1.45f306dc9c883p-2, -0x1.6b01ec5417057p-56)
                            , doublereal_t(0x1.45f306dc9c883p-2, -0x1.6b01ec5417056p-56));
    else if constexpr(std::same_as<u_t, float>)
      return doublereal_mk_cts(eve::tag::inv_pi_{}, as<T>()
                           , doublereal_t(0x1.45f306p-2, 0x1.b9391p-27)
                           , doublereal_t(0x1.45f306p-2, 0x1.b93912p-27));
  }

  ////////////////////////////////////////////////////////////////////////////////////////////
  /// log_10
  ////////////////////////////////////////////////////////////////////////////////////////////
  template<typename T>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::log_10_, as<T> const&) noexcept
  {
    using u_t          =  underlying_type_t<T>;
    using doublereal_t =  doublereal<u_t>;
    if constexpr(std::same_as<u_t, double>)
      return T(doublereal_t(0x1.26bb1bbb55516p+1, -0x1.f48ad494ea3e9p-53));
    else if constexpr(std::same_as<u_t, float>)
      return  T(doublereal_t(0x1.26bb1cp+1, -0x1.12aabap-25));
  }

 template<typename T, decorator D>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::log_10_, D const &, as<T> const&) noexcept
  {
    using u_t          =  underlying_type_t<T>;
    using doublereal_t =  doublereal<u_t>;
    if constexpr(std::same_as<u_t, double>)
      return doublereal_mk_cts(eve::tag::log_10_{}, as<T>()
                            , doublereal_t(0x1.26bb1bbb55516p+1, -0x1.f48ad494ea3eap-53)
                            , doublereal_t(0x1.26bb1bbb55516p+1, -0x1.f48ad494ea3e9p-53));
    else if constexpr(std::same_as<u_t, float>)
      return doublereal_mk_cts(eve::tag::log_10_{}, as<T>()
                           , doublereal_t(0x1.26bb1cp+1, -0x1.12aabcp-25)
                           , doublereal_t(0x1.26bb1cp+1, -0x1.12aabap-25));
  }

  ////////////////////////////////////////////////////////////////////////////////////////////
  /// log_2
  ////////////////////////////////////////////////////////////////////////////////////////////
  template<typename T>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::log_2_, as<T> const&) noexcept
  {
    using u_t          =  underlying_type_t<T>;
    using doublereal_t =  doublereal<u_t>;
    if constexpr(std::same_as<u_t, double>)
      return T(doublereal_t(0x1.62e42fefa39efp-1, 0x1.abc9e3b39803fp-56));
    else if constexpr(std::same_as<u_t, float>)
      return  T(doublereal_t(0x1.62e43p-1, -0x1.05c61p-29));
  }

  template<typename T, decorator D>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::log_2_, D const &, as<T> const&) noexcept
  {
    using u_t          =  underlying_type_t<T>;
    using doublereal_t =  doublereal<u_t>;
    if constexpr(std::same_as<u_t, double>)
      return doublereal_mk_cts(eve::tag::log_2_{}, as<T>()
                            , doublereal_t(0x1.62e42fefa39efp-1, 0x1.abc9e3b39803fp-56)
                            , doublereal_t(0x1.62e42fefa39efp-1, 0x1.abc9e3b39804p-56));
    else if constexpr(std::same_as<u_t, float>)
      return doublereal_mk_cts(eve::tag::log_2_{}, as<T>()
                           , doublereal_t(0x1.62e43p-1, -0x1.05c61p-29)
                           , doublereal_t(0x1.62e43p-1, -0x1.05c60ep-29));
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// pi
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<typename T>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::pi_, as<T> const&) noexcept
  { return doublereal_mk_cts(eve::tag::pi_{}, as<T>(), 3.141592653589793116e+00,1.224646799147353207e-16); }


  template<typename T, decorator D>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::pi_, D const &, as<T> const&) noexcept
  {
    using u_t          =  underlying_type_t<T>;
    using doublereal_t =  doublereal<u_t>;
    if constexpr(std::same_as<u_t, double>)
      return doublereal_mk_cts(eve::tag::pi_{}, as<T>()
                              , doublereal_t(0x1.921fb54442d18p+1, 0x1.1a62633145c06p-53)
                              , doublereal_t(0x1.921fb54442d18p+1, 0x1.1a62633145c07p-53));
    else if constexpr(std::same_as<u_t, float>)
      return doublereal_mk_cts(eve::tag::pi_{}, as<T>()
                              , doublereal_t(0x1.921fb6p+1, -0x1.777a5ep-24)
                              , doublereal_t(0x1.921fb6p+1, -0x1.777a5cp-24));
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// pio_2
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<typename T>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::pio_2_, as<T> const&) noexcept
  { return doublereal_mk_cts(eve::tag::pio_2_{}, as<T>(), 1.570796326794896558e+00, 6.123233995736766036e-17 ); }

  template<typename T, decorator D>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::pio_2_, D const &, as<T> const&) noexcept
  {
    using u_t          =  underlying_type_t<T>;
    using doublereal_t =  doublereal<u_t>;
    if constexpr(std::same_as<u_t, double>)
      return doublereal_mk_cts(eve::tag::pio_2_{}, as<T>()
                              , doublereal_t(0x1.921fb54442d18p+0, 0x1.1a62633145c06p-54)
                              , doublereal_t(0x1.921fb54442d18p+0, 0x1.1a62633145c07p-54));
    else if constexpr(std::same_as<u_t, float>)
      return doublereal_mk_cts(eve::tag::pio_2_{}, as<T>()
                              , doublereal_t(0x1.921fb6p+0, -0x1.777a5ep-25)
                              , doublereal_t(0x1.921fb6p+0, -0x1.777a5cp-25));
   }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// pio_4
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                              template<typename T>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::pio_4_, as<T> const&) noexcept
  { return doublereal_mk_cts(eve::tag::pio_4_{}, as<T>(), 7.853981633974482790e-01, 3.061616997868383018e-17); }

  template<typename T, decorator D>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::pio_4_, D const &, as<T> const&) noexcept
  {
    using u_t          =  underlying_type_t<T>;
    using doublereal_t =  doublereal<u_t>;
    if constexpr(std::same_as<u_t, double>)
      return doublereal_mk_cts(eve::tag::pio_4_{}, as<T>()
                            , doublereal_t(0x1.921fb54442d18p-1, 0x1.1a62633145c07p-55)
                            , doublereal_t(0x1.921fb54442d18p-1, 0x1.1a62633145c08p-55));
    else if constexpr(std::same_as<u_t, float>)
      return doublereal_mk_cts(eve::tag::pio_4_{}, as<T>()
                           , doublereal_t(0x1.921fb6p-1, -0x1.777a5cp-26)
                           , doublereal_t(0x1.921fb6p-1, -0x1.777a5ap-26));
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// three_pio_4
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  template<typename T>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::three_pio_4_, as<T> const&) noexcept
  { return doublereal_mk_cts(eve::tag::three_pio_4_{}, as<T>(), 2.356194490192344837e+00, 9.1848509936051484375e-17); }

  template<typename T, decorator D>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::three_pio_4_, D const &, as<T> const&) noexcept
  {
    using u_t          =  underlying_type_t<T>;
    using doublereal_t =  doublereal<u_t>;
    if constexpr(std::same_as<u_t, double>)
      return doublereal_mk_cts(eve::tag::three_pio_4_{}, as<T>()
                            , doublereal_t(0x1.2d97c7f3321d2p+1, 0x1.a79394c9e8a0ap-54)
                            , doublereal_t(0x1.2d97c7f3321d2p+1, 0x1.a79394c9e8a0bp-54));
    else if constexpr(std::same_as<u_t, float>)
      return doublereal_mk_cts(eve::tag::three_pio_4_{}, as<T>()
                           , doublereal_t(0x1.921fb6p-1, -0x1.777a5cp-26)
                           , doublereal_t(0x1.921fb6p-1, -0x1.777a5ap-26));
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// third
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<ordered_value T>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::third_, as<T> const&) noexcept
  { return doublereal_mk_cts(eve::tag::third_{}, as<T>(), 0x1.5555555555555p-2, 0x1.5555555555555p-56); }

  template<typename T, decorator D>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::third_, D const &, as<T> const&) noexcept
  {
    using u_t          =  underlying_type_t<T>;
    using doublereal_t =  doublereal<u_t>;
    if constexpr(std::same_as<u_t, double>)
      return doublereal_mk_cts(eve::tag::third_{}, as<T>()
                            , doublereal_t(0x1.5555555555555p-2, 0x1.5555555555555p-56)
                            , doublereal_t(0x1.5555555555555p-2, 0x1.5555555555556p-56));
    else if constexpr(std::same_as<u_t, float>)
      return doublereal_mk_cts(eve::tag::third_{}, as<T>()
                           , doublereal_t(0x1.555556p-2, -0x1.555556p-27)
                           , doublereal_t(0x1.555556p-2, -0x1.555554p-27));
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// two_pi
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<typename T>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::two_pi_, as<T> const&) noexcept
  { return doublereal_mk_cts(eve::tag::two_pi_{}, as<T>(), 6.283185307179586232e+00, 2.449293598294706414e-16); }

  template<typename T, decorator D>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::two_pi_, D const &, as<T> const&) noexcept
  {
    using u_t          =  underlying_type_t<T>;
    using doublereal_t =  doublereal<u_t>;
    if constexpr(std::same_as<u_t, double>)
      return doublereal_mk_cts(eve::tag::two_pi_{}, as<T>()
                            , doublereal_t(0x1.921fb54442d18p+2, 0x1.1a62633145c06p-52)
                            , doublereal_t(0x1.921fb54442d18p+2, 0x1.1a62633145c07p-52));
    else if constexpr(std::same_as<u_t, float>)
      return doublereal_mk_cts(eve::tag::two_pi_{}, as<T>()
                           , doublereal_t(0x1.921fb6p-1, -0x1.777a5cp-26)
                           , doublereal_t(0x1.921fb6p-1, -0x1.777a5ap-26));
  }

  // special cases
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// eps
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<ordered_value T>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::eps_, as<T> const&) noexcept
  requires(is_doublereal_v<T>)
  {
    using t_t = underlying_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return (T(Constant<t_t, 0x28800000>()));
    else if constexpr( std::is_same_v<t_t, double> ) return (T(Constant<t_t, 0x3970000000000000ll>()));
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// smallestposval
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<ordered_value T>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::smallestposval_, as<T> const&) noexcept
  requires(is_doublereal_v<T>)
  {
    using t_t = underlying_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return (T(Constant<t_t, 0xc800000>()));// = 2^(-126 + 24)
    else if constexpr( std::is_same_v<t_t, double> ) return (T(Constant<t_t, 0x360000000000000ll>()));// = 2^(-1022 + 53)
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// valmax
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<ordered_value T>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::valmax_, as<T> const&) noexcept
  requires(is_doublereal_v<T>)
  {
    using t_t = underlying_type_t<T>;
    using e_t = doublereal<t_t>;
    if constexpr( std::is_same_v<t_t, float> ) return T(e_t(3.4028235e+38f, 1.0141204e+31f));
    else if constexpr( std::is_same_v<t_t, double> ) return T(e_t(1.79769313486231570815e+308, 9.97920154767359795037e+291));
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// valmin
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<ordered_value T>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::valmin_, as<T> const&) noexcept
  requires(is_doublereal_v<T>)
  {
    using t_t = underlying_type_t<T>;
    using e_t = doublereal<t_t>;
    if constexpr( std::is_same_v<t_t, float> ) return T(e_t(-3.4028235e+38f, -1.0141204e+31f));
    else if constexpr( std::is_same_v<t_t, double> ) return T(e_t(-1.79769313486231570815e+308, -9.97920154767359795037e+291));
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// oneosqrteps
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<ordered_value T>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::oneosqrteps_, as<T> const&) noexcept
  requires(is_doublereal_v<T>)
  {
    using t_t = underlying_type_t<T>;
    using e_t = doublereal<t_t>;
    return rec(sqrt(eps(as<e_t>())));
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// maxflint
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<ordered_value T>
  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::maxflint_, as<T> const&) noexcept
  requires(is_doublereal_v<T>)
  {
    using t_t = underlying_type_t<T>;
    using e_t = doublereal<t_t>;
    if constexpr( std::is_same_v<t_t, float> ) return T(e_t(0x1p+46, -0x1p+0));
    else if constexpr( std::is_same_v<t_t, double> ) return T(e_t(0x1p+104, -0x1p+0));
  }

}
