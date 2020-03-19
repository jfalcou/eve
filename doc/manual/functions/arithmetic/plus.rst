.. _function-plus:

##########
plus
##########

**Required header:** ``#include <eve/function/plus.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ plus = {};
   }

Function object returning the input value :ref:`Value <concept-value>`.
Infix notation: `+` can be used.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Returns the unchanged input value.

Parameter
**********

* ``x``: Instance of a  :ref:`Value <concept-value>`.

Return value
**************

* A value with the sampe type as the parameter.

.. seealso::  :ref:`minus <function-minus>`

Example
*******

.. include:: ../../../../test/doc/core/plus.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/plus.txt
  :literal:
