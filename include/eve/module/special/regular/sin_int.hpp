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
  struct sin_int_t : strict_elementwise_callable<sin_int_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sin_int_t, sin_int_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var sin_int
//!   @brief  `elementwise_callable` object computing the sine integral
//!   \f$ \mathbf{Si}(x) = \displaystyle \int_0^x \frac{\sin t}{t}\;\mbox{d}t\f$.
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
//!      constexpr auto sin_int(floating_value auto x)                                   noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto sin_int[conditional_expr auto c](/*any of the above overloads*/) noexcept; // 2
//!      constexpr auto sin_int[logical_value auto m](/*any of the above overloads*/)    noexcept; // 2
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
//!     1. The value of the sine integral
//!   \f$ \mathbf{E}_n(x) = \displaystyle \int_0^x \frac{\sin t}{t}\;\mbox{d}t\f$, is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld:Sine Integral ](https://mathworld.wolfram.com/SineIntegral.html)
//!   *  [DLMF: Sine Integral](https://dlmf.nist.gov/6.2#i)
//!   *  [Wikipedia: Sine integral](https://en.wikipedia.org/wiki/Sine_integral)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/special/sin_int.cpp}
//================================================================================================
  inline constexpr auto sin_int = functor<sin_int_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr T sin_int_(EVE_REQUIRES(cpu_), O const&, T x) noexcept
    {
      using t_t = underlying_type_t<T>;
      auto t = eve::sqr(x);

      auto br_less36 =  [x](auto x2){//  if t ≤ 36.0
        auto p0 = eve::reverse_horner(x2, t_t(1.00000000000000000000E0),
                                      t_t(-0.44663998931312457298E-1  ),
                                      t_t(0.11209146443112369449E-2   ),
                                      t_t(-0.13276124407928422367E-4  ),
                                      t_t(0.85118014179823463879E-7   ),
                                      t_t(-0.29989314303147656479E-9  ),
                                      t_t(0.55401971660186204711E-12  ),
                                      t_t(-0.42406353433133212926E-15 ));
        auto q0 = eve::reverse_horner(x2, t_t(1.00000000000000000000E0),
                                      t_t(0.10891556624243098264E-1),
                                      t_t(0.59334456769186835896E-4),
                                      t_t(0.21231112954641805908E-6),
                                      t_t(0.54747121846510390750E-9),
                                      t_t(0.10378561511331814674E-11),
                                      t_t(0.13754880327250272679E-14),
                                      t_t(0.10223981202236205703E-17));
        return x * p0/q0;
      };

      auto invt = eve::rec(t);
       auto spio_2 = eve::copysign(pio_2(eve::as(x)), x);
      auto br_less144   =  [x, s, c, spio_2](auto invx2){//if t > 36 && t <=  144.0
        auto [s, c] = sincos(x);
        auto p0 = eve::reverse_horner(invx2, t_t(0.99999999962173909991E0),
                                      t_t(0.36451060338631902917E3),
                                      t_t(0.44218548041288440874E5),
                                      t_t(0.22467569405961151887E7),
                                      t_t(0.49315316723035561922E8),
                                      t_t(0.43186795279670283193E9),
                                      t_t(0.11847992519956804350E10),
                                      t_t(0.45573267593795103181E9));
        auto q0 = eve::reverse_horner(invx2, t_t(1.00000000000000000000E0),
                                      t_t(0.36651060273229347594E3),
                                      t_t(0.44927569814970692777E5),
                                      t_t(0.23285354882204041700E7),
                                      t_t(0.53117852017228262911E8),
                                      t_t(0.50335310667241870372E9),
                                      t_t(0.16575285015623175410E10),
                                      t_t(0.11746532837038341076E10));
        auto p1 = eve::reverse_horner(invx2, t_t(0.99999999920484901956E0),
                                      t_t(0.51385504875307321394E3),
                                      t_t(0.92293483452013810811E5),
                                      t_t(0.74071341863359841727E7),
                                      t_t(0.28142356162841356551E9),
                                      t_t(0.49280890357734623984E10),
                                      t_t(0.35524762685554302472E11),
                                      t_t(0.79194271662085049376E11),
                                      t_t(0.17942522624413898907E11));
        auto q1 = eve::reverse_horner(invx2, t_t(1.00000000000000000000E0),
                                      t_t(0.51985504708814870209E3),
                                      t_t(0.95292615508125947321E5),
                                      t_t(0.79215459679762667578E7),
                                      t_t(0.31977567790733781460E9),
                                      t_t(0.62273134702439012114E10),
                                      t_t(0.54570971054996441467E11),
                                      t_t(0.18241750166645704670E12),
                                      t_t(0.15407148148861454434E12));
        return spio_2 - c*p0/(x*q0) - s*invx2*p1/q1;
      };

      auto br_else  =  [x, s, c, spio_2](auto invx2){//if t >   144.0 && t < inf
        auto [s, c] = sincos(x);
        auto p0 = eve::reverse_horner(invx2, t_t(0.19999999999999978257E1),
                                      t_t(0.22206119380434958727E4),
                                      t_t(0.84749007623988236808E6),
                                      t_t(0.13959267954823943232E9),
                                      t_t(0.10197205463267975592E11),
                                      t_t(0.30229865264524075951E12),
                                      t_t(0.27504053804288471142E13),
                                      t_t(0.21818989704686874983E13));
        auto q0 = eve::reverse_horner(invx2, t_t(1.00000000000000000000E0),
                                      t_t(0.11223059690217167788E4),
                                      t_t(0.43685270974851313242E6),
                                      t_t(0.74654702140658116258E8),
                                      t_t(0.58580034751805687471E10),
                                      t_t(0.20157980379272098841E12),
                                      t_t(0.26229141857684496445E13),
                                      t_t(0.87852907334918467516E13));
        auto p1 = eve::reverse_horner(invx2, t_t(0.59999999999999993089E1),
                                      t_t(0.96527746044997139158E4),
                                      t_t(0.56077626996568834185E7),
                                      t_t(0.15022667718927317198E10),
                                      t_t(0.19644271064733088465E12),
                                      t_t(0.12191368281163225043E14),
                                      t_t(0.31924389898645609533E15),
                                      t_t(0.25876053010027485934E16),
                                      t_t(0.12754978896268878403E16));
        auto q1 = eve::reverse_horner(invx2, t_t(1.00000000000000000000E0),
                                      t_t(0.16287957674166143196E4),
                                      t_t(0.96636303195787870963E6),
                                      t_t(0.26839734750950667021E9),
                                      t_t(0.37388510548029219241E11),
                                      t_t(0.26028585666152144496E13),
                                      t_t(0.85134283716950697226E14),
                                      t_t(0.11304079361627952930E16),
                                      t_t(0.42519841479489798424E16));
        return eve::fsm(eve::fsm(spio_2, (c/x), oneminus( p0/q0*invx2)), s*invx2, oneminus(p1/q1*invx2));
      };

      auto r = eve::if_else(eve::is_nan(x), eve::nan, spio_2);
      auto notdone = eve::is_finite(t);
      if( eve::any(notdone) )
      {
        notdone = next_interval(br_less36, notdone, t <= 36, r, t);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_less144, notdone, t <= 144, r, invt);
          if( eve::any(notdone) )
          {
            last_interval(br_else, notdone, r, invt);
          }
        }
      }
      return r;
    }
  }
}
