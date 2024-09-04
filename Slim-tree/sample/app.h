//---------------------------------------------------------------------------
// app.h - Implementation of the application.
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
//          André Muniz Demori (demori@lncc.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#ifndef appH
#define appH

// Metric Tree includes
#include </home/demori/teste/arboretumR2/include/arboretum/stMetricTree.h>
#include </home/demori/teste/arboretumR2/include/arboretum/stPlainDiskPageManager.h>
#include </home/demori/teste/arboretumR2/include/arboretum/stDiskPageManager.h>
#include </home/demori/teste/arboretumR2/include/arboretum/stMemoryPageManager.h>
#include </home/demori/teste/arboretumR2/include/arboretum/stSlimTree.h>
#include </home/demori/teste/arboretumR2/include/arboretum/stMetricTree.h>


// My object
#include "star.h"

#include <string.h>
#include <fstream>
 
#define DATASET "/home/demori/teste/arboretumR2/sample/sample-01_slimtree_2/datasets/Total0000008col.txt"
#define QUERYSTARFILE "/home/demori/teste/arboretumR2/sample/sample-01_slimtree_2/datasets/Gerador/TestRADEC.txt"
//---------------------------------------------------------------------------
// class TApp
//---------------------------------------------------------------------------
class TApp{
   public:
      /**
      * This is the type used by the result.
      */
      typedef stResult < TStar > myResult;

      typedef stMetricTree < TStar, TStarDistanceEvaluator > MetricTree;

      /**
      * This is the type of the Slim-Tree defined by TStar and
      * TStarDistanceEvaluator.
      */
      typedef stSlimTree < TStar, TStarDistanceEvaluator > mySlimTree;

      /**
      * Creates a new instance of this class.
      */
      TApp(){
         PageManager = NULL;
         SlimTree = NULL;
      }//end TApp

      /**
      * Initializes the application.
      *
      * @param pageSize
      * @param minOccup
      * @param quantidade
      * @param prefix
      */
      void Init(){
         // To create it in disk
         CreateDiskPageManager();
         // Creates the tree
         CreateTree();
      }//end Init

      /**
      * Runs the application.
      *
      * @param DataPath
      * @param DataQueryPath
      */
      void Run();

      /**
      * Deinitialize the application.
      */
      void Done();

   private:

      /**
      * The Page Manager for SlimTree.
      */
      stPlainDiskPageManager * PageManager;

      /**
      * The SlimTree.
      */
      mySlimTree * SlimTree;

      /**
      * Vector for holding the query objects.
      */
      vector <TStar *> queryObjects;

      /**
      * Creates a disk page manager. It must be called before CreateTree().
      */
      void CreateDiskPageManager();

      /**
      * Creates a tree using the current PageManager.
      */
      void CreateTree();

      /**
      * Loads the tree from file with a set of stars.
      */
      void LoadTree(char * fileName);

      /**
      * Loads the vector for queries.
      */
      void LoadVectorFromFile(char * fileName);

      /**
      * Performs the queries and outputs its results.
      */
      void PerformQueries();

      void PerformNearestQuery();

      void PerformRangeQuery();

};//end TApp

#endif //end appH
