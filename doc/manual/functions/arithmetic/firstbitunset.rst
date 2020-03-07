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

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise first bit not set (beginning with the least significant bit) of the :ref:`Value <concept-value>`.

.. rubric:: Parameter

* Instance of a :ref:`Integral Value <concept-integralvalue>`.

.. rubric:: Return value

* A value with the same type as the parameter.


Example
*******

.. include:: ../../../../test/doc/core/firstbitunset.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/firstbitunset.txt
  :literal:
