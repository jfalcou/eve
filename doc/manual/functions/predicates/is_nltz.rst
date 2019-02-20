.. _function-is_nltz:

is_nltz
============

**Required header** ``#include <eve/function/is_nltz.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_nltz( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` or :ref:`False <constant-false_>`
according its parameter  :ref:`Value <concept-value>` is not less than :ref:`Zero <constant-Zero>`.

.. seealso::  :ref:`is_not_less <function-is_less>`

Parameters
----------

  - ``lhs``  : values to compare to 0.

Return value
------------

Semantically equivalent to `is_not_less(lhs, Zero(as(lhs)))`

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_nltz.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_nltz.txt
  :literal:

