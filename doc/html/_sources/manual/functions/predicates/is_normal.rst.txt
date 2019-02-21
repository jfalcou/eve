.. _function-is_normal:

is_normal
============

**Required header** ``#include <eve/function/is_normal.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr as_logical_t<Value> is_normal( Value lhs ) noexcept
   }


This function returns :ref:`True <constant-true_>` if and only if the parameter is normal
 
.. seealso::  :ref:`is_not_denormal <function-is_not_denormal>`,  :ref:`is_finite <function-is_finite>`,  :ref:`is_nez <function-is_nez>`

Parameters
----------

  - ``lhs``  : values to test.

Return value
------------

Semantically equivalent to ``is_not_denormal(lhs) && is_finite(lhs) && is_nez(lhs)``

Options
-------


Example
-------

.. include:: ../../../../test/doc/is_normal.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_normal.txt
  :literal:

