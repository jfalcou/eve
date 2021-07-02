//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/add.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/constant/valmax.hpp>
#include <string>

struct use_friend
{
  friend std::string tagged_dispatch( eve::tag::valmax_, eve::as<use_friend> )
  {
    return "valmax dispatched via friend";
  }

  friend std::string tagged_dispatch( eve::tag::add_, use_friend, use_friend )
  {
    return "add dispatched via friend";
  }

  template<eve::conditional_expr Cond>
  friend std::string tagged_dispatch( eve::tag::add_, Cond, use_friend, use_friend )
  {
    return "conditional add dispatched via friend";
  }

  friend std::string tagged_dispatch( eve::tag::add_, eve::pedantic_type, use_friend, use_friend )
  {
    return "pedantic add dispatched via friend";
  }

  template<eve::conditional_expr Cond>
  friend std::string tagged_dispatch( eve::tag::add_, Cond, eve::pedantic_type, use_friend, use_friend )
  {
    return "conditional pedantic add dispatched via friend";
  }
};

namespace other_space
{
  struct use_adl {};

  std::string tagged_dispatch( eve::tag::valmax_, eve::as<use_adl> )
  {
    return "valmax dispatched via ADL";
  }

  std::string tagged_dispatch( eve::tag::add_, use_adl, use_adl  )
  {
    return "add dispatched via ADL";
  }

  auto operator+(use_adl a, use_adl b)
  {
    return eve::add(a,b);
  }

  template<eve::conditional_expr Cond>
  std::string tagged_dispatch( eve::tag::add_, Cond, use_adl, use_adl )
  {
    return "conditional add dispatched via ADL";
  }

  std::string tagged_dispatch( eve::tag::add_, eve::pedantic_type, use_adl, use_adl )
  {
    return "pedantic add dispatched via ADL";
  }

  template<eve::conditional_expr Cond>
  std::string tagged_dispatch( eve::tag::add_, Cond, eve::pedantic_type, use_adl, use_adl )
  {
    return "conditional pedantic add dispatched via ADL";
  }
}

TTS_CASE("Check that constant can be externally defined for user-defined types" )
{
  TTS_EQUAL( eve::valmax( eve::as<use_friend>{}            ), "valmax dispatched via friend" );
  TTS_EQUAL( eve::valmax( eve::as<other_space::use_adl>{}  ), "valmax dispatched via ADL"    );
}

TTS_CASE("Check that function can be externally defined for user-defined types" )
{
  use_friend            fa, fb;
  other_space::use_adl  aa, ab;

  TTS_EQUAL( eve::add(fa, fb) , "add dispatched via friend" );
  TTS_EQUAL( eve::add(aa, ab) , "add dispatched via ADL"    );
  TTS_EQUAL( (aa + ab)        , "add dispatched via ADL"    );
}

TTS_CASE("Check that function + conditional can be externally defined for user-defined types" )
{
  use_friend            fa, fb;
  other_space::use_adl  aa, ab;

  TTS_EQUAL( eve::add[true](fa, fb) , "conditional add dispatched via friend" );
  TTS_EQUAL( eve::add[true](aa, ab) , "conditional add dispatched via ADL"    );
}

TTS_CASE("Check that function + decorator can be externally defined for user-defined types" )
{
  use_friend            fa, fb;
  other_space::use_adl  aa, ab;

  TTS_EQUAL( eve::pedantic(eve::add)(fa, fb) , "pedantic add dispatched via friend" );
  TTS_EQUAL( eve::pedantic(eve::add)(aa, ab) , "pedantic add dispatched via ADL"    );
}

TTS_CASE("Check that conditional function + decorator can be externally defined for user-defined types" )
{
  use_friend            fa, fb;
  other_space::use_adl  aa, ab;

  TTS_EQUAL( eve::pedantic(eve::add[true])(fa, fb) , "conditional pedantic add dispatched via friend" );
  TTS_EQUAL( eve::pedantic(eve::add[true])(aa, ab) , "conditional pedantic add dispatched via ADL"    );
}
