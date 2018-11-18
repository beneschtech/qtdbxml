# qtdbxml
Stores XML data in a database in a versioned manner using QT

This project is a library which allows you to store XML files in a database, complete with tracked revisions.

The connection parameters can either come from an initialization function which you pass all of those in,
or from an environment variable named XMLCONFIG, which will be a base64 encoded JSON string.

A database can also contain a "magic" string (up to 64 chars) that can be used as additional security
to ensure that you are connecting to the correct database.

The library will create a DOM structure based on inherited objects based on QT xml objects.
As you modify these objects, changes can be stored, but only the parts that were changed which will then create a new revision
The revisions can be queried and have either a default message in place or allow you to specify a message.
The userid will come from either the system libraries if none specified, or if specified will use that.

Tools needed to build:

QT > 5.7
C++11 capable compiler
QT Database driver of choice

I developed this in postgresql but it can be used in any database QT supports.

Please see the DB directory for the latest SQL definition file for creating a database with these tables, or adding to an existing database.

Notes:

The SQL user is not the same as the XML config user.
The initial data load or import is big, but the changes after are only deltas

Easy building steps:
qmake qtdbxml.pro CONFIG-=debug CONFIG+=release
make
make install
