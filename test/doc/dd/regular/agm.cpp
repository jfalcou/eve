#include <tts/tts.hpp>
#include <eve/module/dd.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>
#include <boost/multiprecision/cpp_bin_float.hpp>

int main()
{
  using namespace boost::multiprecision;

  auto outputit = [](auto tag, auto valstr){
    cpp_bin_float_quad val(valstr);
    double hi = double(val);
    double lo = double(val-hi);

    std::cout << "  template<typename T>\n";
    std::cout << "  EVE_FORCEINLINE constexpr auto dd_cts_dispatch(eve::tag::" << tag << ", as<T> const&) noexcept\n";
    std::cout << "  {return dd_mk_cts(eve::tag::pio_4_{}, as<T>(), " << std::setprecision(17) << hi << ", " << lo << "); }\n\n";
  };

outputit("catalan","0.91596 55941 77219 01505");
// outputit("cbrt_pi","");
// outputit("cos_1","");
// outputit("cosh_1","");
// outputit("egamma","");
// outputit("egamma_sqr","");
// //outputit("epso_2","");
// outputit("euler","");
// outputit("exp_pi","");
// outputit("extreme_value_skewness","");
// outputit("four_minus_pi","");
// outputit("four_pio_3","");
// outputit("glaisher","1.28242 71291 00622 63687");
// //outputit("inv_2eps","");
// outputit("inv_2pi","");
// outputit("invcbrt_pi","");
// outputit("inv_egamma","");
// outputit("inv_e","");
// outputit("invlog10_2","");
// outputit("invlog10_e","");
// outputit("invlog_10","");
// outputit("invlog_2","");
// outputit("invlog_phi","");
// outputit("inv_pi","");
// outputit("invsqrt_2","");
// outputit("khinchin","");
// outputit("log10_e","");
// outputit("log_10","");
// outputit("log2_e","");
// outputit("log_2","");
// outputit("loglog_2","");
// outputit("log_phi","");
// outputit("math","");
// outputit("maxlog10","");
// outputit("maxlog2","");
// outputit("maxlog","");
// outputit("minlog10denormal","");
// outputit("minlog10","");
// outputit("minlog2denormal","");
// outputit("minlog2","");
// outputit("minlogdenormal","");
// outputit("minlog","");
// outputit("phi","1.61803398874989484820");
// outputit("pi2","");
// outputit("pi2o_16","");
// outputit("pi2o_6","");
// outputit("pi3","");
// outputit("pi_minus_3","");
// outputit("pio_3","");
// outputit("pio_6","");
// outputit("pi_pow_e","");
// outputit("rayleigh_kurtosis_excess","");
// outputit("rayleigh_kurtosis","");
// outputit("rayleigh_skewness","");
// outputit("rsqrt_2pi","");
// outputit("rsqrt_e","");
// outputit("rsqrt_pi","");
// outputit("rsqrt_pio_2","");
// outputit("sin_1","");
// outputit("sinh_1","");
// outputit("sixth","");
// outputit("sqrt_2","1.41421 35623 73095 04880");
// outputit("sqrt_2pi","");
// outputit("sqrt_3","1.73205 08075 68877 29352");
// outputit("sqrt_e","");
// outputit("sqrtlog_4","");
// outputit("sqrt_pi","");
// outputit("sqrt_pio_2","");
// outputit("third","");
// outputit("three_o_4","");
// outputit("three_pio_4","");
// outputit("two_o_3","");
// outputit("two_o_pi","");
// outputit("two_o_sqrt_pi","");
// outputit("two_pi","");
// outputit("two_pio_3","");
// outputit("zeta_2","");
// outputit("zeta_3","");

  return 0;
}
