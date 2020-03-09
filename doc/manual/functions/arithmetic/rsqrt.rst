.. _function-rsqrt:

#####
rsqrt
#####

**Required header:** ``#include <eve/function/rsqrt.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ rsqrt = {};
   }

Function object computing the inverse of the square root value of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise inverse square root of the :ref:`Value <concept-ieeevalue>`.

Parameter
*********

* Instance of a :ref:`Value <concept-value>`.

Return value
**************

* A value with the same type as the parameter.

Options
*******

  - with :ref:`raw_ <feature-decorator>` decorator: if any fast and dirty intrinsic exists it 
    will be used with generally good speed but very poor accuracy.

Example
*******

.. include:: ../../../../test/doc/core/rsqrt.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/rsqrt.txt
  :literal:
