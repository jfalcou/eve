.. _function-firstbitunset:

#############
firstbitunset
#############

**Required header:** ``#include <eve/function/firstbitunset.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ firstbitunset = {};
   }

Function object computing the bit pattern (with the integral parameter type) in which the only bit set is
the first bit not set (beginning with the least significant bit) in the parameter which must satisfy the
:ref:`IntegralValue <concept-integralvalue>` concept.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise first bit  not set (beginning with the least significant bit) of the :ref:`wide <type-wide>`.
* [2] Computes the first bit not set (beginning with the least significant bit) of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide` satisfying :ref:`IntegralValue <concept-integralvalue>` concept.
* **s**: Scalar integral value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.


Example
*******

.. include:: ../../../../test/doc/core/firstbitunset.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/firstbitunset.txt
  :literal:
