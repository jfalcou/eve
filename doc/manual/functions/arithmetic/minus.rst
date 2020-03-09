.. _function-minus:

###########
minus
###########

**Required header:** ``#include <eve/function/minus.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ minus = {};
   }

Function object computing the opposite  of a :ref:`Value <concept-value>`.
Infix notation: `-` can be used.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise minus value of the parameter.

Parameters
**********

* Instance of a  :ref:`Value <concept-value>`.

Return value
**************

* A value with the same type as the parameter.

Notes
*****

  - minus on floating point types  changes the bit of sign.

  - conditional call is allowed: ``minus[cond](a)`` is equivalent (but optimized) to ``if_else(cond, minus(a), a)``

  - take care that the infix notation on scalar can imply C++ promotion as it is the original operator.

  - Be aware that for signed integers the opposite of :ref:`Valmin <constant-valmin>` is
    not representable in the input type and the result is undefined.

.. seealso::  :ref:`plus <function-plus>`

Example
*******

.. include:: ../../../../test/doc/core/minus.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/minus.txt
  :literal:
