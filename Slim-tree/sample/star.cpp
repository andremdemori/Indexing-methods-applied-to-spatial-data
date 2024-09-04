//---------------------------------------------------------------------------
// city.cpp - Implementation of the User Layer
//
// In this file we have the implementation of TStar::Serialize(),
// TStar::Unserialize() and an output operator for TStar (which is not required
// by user layer).
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.sc.usp.br)
//          Fabio Jun Takada Chino (chino@icmc.sc.usp.br)
//          André Muniz Demori (demori@lncc.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#pragma hdrstop
#include "star.h"
#pragma package(smart_init)
#include <iostream>

//---------------------------------------------------------------------------
// Class TStar
//---------------------------------------------------------------------------
/**
* Returns the serialized version of this object.
* This method is required  by  stObject interface.
* @warning If you don't know how to serialize an object, this method may
* be a good example.
*/
const stByte * TStar::Serialize(){
   double * d;

   // Is there a seralized version ?
   if (Serialized == NULL){
      // No! Lets build the serialized version.

      // The first thing we need to do is to allocate resources...
      Serialized = new stByte[GetSerializedSize()];

      // We will organize it in this manner:
      // +----------+-----------+--------+
      // | Latitude | Longitude | Name[] |
      // +----------+-----------+--------+
      // So, write the Longitude and Latitude should be written to serialized
      // version as follows
      d = (double *) Serialized; // If you are not familiar with pointers, this
                                // action may be tricky! Be careful!
      d[0] = Ra;
      d[1] = Dec;
      d[2] = U;
      d[3] = G;
      d[4] = R;
      d[5] = I;
      d[6] = Z;

      // Now, write the name after the 7 doubles...
      memcpy(Serialized + (sizeof(double) * 7), ID.c_str(), ID.length());
   }//end if

   return Serialized;
}//end TStar::Serialize
/**
* Rebuilds a serialized object.
* This method is required  by  stObject interface.
*
* @param data The serialized object.
* @param datasize The size of the serialized object in bytes.
* @warning If you don't know how to serialize an object, this method may
* be a good example.
*/
void TStar::Unserialize(const stByte *data, stSize datasize){
   double * d;
   stSize strl;

   // This is the reverse of Serialize(). So the steps are similar.
   // Remember, the format of the serizalized object is
   // +----------+-----------+--------+
   // | Latitude | Longitude | Name[] |
   // +----------+-----------+--------+

   // Read Longitude and Latitude
   d = (double *) data;  // If you are not familiar with pointers, this action may be tricky! Be careful!

   Ra = d[0];
   Dec = d[1];
   U = d[2];
   G = d[3];
   R = d[4];
   I = d[5];
   Z = d[6];

   // To read the name, we must discover its size first. Since it is the only
   // variable length field, we can get it back by subtract the fixed size
   // from the serialized size.
   strl = datasize - (sizeof(double) * 7);

   // Now we know the size, lets get it from the serialized version.
   ID.assign((char *)(data + (sizeof(double) * 7)), strl);

   // Since we have changed the object contents, we must invalidate the old
   // serialized version if it exists. In fact we, may copy the given serialized
   // version of tbe new object to the buffer but we don't want to spend memory.
   if (Serialized != NULL){
      delete [] Serialized;
      Serialized = NULL;
   }//end if
}//end TStar::Unserialize

//---------------------------------------------------------------------------
// Output operator
//---------------------------------------------------------------------------
/**
* This operator will write a string representation of a star to an outputstream.
*/
ostream & operator << (ostream & out, TStar & star){

   out << "[Star=" << star.GetID() << ";Ra=" <<
         star.GetRa() << ";Dec=" <<
         star.GetDec() << ";U=" <<
         star.GetU() << ";G" <<
         star.GetG() << ";R" <<
         star.GetR() << ";I" <<
         star.GetI() << ";Z" <<
         star.GetZ() << "]";
   return out;
}//end operator <<

