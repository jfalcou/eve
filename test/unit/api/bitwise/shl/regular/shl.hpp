//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/shl.hpp>
#include <eve/constant/allbits.hpp>

TTS_CASE_TPL("Check operator<< return type", EVE_TYPE)
{
  using vi_t = eve::as_integer_t<T        , signed  >;
  using vu_t = eve::as_integer_t<T        , unsigned>;
  using si_t = eve::as_integer_t<EVE_VALUE, signed  >;
  using su_t = eve::as_integer_t<EVE_VALUE, unsigned>;

  TTS_EXPR_IS((T() << T() )   , T);
  TTS_EXPR_IS((T() << vi_t() ), T);
  TTS_EXPR_IS((T() << vu_t() ), T);

  TTS_EXPR_IS((T() << EVE_VALUE() ) , T);
  TTS_EXPR_IS((T() << si_t() )      , T);
  TTS_EXPR_IS((T() << su_t() )      , T);
}

TTS_CASE_TPL("Check operator<< behavior", EVE_TYPE)
{
  using vi_t = eve::as_integer_t<T        , signed  >;
  using vu_t = eve::as_integer_t<T        , unsigned>;
  using si_t = eve::as_integer_t<EVE_VALUE, signed  >;
  using su_t = eve::as_integer_t<EVE_VALUE, unsigned>;

  TTS_EQUAL((T(0) << T(7)), T( 0));
  TTS_EQUAL((T(1) << T(4)), T(16));
  TTS_EQUAL((T(3) << T(2)), T(12));

  TTS_EQUAL((T(0) << vi_t(7)), T( 0));
  TTS_EQUAL((T(1) << vi_t(4)), T(16));
  TTS_EQUAL((T(3) << vi_t(2)), T(12));

  TTS_EQUAL((T(0) << vu_t(7)), T( 0));
  TTS_EQUAL((T(1) << vu_t(4)), T(16));
  TTS_EQUAL((T(3) << vu_t(2)), T(12));

  TTS_EQUAL((T(0) << EVE_VALUE(7)), T( 0));
  TTS_EQUAL((T(1) << EVE_VALUE(4)), T(16));
  TTS_EQUAL((T(3) << EVE_VALUE(2)), T(12));

  TTS_EQUAL((T(0) << si_t(7)), T( 0));
  TTS_EQUAL((T(1) << si_t(4)), T(16));
  TTS_EQUAL((T(3) << si_t(2)), T(12));

  TTS_EQUAL((T(0) << su_t(7)), T( 0));
  TTS_EQUAL((T(1) << su_t(4)), T(16));
  TTS_EQUAL((T(3) << su_t(2)), T(12));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL((T(-1) << T(4)), T(-16));
    TTS_EQUAL((T(-3) << T(2)), T(-12));
    TTS_EQUAL((eve::allbits(eve::as<T>()) << T(1)), T(-2));

    TTS_EQUAL((T(-1) << vi_t(4)), T(-16));
    TTS_EQUAL((T(-3) << vi_t(2)), T(-12));
    TTS_EQUAL((eve::allbits(eve::as<T>()) << vi_t(1)), T(-2));

    TTS_EQUAL((T(-1) << vu_t(4)), T(-16));
    TTS_EQUAL((T(-3) << vu_t(2)), T(-12));
    TTS_EQUAL((eve::allbits(eve::as<T>()) << vu_t(1)), T(-2));

    TTS_EQUAL((T(-1) << EVE_VALUE(4)), T(-16));
    TTS_EQUAL((T(-3) << EVE_VALUE(2)), T(-12));
    TTS_EQUAL((eve::allbits(eve::as<T>()) << EVE_VALUE(1)), T(-2));

    TTS_EQUAL((T(-1) << si_t(4)), T(-16));
    TTS_EQUAL((T(-3) << si_t(2)), T(-12));
    TTS_EQUAL((eve::allbits(eve::as<T>()) << si_t(1)), T(-2));

    TTS_EQUAL((T(-1) << su_t(4)), T(-16));
    TTS_EQUAL((T(-3) << su_t(2)), T(-12));
    TTS_EQUAL((eve::allbits(eve::as<T>()) << su_t(1)), T(-2));
  }
  else
  {
    TTS_EQUAL((eve::allbits(eve::as<T>()) << T(1)), eve::allbits(eve::as<T>()) - 1 );
    TTS_EQUAL((eve::allbits(eve::as<T>()) << vi_t(1)), eve::allbits(eve::as<T>()) - 1 );
    TTS_EQUAL((eve::allbits(eve::as<T>()) << vu_t(1)), eve::allbits(eve::as<T>()) - 1 );

    TTS_EQUAL((eve::allbits(eve::as<T>()) << EVE_VALUE(1)), eve::allbits(eve::as<T>()) - 1 );
    TTS_EQUAL((eve::allbits(eve::as<T>()) << si_t(1)), eve::allbits(eve::as<T>()) - 1 );
    TTS_EQUAL((eve::allbits(eve::as<T>()) << su_t(1)), eve::allbits(eve::as<T>()) - 1 );
  }
}
