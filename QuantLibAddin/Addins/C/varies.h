
/*
 Copyright (C) 2004, 2005 Eric Ehlers

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef qla_varies_h
#define qla_varies_h

typedef enum {FALSE=0, TRUE} Boolean;
typedef enum { LONG, DOUBLE, BOOL, CHARP, 
    /* not yet implemented
    LONG_ARRAY, DOUBLE_ARRAY, BOOL_ARRAY, CHARP_ARRAY,
    LONG_MATRIX, DOUBLE_MATRIX, BOOL_MATRIX, CHARP_MATRIX 
    */ } Type;

typedef union {
    long AsLong;
    double AsDouble;
    Boolean AsBool;
    char* AsCharP;
/* not yet implemented
    long* AsLongArray;
    double* AsDoubleArray;
    Boolean* AsBoolArray;
    char** AsCharPArray;
    long** AsLongMatrix;
    double** AsDoubleMatrix;
    Boolean** AsBoolMatrix;
    char*** AsCharPMatrix;
*/
} DataUnion;

typedef struct {
    DataUnion data;
    Type type;
    int numRows;
    int numCols;
//    char* Label;
} Varies;

void freeVaries(Varies *vl);
void initialize();

#endif

