.. _function-bitofsign:

#########
bitofsign
#########

**Required header:** ``#include <eve/function/bitofsign.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ bitofsign = {};
   }

Function object computing the bit of sign of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T x ) noexcept;

* Returns the element-wise masking of all bits of the parameter except the highest one.

.. rubric:: Parameter

* Instance of a :ref:`Value <concept-value>`.

Return value
**************

* A value with the same type as the parameter.

Notes
******

 - This function is not a sign function: the results elements are always 
   :math:`\pm0` for any :ref:`IEEEValue <concept-ieeevalue>` and has undefined behaviour on Nans.

.. seealso::  :ref:`sign <function-sign>`,  :ref:`signz <function-signnz>`

Example
*******

.. include:: ../../../../test/doc/core/bitofsign.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/bitofsign.txt
  :literal:
