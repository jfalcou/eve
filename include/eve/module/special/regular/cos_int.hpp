//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/detail/hz_device.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

namespace eve
{
  template<typename Options>
  struct cos_int_t : strict_elementwise_callable<cos_int_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(cos_int_t, cos_int_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var cos_int
//!   @brief  `elementwise_callable` object computing the cosine integral
//!   \f$ \mathbf{Ci}(x) = \displaystyle -\int_x^\infty \frac{\cos t}{t}\;\mbox{d}t\f$.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/special.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto cos_int(floating_value auto x)                                   noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto cos_int[conditional_expr auto c](/*any of the above overloads*/) noexcept; // 2
//!      constexpr auto cos_int[logical_value auto m](/*any of the above overloads*/)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [real floating argument](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. The value of the cosine integral
//!   \f$ \mathbf{Ci}(x) = \displaystyle -\int_x^\infty \frac{\cos t}{t}\;\mbox{d}t\f$, is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld:Cosine Integral ](https://mathworld.wolfram.com/CosineIntegral.html)
//!   *  [DLMF: Cosine Integral](https://dlmf.nist.gov/6.2#i)
//!   *  [Wikipedia:Cosine integral](https://en.wikipedia.org/wiki/Cosine_integral)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/special/cos_int.cpp}
//================================================================================================
  inline constexpr auto cos_int = functor<cos_int_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr T cos_int_(EVE_REQUIRES(cpu_), O const&, T x) noexcept
    {
      auto t2 = eve::sqr(x);
      auto invt2 = eve::rec(t2);
      using e_t =  eve::element_type_t<T>;

      auto br_less3 =  [x](auto x2){//  if x ≤ 3
        e_t r0 =  0.616505485620716233797110404100;
        e_t r01 = 0.6162109375;
        e_t r02 = 0.29454812071623379711E-3;
        auto p =  eve::reverse_horner(x2, -0.24607411378767540707E0,
                                      0.72113492241301534559E-2,
                                      -0.11867127836204767056E-3,
                                      0.90542655466969866243E-6,
                                      -0.34322242412444409037E-8,
                                      0.51950683460656886834E-11);
        auto q = eve::reverse_horner(x2, 1.00000000000000000000E0,
                                     0.12670095552700637845E-1,
                                     0.78168450570724148921E-4,
                                     0.29959200177005821677E-6,
                                     0.73191677761328838216E-9,
                                     0.94351174530907529061E-12);
        return eve::fam(eve::log(x/r0), ((x-r01)-r02)*(x+r0), p/q);
      };

      auto br_less6 =  [x](auto x2){//  if x > 3 && x <= 6
        e_t r1 =  3.384180422551186426397851146402;
        e_t r11 = 3.3837890625;
        e_t r12 = 0.39136005118642639785E-3;
        auto p = eve::reverse_horner(x2, -0.15684781827145408780E0,
                                     0.66253165609605468916E-2,
                                     -0.12822297297864512864E-3,
                                     0.12360964097729408891E-5,
                                     -0.66450975112876224532E-8,
                                     0.20326936466803159446E-10,
                                     -0.33590883135343844613E-13,
                                     0.23686934961435015119E-16);
        auto q = eve::reverse_horner(x2, 1.00000000000000000000E0,
                                     0.96166044388828741188E-2,
                                     0.45257514591257035006E-4,
                                     0.13544922659627723233E-6,
                                     0.27715365686570002081E-9,
                                     0.37718676301688932926E-12,
                                     0.27706844497155995398E-15);

        return eve::fam(eve::log(x/r1), ((x-r11)-r12)*(x+r1), p/q);
      };

      auto br_less12 =  [x](auto invx2){//  if x > 6 && x <= 12
        auto [s, c] =  sincos(x);
        auto p0 =eve::reverse_horner(invx2, 0.99999999962173909991E0,
                                     0.36451060338631902917E3,
                                     0.44218548041288440874E5,
                                     0.22467569405961151887E7,
                                     0.49315316723035561922E8,
                                     0.43186795279670283193E9,
                                     0.11847992519956804350E10,
                                     0.45573267593795103181E9);
        auto q0 =eve::reverse_horner(invx2, 1.00000000000000000000E0,
                                     0.36651060273229347594E3,
                                     0.44927569814970692777E5,
                                     0.23285354882204041700E7,
                                     0.53117852017228262911E8,
                                     0.50335310667241870372E9,
                                     0.16575285015623175410E10,
                                     0.11746532837038341076E10);
        auto p1 =eve::reverse_horner(invx2, 0.99999999920484901956E0,
                                     0.51385504875307321394E3,
                                     0.92293483452013810811E5,
                                     0.74071341863359841727E7,
                                     0.28142356162841356551E9,
                                     0.49280890357734623984E10,
                                     0.35524762685554302472E11,
                                     0.79194271662085049376E11,
                                     0.17942522624413898907E11);
        auto q1 = eve::reverse_horner(invx2, 1.00000000000000000000E0,
                                      0.51985504708814870209E3,
                                      0.95292615508125947321E5,
                                      0.79215459679762667578E7,
                                      0.31977567790733781460E9,
                                      0.62273134702439012114E10,
                                      0.54570971054996441467E11,
                                      0.18241750166645704670E12,
                                      0.15407148148861454434E12);
        return diff_of_prod( (s/x), p0/q0, c*invx2, p1/q1);
      };

      auto br_else =  [x](auto invx2){//  if x > 12 && x < Inf
        auto [s, c] =  sincos(x);
        auto p0 = eve::reverse_horner(invx2, 0.19999999999999978257E1,
                                      0.22206119380434958727E4,
                                      0.84749007623988236808E6,
                                      0.13959267954823943232E9,
                                      0.10197205463267975592E11,
                                      0.30229865264524075951E12,
                                      0.27504053804288471142E13,
                                      0.21818989704686874983E13);
        auto q0 = eve::reverse_horner(invx2, 1.00000000000000000000E0,
                                      0.11223059690217167788E4,
                                      0.43685270974851313242E6,
                                      0.74654702140658116258E8,
                                      0.58580034751805687471E10,
                                      0.20157980379272098841E12,
                                      0.26229141857684496445E13,
                                      0.87852907334918467516E13);
        auto p1 = eve::reverse_horner(invx2, 0.59999999999999993089E1,
                                      0.96527746044997139158E4,
                                      0.56077626996568834185E7,
                                      0.15022667718927317198E10,
                                      0.19644271064733088465E12,
                                      0.12191368281163225043E14,
                                      0.31924389898645609533E15,
                                      0.25876053010027485934E16,
                                      0.12754978896268878403E16);
        auto q1 = eve::reverse_horner(invx2, 1.00000000000000000000E0,
                                      0.16287957674166143196E4,
                                      0.96636303195787870963E6,
                                      0.26839734750950667021E9,
                                      0.37388510548029219241E11,
                                      0.26028585666152144496E13,
                                      0.85134283716950697226E14,
                                      0.11304079361627952930E16,
                                      0.42519841479489798424E16);

        return eve::diff_of_prod((s/x), eve::oneminus(p0/q0*invx2), c*invx2, eve::oneminus(p1/q1*invx2));
      };

      auto r = eve::if_else(eve::is_nan(x)||is_ltz(x), eve::nan, zero(eve::as(x)));
      r =  eve::if_else(is_eqz(x), eve::minf(as(x)), r);
      auto notdone = eve::is_gtz(x)&& (x != eve::inf(eve::as(x)));
      if( eve::any(notdone) )
      {
        notdone = next_interval(br_less3, notdone, x <= 3, r, t2);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_less6, notdone, x <= 6, r, t2);
          if( eve::any(notdone) )
          {
            notdone = next_interval(br_less12, notdone, x <= 12, r, invt2);
            if( eve::any(notdone) )
            {
              last_interval(br_else, notdone, r, invt2);
            }
          }
        }
      }
      return r;
    }
  }
}
