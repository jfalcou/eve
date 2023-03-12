//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "measures.hpp"
#include <eve/module/doublereal.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

eve::doublereal<double> cvt(boost::multiprecision::cpp_bin_float_quad a)
{
  double h = double(a);
  double l = double(a-h);
  return eve::doublereal<double>(h, l);
}
eve::doublereal<float> cvt(double a)
{
  float h = float(a);
  float l = float(a-h);
  return eve::doublereal<float>(h, l);
}

TTS_CASE_WITH( "Check behavior of exp on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& , T const& )
{
  using boost::multiprecision::cpp_bin_float_quad;
  using f128 = cpp_bin_float_quad;
  using dd_t = typename eve::doublereal<double>;
  dd_t  zbr_smalld, zbr_larged;
  using ff_t = typename eve::doublereal<float>;
  ff_t  zbr_smallf, zbr_largef;
  auto comp = [](auto ct, auto zbm, auto & zbr_small,  auto & zbr_large){
    auto zdr = tts::uptype(ct);

    if (zdr < zbm)
    {
      zbr_small = ct;
      zbr_large = eve::next(ct);
    }
    else if (zdr ==  zbm)
    {
      zbr_small = ct;
      zbr_large = ct;
    }
    else if (zdr > zbm)
    {
      zbr_small = eve::prev(ct);
      zbr_large = ct;
    }
  };
  auto name = "inv_pi";
  auto zbm = f128(1)/(4*(bm::atan(f128(1))));
  dd_t ctd = tts::to_doublereal<dd_t>(zbm);
  ff_t ctf = tts::to_doublereal<ff_t>(zbm);

  std::cout << std::setprecision(35) << "zbm " << zbm << std::endl;
  std::cout << "ctd " << ctd << std::endl;
  comp(ctd, zbm, zbr_smalld, zbr_larged);
  std::cout << "smalld " <<  zbr_smalld << std::endl;
  std::cout << "larged " <<  zbr_larged << std::endl;
  std::cout << "ctf " << ctf << std::endl;
  comp(ctf, zbm, zbr_smallf, zbr_largef);
  std::cout << "smallf " <<  zbr_smallf << std::endl;
  std::cout << "largef " <<  zbr_largef << std::endl;

  TTS_EQUAL(0, 0);

  std::cout << '\n' <<
    "  template<typename T>                                                                                       \n" <<
    "  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::" << name << "_, as<T> const&) noexcept   \n" <<
    "  {                                                                                                          \n" <<
    "    using u_t          =  underlying_type_t<T>;                                                              \n" <<
    "    using doublereal_t =  doublereal<u_t>;                                                                   \n" <<
    "    if constexpr(std::same_as<u_t, double>)                                                                  \n" <<
    "      return T(" << ctd << ");                                                                               \n" <<
    "    else if constexpr(std::same_as<u_t, float>)                                                              \n" <<
    "      return  T(" << ctf << ");                                                                              \n" <<
    "  }                                                                                                          \n" <<
    "                                                                                                             \n" <<
    "  template<typename T, decorator D>                                                                          \n" <<
    "  EVE_FORCEINLINE constexpr auto doublereal_cts_dispatch(eve::tag::" << name << "_, D const &, as<T> const&) noexcept    \n" <<
    "  {                                                                                                          \n" <<
    "    using u_t          =  underlying_type_t<T>;                                                              \n" <<
    "    using doublereal_t =  doublereal<u_t>;                                                                   \n" <<
    "    if constexpr(std::same_as<u_t, double>)                                                                  \n" <<
    "      return doublereal_mk_cts(eve::tag::" << name << "_{}, as<T>()                                          \n" <<
    "                            , " << zbr_smalld <<                                                            "\n" <<
    "                            , " << zbr_larged << "); " <<                                                   "\n" <<
    "    else if constexpr(std::same_as<u_t, float>)                                                              \n" <<
    "      return doublereal_mk_cts(eve::tag::" << name << "_{}, as<T>()                                          \n" <<
    "                           , " << zbr_smallf <<                                                             "\n" <<
    "                           , " << zbr_largef << "); " <<                                                    "\n" <<
    "  }                                                                                                          \n";



};
