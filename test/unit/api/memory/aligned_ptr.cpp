//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/memory/aligned_ptr.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <array>

TTS_CASE( "aligned_ptr default constructors" )
{
  eve::aligned_ptr<double> nullptr_constructed_ptr = nullptr;
  eve::aligned_ptr<double> default_constructed_ptr;

  TTS_EQUAL( default_constructed_ptr.get(), nullptr );
  TTS_EQUAL( nullptr_constructed_ptr.get(), nullptr );
}

TTS_CASE( "aligned_ptr factory functions" )
{
  alignas(16) std::array<char,10> values;
  TTS_EQUAL( eve::as_aligned(&values[0]).get()    , &values[0] );
  TTS_EQUAL( eve::as_aligned<16>(&values[0]).get(), &values[0] );
}

TTS_CASE( "aligned_ptr pre/post increment & decrement" )
{
  char values[2];
  eve::aligned_ptr<char,1> ptr = &values[0];

  ptr++;
  TTS_EQUAL( ptr.get(), &values[1] );
  ptr--;
  TTS_EQUAL( ptr.get(), &values[0] );
  ++ptr;
  TTS_EQUAL( ptr.get(), &values[1] );
  --ptr;
  TTS_EQUAL( ptr.get(), &values[0] );
}

struct type
{
  auto method() const { return this; }
  int member;
};

TTS_CASE( "aligned_ptr provides pointer-like interface" )
{
  TTS_SETUP("An aligned_ptr of default alignment")
  {
    type value{42}, other_value{1337};
    alignas(16) type extra_aligned_value{787};

    eve::aligned_ptr<type> ptr        = &value;
    eve::aligned_ptr<type> other_ptr  = &other_value;
    eve::aligned_ptr<type,16> realigned_ptr  = &extra_aligned_value;

    TTS_SECTION("has the proper default alignment")
    {
      TTS_EQUAL( ptr.alignment(), alignof(type) );
    }

    TTS_SECTION("has access to its pointee members")
    {
      TTS_EQUAL( ptr.get(), &value );
      TTS_EQUAL( ptr->method(), &value );
      TTS_EQUAL( ptr->member, 42 );
      ptr->member = 69;
      TTS_EQUAL( value.member, 69 );
    }

    TTS_SECTION("supports re-assignment from raw pointer")
    {
      ptr  = &other_value;
      TTS_EQUAL( ptr->method(), &other_value );
      TTS_EQUAL( ptr->member, 1337 );
      ptr->member = 101;
      TTS_EQUAL( other_value.member, 101 );
    }

    TTS_SECTION("supports re-assignment from other aligned_ptr")
    {
      ptr = other_ptr;
      TTS_EQUAL( ptr->method(), &other_value );
      TTS_EQUAL( ptr->member, 1337 );
      ptr->member = 99;
      TTS_EQUAL( other_value.member, 99 );
    }

    TTS_SECTION("supports re-assignment from other aligned_ptr of different alignment")
    {
      ptr = realigned_ptr;
      TTS_EQUAL( ptr->method(), &extra_aligned_value );
      TTS_EQUAL( ptr->member, 787 );
      ptr->member = 99;
      TTS_EQUAL( extra_aligned_value.member, 99 );
    }

    TTS_SECTION("supports subscripting operator")
    {
      ptr[0] = other_value;
      TTS_EQUAL( ptr->method(), &value );
      TTS_EQUAL( ptr->member, 1337 );
      ptr->member = 99;
      TTS_EQUAL( value.member, 99 );
    }

    TTS_SECTION("supports incrementing by valid value")
    {
      ptr += ptr.alignment();
      TTS_EQUAL( ptr.get(), &value + ptr.alignment());
    }

    TTS_SECTION("supports decrementing by valid value")
    {
      ptr -= ptr.alignment();
      TTS_EQUAL( ptr.get(), &value - ptr.alignment());
    }

    TTS_SECTION("supports swap")
    {
      ptr.swap(other_ptr);
      TTS_EQUAL( ptr->member, 1337 );
      TTS_EQUAL( other_ptr->member, 42 );

      swap(ptr,other_ptr);
      TTS_EQUAL( ptr->member, 42 );
      TTS_EQUAL( other_ptr->member, 1337 );
    }
  }
}
