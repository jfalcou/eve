.. _function-exponent:

########
exponent
########

**Required header:** ``#include <eve/function/exponent.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ exponent = {};
   }

Function object computing the exponent  of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise  exponent of the :ref:`wide <type-wide>`.
* [2] Computes the exponent of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same integral type associated to the parameter. 

Notes
*****

    The exponent :math:`e` and mantissa :math:`m` of a floating point entry :math:`x` are related by
    :math:`x =  m\times 2^e`, with  :math:`|m| \in [1, 2[` (except for :math:`x = 0`,
    where :math:`m=0` and :math:`e=0` ).



.. seealso::  :ref:`mantissa <function-mantissa>`,  :ref:`ifrexp <function-ifrexp>`,  :ref:`frexp <function-frexp>`, 
 :ref:`ldexp <function-ldexp>`

Example
*******

.. include:: ../../../../test/doc/core/exponent.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/exponent.txt
  :literal:
