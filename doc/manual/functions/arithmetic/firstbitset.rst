.. _function-firstbitset:

############
firstbitset
############

**Required header:** ``#include <eve/function/firstbitset.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ firstbitset = {};
   }

Function object computing the bit pattern (with the integral parameter type) in which the only bit set (if it exists) is
the first bit set (beginning with the least significant bit) in the parameter which must satisfy the
:ref:`IntegralValue <concept-integralvalue>` concept.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise rfirst bit set (beginning with the least significant bit) of the :ref:`wide <type-wide>`.
* [2] Computes the first bit set (beginning with the least significant bit) of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide` satisfying :ref:`IntegralValue <concept-integralvalue>` concept.
* **s**: Scalar integral value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.

Note
****

  - With input 0 returns 0.

Example
*******

.. include:: ../../../../test/doc/core/firstbitset.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/firstbitset.txt
  :literal:
