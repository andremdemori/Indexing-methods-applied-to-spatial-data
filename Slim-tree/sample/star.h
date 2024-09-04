//---------------------------------------------------------------------------
// city.h - Implementation of the User Layer
//
// This file implements the 2 classes required by the SlimTree Library User
// Layer.
//
// TCity is the object which will be indexed by a metric tree. It abstracts a
// city. Each city has a name, a latitude and a longitude. TCity defines an
// interface to manipulate its information and also implements the stObject
// interface.
//
// TCityDistanceEvaluator implements the stMetricEvaluator interface. It will
// mesure the distance between 2 TCity instances.
//
// With these classes, it is possible to define and instantiate any metric tree
// defined by the SlimTree Library.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.sc.usp.br)
//          Fabio Jun Takada Chino (chino@icmc.sc.usp.br)
//          André Muniz Demori (demori@lncc.br)
// Copyright (c) 2002 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef starH
#define starH

#include <math.h>
#include <string>
#include <time.h>
#include <ostream>
using namespace std;

// Metric Tree includes
#include </home/demori/teste/arboretumR2/include/arboretum/stUserLayerUtil.h>
#include </home/demori/teste/arboretumR2/include/arboretum/stTypes.h>
#include </home/demori/teste/arboretumR2/include/arboretum/stUtil.h>

//---------------------------------------------------------------------------
// Class TStar
//---------------------------------------------------------------------------
/**
* This class abstracts a star in a map. Each star has an id, ra, dec, u, g, r, i, z.
*
* <P>In addition to data manipulation methods (such as Getdec(), GetobjID()
* and others), this class implements the stObject interface. This interface
* qualifies this object to be indexed by a metric tree implemented by GBDI
* SlimTree Library.
*
* <P>This interface requires no inheritance (because of the use of class
* templates in the Structure Layer) but requires the following methods:
*     - TStar() - A default constructor.
*     - Clone() - Creates a clone of this object.
*     - IsEqual() - Checks if this instance is equal to another.
*     - GetSerializedSize() - Gets the size of the serialized version of this object.
*     - Serialize() - Gets the serialzied version of this object.
*     - Unserialize() - Restores a serialzied object.
*
* <P>Since the array which contains the serialized version of the object must be
* created and destroyed by each object instance, this class will hold this array
* as a buffer of the serialized version of this instance. This buffer will be
* created only if required and will be invalidated every time the object changes
* its values.
*
* <P>The serialized version of the object will be created as follows:<BR>
* <CODE>
* +----------+-----------+--------+<BR>
* | Latitude | Longitude | Name[] |<BR>
* +----------+-----------+--------+<BR>
* </CODE>
*
* <P>Latitude and Logitude are stored as doubles (2 64-bit IEEE floating point
* value) and Name[] is an array of chars with no terminator. Since Name[] has
* a variable size (associated with the name of the city), the serialized form
* will also have a variable number of bytes.
*
* @version 1.0
* @author Fabio Jun Takada Chino
*/
class TStar{
   public:
      /**
      * Default constructor. It creates a city with no name and longitude and
      * latitude set to 0. This constructor is required by stObject interface.
      */
      TStar(){
         ID = "";
         Ra = 0;
         Dec = 0;
         U = 0;
         G = 0;
         R = 0;
         I = 0;
         Z = 0;

         // Invalidate Serialized buffer.
         Serialized = NULL;
      }//end TStar

      /**
      * Creates a new star.
      *
      * @param iD Id of the object.
      * @param ra
      * @param dec
      * @param u
      * @param g
      * @param r
      * @param i
      * @param z
      */
      TStar(const string iD, double ra, double dec, double u, double g, double r, double i, double z){
         ID = iD;
         Ra = ra;
         Dec = dec;
         U = u;
         G = g;
         R = r;
         I = i;
         Z = z;

         // Invalidate Serialized buffer.
         Serialized = NULL;
      }//end TStar

      /**
      * Destroys this instance and releases all associated resources.
      */
      ~TStar(){

         // Does Serialized exist ?
         if (Serialized != NULL){
            // Yes! Dispose it!
            delete [] Serialized;
         }//end if
      }//end TStar

       /**
      * Gets Z.
      */
      double GetZ(){
         return Z;
      }//end Getz

       /**
      * Gets Z.
      */
      double GetI(){
         return I;
      }//end Geti

       /**
      * Gets R.
      */
      double GetR(){
         return R;
      }//end Getr

       /**
      * Gets G.
      */
      double GetG(){
         return G;
      }//end Getg

       /**
      * Gets U.
      */
      double GetU(){
         return U;
      }//end Getu

      /**
      * Gets Dec.
      */
      double GetDec(){
         return Dec;
      }//end Getdec

      /**
      * Gets Ra.
      */
      double GetRa(){
         return Ra;
      }//end Getra

      /**
      * Gets the ID of the star.
      */
      const string & GetID(){
         return ID;
      }//end GetID

      // The following methods are required by the stObject interface.
      /**
      * Creates a perfect clone of this object. This method is required by
      * stObject interface.
      *
      * @return A new instance of TStar wich is a perfect clone of the original
      * instance.
      */
      TStar * Clone(){
         return new TStar(ID, Ra, Dec, U, G, R, I, Z);
      }//end Clone

      /**
      * Checks to see if this object is equal to other. This method is required
      * by  stObject interface.
      *
      * @param obj Another instance of TStar.
      * @return True if they are equal or false otherwise.
      */
      bool IsEqual(TStar *obj){

         return (Ra == obj->GetRa()) &&
                (Dec == obj->GetDec()) &&
                (U == obj->GetU()) &&
                (G == obj->GetG()) &&
                (R == obj->GetR()) &&
                (I == obj->GetI()) &&
                (Z == obj->GetZ());
      }//end IsEqual

      /**
      * Returns the size of the serialized version of this object in bytes.
      * This method is required  by  stObject interface.
      */
      stSize GetSerializedSize(){

         return (sizeof(double) * 7) + ID.length();
      }//end GetSerializedSize

      /**
      * Returns the serialized version of this object.
      * This method is required  by  stObject interface.
      *
      * @warning If you don't know how to serialize an object, this method may
      * be a good example.
      */
      const stByte * Serialize();

      /**
      * Rebuilds a serialized object.
      * This method is required  by  stObject interface.
      *
      * @param data The serialized object.
      * @param datasize The size of the serialized object in bytes.
      * @warning If you don't know how to serialize an object, this methos may
      * be a good example.
      */
      void Unserialize (const stByte *data, stSize datasize);
   private:
      /**
      * The ID of the star.
      */
      string ID;

      /**
      * Star's ra.
      */
      double Ra;

      /**
      * Star's dec.
      */
      double Dec;

      /**
      * Star's u.
      */
      double U;

      /**
      * Star's g.
      */
      double G;

      /**
      * Star's r.
      */
      double R;

      /**
      * Star's i.
      */
      double I;

      /**
      * Star's z.
      */
      double Z;

      /**
      * Serialized version. If NULL, the serialized version is not created.
      */
      stByte * Serialized;
};//end TMapPoint

//---------------------------------------------------------------------------
// Class TCityDistanceEvaluator
//---------------------------------------------------------------------------
/**
* This class implements a metric evaluator for TStar instances. It calculates
* the distance between stars by performing a euclidean distance between star
* coordinates (I know it is not accurate but it is only a sample!!!).
*
* <P>It implements the stMetricEvaluator interface. As stObject interface, the
* stMetricEvaluator interface requires no inheritance and defines 2 methods:
*     - GetDistance() - Calculates the distance between 2 objects.
*     - GetDistance2()  - Calculates the distance between 2 objects raised by 2.
*
* <P>Both methods are defined due to optmization reasons. Since euclidean
* distance raised by 2 is easier to calculate, It will implement GetDistance2()
* and use it to calculate GetDistance() result.
*
* @version 1.0
* @author Fabio Jun Takada Chino
*/
class TStarDistanceEvaluator : public stMetricEvaluatorStatistics{
   public:
      /**
      * Returns the distance between 2 stars. This method is required by
      * stMetricEvaluator interface.
      *
      * @param obj1 Object 1.
      * @param obj2 Object 2.
      */
      stDistance GetDistance(TStar *obj1, TStar *obj2){
         return sqrt(GetDistance2(obj1, obj2));
      }//end GetDistance

      /**
      * Returns the distance between 2 stars raised by the power of 2.
      * This method is required by stMetricEvaluator interface.
      *
      * @param obj1 Object 1.
      * @param obj2 Object 2.
      */
      stDistance GetDistance2(TStar *obj1, TStar *obj2){
         double delta1, delta2;

         UpdateDistanceCount(); // Update Statistics

         delta1 = obj1->GetDec() - obj2->GetDec();
         delta2 = obj1->GetRa() - obj2->GetRa();
         return (delta1 * delta1) + (delta2 * delta2);
      }//end GetDistance2

};//end TStarDistanceEvaluator

//---------------------------------------------------------------------------
// Output operator
//---------------------------------------------------------------------------
/**
* This operator will write a string representation of a city to an outputstream.
*/
ostream & operator << (ostream & out, TStar & star);

#endif //end myobjectH
