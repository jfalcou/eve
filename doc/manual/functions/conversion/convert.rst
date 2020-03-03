.. _function-convert:

#######
convert
#######

**Required header:** ``#include <eve/function/convert.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ convert = {};
   }

Function object converting value of a type to another.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename U, typename N>  wide<U,N> operator()( wide<T,N> const& v, as_<U> const &) noexcept;
   template<typename T> constexpr                U         operator()( T s, as_<U> ) noexcept;

* [1] Converts element-wise  the first parameter to the second one.
* [2] Converts the first parameter to the type second one.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar of type **T**.

.. rubric:: Return value

* [1,2] A value of the type defined by **U** and the wideness of the first parameter. 

Notes
*****
  
  - U is always a scalar type.

  - If the first parameter is a wide type the output is a wide the cardinal of which is the same.

  - For scalar types ``convert(a,as<U>())`` is equivalent to ``static_cast<U>(a)``.

  - if ``sizeof(T)`` is less than 8 the associated base type is ``float`` else ``double``.


Options
*******

  - :ref:`saturated_ <feature-decorator>` decorator saturate the conversion.


.. seealso::  :ref:`convert <function-convert>`,  :ref:`toint <function-toint>`,  :ref:`touint <function-touint>`

Example
*******

.. include:: ../../../../test/doc/core/convert.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/convert.txt
  :literal:
