.. _function-is_finite:

is_finite
============

**Required header** ``#include <eve/function/is_finite.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_finite( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` if and only if the parameter is finite

.. seealso::  :ref:`is_inf <function-is_inf>`, :ref:`is_nan <function-is_nan>`, :ref:`logical_not <function-logical_not>`

Parameters
----------

  - ``lhs``  : values to test.

Return value
------------

Semantically equivalent to ``logical_not(is_inf(lhs)||is_nan(lhs)))``

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_finite.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_finite.txt
  :literal:

