.. _function-sqrt:

####
sqrt
####

**Required header:** ``#include <eve/function/sqrt.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ sqrt = {};
   }

Function object computing the square root value of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise square root of the :ref:`Value <concept-ieeevalue>`.

Parameter
*********

* Instance of a :ref:`Value <concept-value>`.

Return value
**************

* A value with the same type as the parameter.

Notes
*******

 For postive Integral typed entries the return is the truncation of the real result

Options
*******

  - With the :ref:`raw_ <feature-decorator>` decorator: if any fast and dirty intrinsic exists it will be returned by the  call
    with generally good speed but very poor accuracy.

Example
*******

.. include:: ../../../../test/doc/core/sqrt.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/sqrt.txt
  :literal:
