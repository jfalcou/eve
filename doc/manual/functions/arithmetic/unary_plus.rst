.. _function-unary_plus:

##########
unary_plus
##########

**Required header:** ``#include <eve/function/unary_plus.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ unary_plus = {};
   }

Function object returning the input value :ref:`Value <concept-value>`.
Infix notation: `+` can be used.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1,2] Returns the unchanged input value.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter. *TODO*

Notes
*****

  - take care that the infix notation on scalar an imply C++ promotion as it is the original operator.

.. seealso::  :ref:`unary_minus <function-unary_minus>`

Example
*******

.. include:: ../../../../test/doc/core/unary_plus.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/unary_plus.txt
  :literal:
