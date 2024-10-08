Installation
============

Install from source
-------------------
Tenseur can be installed from its source code available at https://github.com/istmarc/tenseur.

The following instructions describe how to clone the repository and install Tenseur on Linux and MacOS:

.. code-block:: bash

   $ git clone https://github.com/istmarc/tenseur.git
   $ cd tenseur
   $ mkdir build
   $ cd build
   $ cmake ..
   $ make install

Set the install prefix:

.. code-block:: bash

   $ cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
   $ make install

