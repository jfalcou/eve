.. _function-exponentbits:

############
exponentbits
############

**Required header:** ``#include <eve/function/exponentbits.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ exponentbits = {};
   }

    This function object returns the exponent bits of its arguments as an integral based value,
    the other bits (sign and mantissa) being just masked.


Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s) noexcept;

.. rubric:: Parameters

* **v**, **m**: Instance of :ref:`type-wide`.
* **s**, **n**: Scalar values.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter which must be floating-point based.

Example
*******

.. include:: ../../../../test/doc/exponentbits.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/exponentbits.txt
  :literal:



 