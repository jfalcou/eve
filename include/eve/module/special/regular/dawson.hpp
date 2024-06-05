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
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

namespace eve
{
  template<typename Options>
  struct dawson_t : elementwise_callable<dawson_t, Options>
  {
    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE constexpr T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(dawson_t, dawson_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var dawson
//!   @brief Computes the Dawson function \f$\displaystyle D_+(x)=e^{-x^2}\int_0^{x}
//!   e^{t^2} \mbox{d}t\f$
//!
//!   **Defined in header**
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
//!      template< eve::floating_ordered_value T >
//!      T dawson(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   the value of the Dawson function for `x` is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/dawson.cpp}
//! @}
//================================================================================================
inline constexpr auto dawson = functor<dawson_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr T dawson_(EVE_REQUIRES(cpu_), O const&, T const& a0) noexcept
    {
      using elt_t  = element_type_t<T>;
      auto x       = eve::abs(a0);
      auto rx      = x;
      auto xx      = sqr(x);
      auto dawson1 = [](auto xx, auto x){
        if constexpr( std::is_same_v<elt_t, float> )
        {
          return x *
          eve::reverse_horner(xx, T(0x1.000000p+0f), T(-0x1.77cccap-4f), T(0x1.5a3578p-5f)
                             , T(-0x1.bdb92ep-11f), T(0x1.71a316p-12f), T(0x1.9d2900p-19f)
                             , T(0x1.ffb82ep-21f), T(0x1.4e0912p-26f), T(0x1.d2e30ap-31f)
                             , T(0x1.8ffb30p-37f)) /
          eve::reverse_horner(xx, T(0x1.000000p+0f), T(0x1.265bbcp-1f), T(0x1.455fdcp-3f)
                             , T(0x1.c9d936p-6f), T(0x1.c92fd0p-9f), T(0x1.555662p-12f)
                             , T(0x1.860dcep-16f), T(0x1.559b5cp-20f), T(0x1.bfc372p-25f)
                             , T(0x1.993234p-30f), T(0x1.a6ddf6p-36f)) ;
        }
        else
        {
          return x  *
          eve::reverse_horner(xx, T(0x1.0000000000000p+0), T(-0x1.77ccca3261da7p-4), T(0x1.5a357714ced03p-5)
                             , T(-0x1.bdb92e4e9a921p-11), T(0x1.71a3163a27174p-12), T(0x1.9d29007c3bd6ap-19)
                             , T(0x1.ffb82d857b833p-21), T(0x1.4e09113ca0ba0p-26), T(0x1.d2e309db8f5fbp-31)
                             , T(0x1.8ffb30f7d51f1p-37)) /
          eve::reverse_horner(xx, T(0x1.0000000000000p+0), T(0x1.265bbc0f09197p-1), T(0x1.455fdbcb2a008p-3)
                             , T(0x1.c9d9358f736f7p-6), T(0x1.c92fcf5507532p-9), T(0x1.555661ec43b62p-12)
                             , T(0x1.860dcd4d604a3p-16), T(0x1.559b5c414f013p-20), T(0x1.bfc372910659cp-25)
                             , T(0x1.993234f10c1b4p-30), T(0x1.a6ddf536ed65ap-36));
        }
      };
      auto dawson2 = [](auto xx, auto rx, auto x){
        if constexpr( std::is_same_v<elt_t, float> )
        {
          auto num   =
          eve::reverse_horner(xx, T(0x1.3bfc2ap-35f), T(-0x1.4a3b14p-29f), T(0x1.86d8bep-24f), T(-0x1.2015dep-19f)
                             , T(0x1.2db062p-15f), T(-0x1.bbc454p-12f), T(0x1.dffee2p-9f), T(-0x1.665626p-6f)
                             , T(0x1.81a4bap-4f), T(-0x1.f541cep-3f), T(0x1.0495c6p-1f))
          ;
          auto denom =
          eve::reverse_horner(xx, T(0x1.3bfc20p-34f), T(-0x1.51a2c0p-28f), T(0x1.961706p-23f), T(-0x1.31eec2p-18f)
                             , T(0x1.4795fcp-14f), T(-0x1.f105f8p-11f), T(0x1.15e2e6p-7f), T(-0x1.b3a7e0p-5f)
                             , T(0x1.e4c688p-3f), T(-0x1.438084p-1f), T(0x1.0p0))
          ;
          return average(rx, xx * num / (denom * x));
        }
        else
        {
          auto num   =
          eve::reverse_horner(xx, T(0x1.3bfc2ac32b39ep-35), T(-0x1.4a3b14d9709f0p-29), T(0x1.86d8be5016991p-24)
                             , T(-0x1.2015dd001fa5bp-19), T(0x1.2db061d28d773p-15), T(-0x1.bbc454e5479acp-12)
                             , T(0x1.dffee25eba9bdp-9), T(-0x1.66562633da983p-6), T(0x1.81a4b94e413c5p-4)
                             , T(-0x1.f541cdebcb905p-3), T(0x1.0495c52fe411ep-1))
          ;
          auto denom =
          eve::reverse_horner(xx, T(0x1.3bfc202a6b560p-34), T(-0x1.51a2c0f7cf15cp-28), T(0x1.961705729c1cdp-23)
                             , T(-0x1.31eec145c9b53p-18), T(0x1.4795fc069cc34p-14), T(-0x1.f105f8f05c7d8p-11)
                             , T(0x1.15e2e53c1fb60p-7), T(-0x1.b3a7e0ed1122bp-5), T(0x1.e4c6875173c3ep-3)
                             , T(-0x1.438083f2d47c7p-1), T(0x1.0p0))
          ;
          return average(rx, xx * num / (denom * x));
        }
      };
      auto dawson3 = [](auto xx, auto rx, auto x){
        if constexpr( std::is_same_v<elt_t, float> )
        {
          auto num   =
          eve::reverse_horner(xx, T(-0x1.fe79cap-12f), T(0x1.0e11acp-6f), T(-0x1.6203e2p-3f)
                             , T(0x1.422b20p-1f), T(-0x1.2e6230p-1f))
          ;
          auto denom =
          eve::reverse_horner(xx, T(-0x1.fe79cap-11f), T(0x1.1a0886p-5f), T(-0x1.932858p-2f)
                             , T(0x1.bb92c0p+0f), T(-0x1.595ea2p+1f), T(0x1.0p0));
          return average(rx, xx * num / (denom * x));
        }
        else
        {
          auto num   =
          eve::reverse_horner(xx, T(-0x1.fe79cad3d09fbp-12), T(0x1.0e11ab3d4d36bp-6), T(-0x1.6203e2f0a174ep-3)
                             , T(0x1.422b1f29fbcb6p-1), T(-0x1.2e622ffa7ef20p-1));
          auto denom =
          eve::reverse_horner(xx, T(-0x1.fe79cad3d0a8dp-11), T(0x1.1a0885fe44f2dp-5), T(-0x1.932857b438c94p-2)
                             , T(0x1.bb92c0388a954p+0), T(-0x1.595ea2e7576e2p+1), T(0x1.0p0));
          return average(rx, xx * num / (denom * x));
        }
      };
      auto dawson4 = [](auto rx) { return rx * T(0.5); };

      auto r       = nan(as<T>());
      auto notdone = is_not_nan(x);
      notdone      = next_interval(dawson1, notdone, x < elt_t(3.25), r, xx, x);
      rx           = rec[pedantic2](x);
      xx           = sqr(rx);
      if( eve::any(notdone) )
      {
        notdone = next_interval(dawson2, notdone, x < elt_t(6.25), r, xx, rx, x);
        if( eve::any(notdone) )
        {
          notdone = next_interval(dawson3, notdone, x < elt_t(1.0e9), r, xx, rx, x);
          if( eve::any(notdone) ) { last_interval(dawson4, x >= elt_t(1.0e9), r, rx); }
        }
      }
      return eve::copysign(r, a0);
    }
  }
}
