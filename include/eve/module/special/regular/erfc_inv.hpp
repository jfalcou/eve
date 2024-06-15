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
#include <eve/detail/hz_device.hpp>
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/math.hpp>

namespace eve
{
  template<typename Options>
  struct erfc_inv_t : elementwise_callable<erfc_inv_t, Options>
  {
    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(erfc_inv_t, erfc_inv_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var erfc_inv
//!   @brief Computes the inverse of the complementary error function.
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
//!      T erfc_inv(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!       Must be in interval  \f$[0, 2]\f$ else nan is returned.
//!
//!    **Return value**
//!
//!    The value of the inverse complementary error function is returned. In particular:
//!
//!      * If the argument is \f$\pm0\f$, \f$1\f$ is returned.
//!      * If the argument is \f$2\f$, \f$-\infty\f$ is returned.
//!      * If the argument is \f$0\f$,\f$\infty\f$ is returned.
//!      * If the argument is NaN, NaN is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/erfc_inv.cpp}
//! @}
//================================================================================================
inline constexpr auto erfc_inv = functor<erfc_inv_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    T constexpr erfc_inv_(EVE_REQUIRES(cpu_), O const&, T a0) noexcept
    {
      using elt_t = element_type_t<T>;
      auto a00     = oneminus(a0);
      auto w       = -log(a0 * (T(2) - a0));
      auto test    = w < T(5);
      auto r       = nan(as(a0));
      auto notdone = (a0 <= T(2)) && (a0 >= T(0));
      if constexpr( std::is_same_v<elt_t, float> )
      {
        w            = if_else(test, w - T(2.5), sqrt(w));
        auto br_wlt5 = [a00](auto w){
          return a00*eve::reverse_horner(w, T(0x1.805c5ep+0f), T(0x1.f91ec6p-3f), T(-0x1.11c9dep-8f)
                                        , T(-0x1.48a810p-10f), T(0x1.ca65b6p-13f), T(-0x1.26b582p-18f)
                                        , T(-0x1.d8e6aep-19f), T(0x1.70966cp-22f), T(0x1.e2cb10p-26f));
        };
        notdone = next_interval(br_wlt5, notdone, test, r, w);
        if( eve::any(notdone) )
        {
          auto br_wge5 = [a00](auto w){
            auto h = eve::reverse_horner(w, T(-0x1.5f17fcp-8f), T(0x1.31c2f8p-6f), T(-0x1.179ec6p-6f)
                                        , T(0x1.4c58aep-8f), T(0x1.7515dcp-9f))/
            eve::reverse_horner(w, T(0x1.5e8044p-7f), T(-0x1.bb0154p-7f), T(0x1.5204bep-8f)
                               , T(0x1.74e782p-9f), T(0x1.2c6364p-27f));
            return copysign(h, a00);
          };
          notdone = last_interval(br_wge5, notdone, r, w);
        }
        return if_else(w == inf(as(a0)), copysign(w, a00), r);
      }
      else // double
      {
        auto wlt6_25 = w < T(6.25);
        auto wlt16   = w < T(16.0);
        w            = if_else(wlt6_25, w, sqrt(w));
        w -= if_else(wlt6_25, T(3.125), if_else(wlt16, T(3.25), T(5.0)));
        auto br_wlt6_25 = [](auto w){
          return eve::reverse_horner(w, T(0x1.a755e7c99ae86p+0), T(0x1.ebd80d9b13e28p-3), T(-0x1.8b6c33114f909p-8)
                                    , T(-0x1.845769484fca8p-11), T(0x1.879c2a212f024p-13), T(-0x1.d1d1f7b8736f6p-17)
                                    , T(-0x1.6e8a5434ae8a2p-20), T(0x1.c6b4f5d03b787p-22), T(-0x1.f36cd6d3d46a9p-26)
                                    , T(-0x1.1a9e38dc84d60p-28), T(0x1.20f47ccf46b3cp-30), T(-0x1.dc583d118a561p-35)
                                    , T(-0x1.c8859c4e5c0afp-37), T(0x1.72a22c2d77e20p-39), T(-0x1.6f2167040d8e2p-44)
                                    , T(-0x1.6d33eed66c487p-45), T(0x1.de4acfd9e26bap-48), T(0x1.82e11898132e0p-56)
                                    , T(-0x1.33689090a6b96p-53), T(0x1.9ba72cd589b91p-57), T(0x1.7b83eef0b7c9fp-60)
                                    , T(-0x1.8ddf93324d327p-63), T(-0x1.135d2e746e627p-68));
        };
        notdone = next_interval(br_wlt6_25, notdone, wlt6_25, r, w);
        if( eve::any(notdone) )
        {
          auto br_wlt16 = [](auto w){
            return eve::reverse_horner(w, T(0x1.8abcc380d5a48p+1), T(0x1.0158a6d641d39p+0), T(0x1.5ffcfe5b76afcp-8)
                                      , T(-0x1.ebadabb891bbdp-9), T(0x1.468eeca533cf8p-9), T(-0x1.ba924132f38b1p-10)
                                      , T(0x1.f3cc55ad40c25p-11), T(-0x1.7448a89ef8aa3p-12), T(0x1.932cd54c8a222p-16)
                                      , T(0x1.1e684d0b9188ap-14), T(-0x1.8cef1f80281f2p-15), T(0x1.a29a0cacdfb23p-17)
                                      , T(0x1.8860cd5d652f6p-19), T(-0x1.0d5db812b5083p-18), T(0x1.936388a3790adp-20)
                                      , T(0x1.395abcd554c6cp-26), T(-0x1.2777453dd3955p-22), T(0x1.85cbe52878635p-24)
                                      , T(0x1.3040f87dbd932p-29));
          };
          notdone = next_interval(br_wlt16, notdone, wlt16, r, w);
          if( eve::any(notdone) )
          {
            auto br_wge16 = [](auto w){
              return eve::reverse_horner(w, T(0x1.3664ddd1ad7fbp+2), T(0x1.02a30d1fba0dcp+0), T(-0x1.22ea5df04047cp-13)
                                        , T(-0x1.c2f36a8fc5d53p-13), T(0x1.3ebf4eb00938fp-14), T(-0x1.4a3497e1e0facp-16)
                                        , T(0x1.2fbd29d093d2bp-18), T(-0x1.0a8d40ea372ccp-20), T(0x1.ebc8bb824cb54p-23)
                                        , T(-0x1.22d220fdf9c3ep-24), T(0x1.f4c20e1334af8p-26), T(-0x1.0102e495fb9c0p-26)
                                        , T(0x1.05ac6a8fba182p-27), T(-0x1.0468fb24e2f5fp-28), T(0x1.9e6bf2dda45e3p-30)
                                        , T(-0x1.18feec0e38727p-32), T(-0x1.dcec3a7785389p-36));
            };
            notdone = last_interval(br_wge16, notdone, r, w);
          }
        }
      }
      return if_else(w == inf(as(a0)), copysign(w, a00), a00 * r);
    }
  }
}
