.. _feature-decorator:

Decorators
==========

A :ref:`feature-decorator` type is usable with many **EVE** object functions to
produce different behaviours

Syntax
------

  If `xxx_` is a decorator and `func` a function object that allows the decorator use
  a call to ``func_(...)`` can be replaced by ``xxx_(func_)(...)``

Existing decorators
-------------------

  - ``raw_``           : perhaps speedier but less accurate version
  - ``pedantic_``      : perhaps slower but acting conforming to standard in corner cases
  - ``regular`` `      : as no decorator
  - ``saturated``      : saturated oeration
  - ``numeric_```      : prefer non Nan numbers to Nans when possible


Example
-------

.. include:: ../../../test/doc/core/deco.cpp
  :literal:

Possible output:

.. include:: ../../../test/doc/core/deco.txt
  :literal:

