.. _function-cbrt:

####
cbrt
####

**Required header:** ``#include <eve/function/cbrt.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ cbrt = {};
   }

Function object computing the cubic root  of a :ref:`IEEEValue <concept-ieeevalue>`

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise  cubic root of the :ref:`IEEEValue <concept-ieeevalue>`
* [2] Computes the cubic root of the floating point scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.


.. seealso::  :ref:`sqrt <function-sqrt>`,  :ref:`rsqrt <function-rsqrt>`

Example
*******

.. include:: ../../../../test/doc/core/cbrt.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/cbrt.txt
  :literal:
