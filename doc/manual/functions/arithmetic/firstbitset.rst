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

Function object computing the bit pattern in which the only bit set (if it exists) is
the first bit set (beginning with the least significant bit) in the input.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise first bit set (beginning with the least significant bit) of the :ref:`Value <concept-value>`.

.. rubric:: Parameter

* Instance of a :ref:`Integral Value <concept-integralvalue>`.

Return value
**************

* A value with the same type as the parameter.

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
