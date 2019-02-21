.. _function-is_not_inf:

is_not_inf
============

**Required header** ``#include <eve/function/is_not_inf.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_not_inf( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` if and only if the parameter is not infinite

.. seealso::  :ref:`Nan <constant-nan>`, :ref:`logical_or <function-logical_or>>`

Parameters
----------

  - ``lhs``  : values to test.

Return value
------------

Semantically equivalent to ``logical_or(is_less(abs(lhs), Inf(as(lhs))), is_nan(lhs))``

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_not_inf.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_not_inf.txt
  :literal:

