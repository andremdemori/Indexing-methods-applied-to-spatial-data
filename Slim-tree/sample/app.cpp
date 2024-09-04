//---------------------------------------------------------------------------
// app.cpp - Implementation of the application.
//
// To change the behavior of this application, comment and uncomment lines at
// TApp::Init() and TApp::Query().
//
// Authors: Marcos Rodrigues Vieira (mrvieira@icmc.usp.br)
//          André Muniz Demori (demori@lncc.br)
// Copyright (c) 2003 GBDI-ICMC-USP
//---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <math.h>
#pragma hdrstop
#include "app.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
// Class TApp
//------------------------------------------------------------------------------
void TApp::CreateTree(){
   // create for Slim-Tree
   SlimTree = new mySlimTree(PageManager);
}//end TApp::CreateTree

//------------------------------------------------------------------------------
void TApp::CreateDiskPageManager(){
   //for SlimTree
   PageManager = new stPlainDiskPageManager("SlimTree.dat", 1024);
}//end TApp::CreateDiskPageManager

//------------------------------------------------------------------------------
void TApp::Run(){

std::cout << std::fixed << std::setprecision(25);


   // Lets load the tree with a lot values from the file.
   //cout << "\n\nAdding objects in the SlimTree";

    clock_t x;
    int y;
    y = clock();

    LoadTree(DATASET);

    y = clock() - y;
    cout << "\nTotal tree creation time: " <<((float)y)/CLOCKS_PER_SEC << " segundos";

   cout << "\n\nLoading the query file";
   LoadVectorFromFile(QUERYSTARFILE);

   if (queryObjects.size() > 0){
      // Do 500 queries.
      PerformQueries();
   }//end if
   // Hold the screen.
   cout << "\n\nFinished the whole test!";
}//end TApp::Run

//------------------------------------------------------------------------------
void TApp::Done(){

   if (this->SlimTree != NULL){
      delete this->SlimTree;
   }//end if
   if (this->PageManager != NULL){
      delete this->PageManager;
   }//end if

   // delete the vetor of queries.
   for (unsigned int i = 0; i < queryObjects.size(); i++){
      delete (queryObjects.at(i));
   }//end for
}//end TApp::Done

//------------------------------------------------------------------------------
void TApp::LoadTree(char * fileName){
   ifstream in(fileName);
   char starID[200];
   double dRa,dDec,dU,dG,dR,dI,dZ;
   long w = 0;
   TStar * star;

   if (SlimTree!=NULL){

      if (in.is_open()){
         //cout << "\nLoading objects ";
         while(in.getline(starID, 200, '\t')){
            in >> dRa;
            in >> dDec;
            in >> dU;
            in >> dG;
            in >> dR;
            in >> dI;
            in >> dZ;
            in.ignore();
            star = new TStar(starID, dRa, dDec, dU, dG, dR, dI, dZ);
            SlimTree->Add(star);
            delete star;
            w++;
            if (w % 10 == 0){
               //cout << '.';
            }//end if*/
         }//end while
         //cout << " Added " << SlimTree->GetNumberOfObjects() << " objects ";
         in.close();
      }else{
         cout << "\nProblem to open the file.";
      }//end if

   }else{
      cout << "\n Zero object added!!";
   }//end if

}//end TApp::LoadTree

//------------------------------------------------------------------------------
void TApp::LoadVectorFromFile(char * fileName){
   ifstream in(fileName);
   char starID[200];
   int cont;
   double dRa, dDec, dU, dG, dR, dI, dZ;

   // clear before using.
   queryObjects.clear();

   if (in.is_open()){
      cout << "\nLoading query objects ";
      cont = 0;
      while(in.getline(starID, 200, '\t')){
            in >> dRa;
            in >> dDec;
            in >> dU;
            in >> dG;
            in >> dR;
            in >> dI;
            in >> dZ;
         in.ignore();
         this->queryObjects.insert(queryObjects.end(), new TStar(starID, dRa, dDec, dU, dG, dR, dI, dZ));
         cont++;
      }//end while
      cout << " Added " << queryObjects.size() << " query objects ";
      in.close();
   }else{
      cout << "\nProblem to open the query file.";
      cout << "\n Zero object added!!\n";
   }//end if
}//end TApp::LoadVectorFromFile

//------------------------------------------------------------------------------
void TApp::PerformQueries(){
   if (SlimTree){
      cout << "\nStarting Statistics for Range Query with SlimTree.... ";
      PerformRangeQuery();
      cout << " Ok\n";

     // cout << "\nStarting Statistics for Nearest Query with SlimTree.... ";
     // PerformNearestQuery();
     // cout << " Ok\n";
   }//end if
}//end TApp::PerformQuery

//------------------------------------------------------------------------------
   /*----------------

void TApp::PerformRangeQuery(){

   myResult * result;
   stDistance radius;
   clock_t start, end;
   unsigned int size;
   unsigned int i;
   long double time_1;
   long double time_2;
   long double time_3;
   long double time_4;

   if (SlimTree){
      size = queryObjects.size();
      // reset the statistics
      PageManager->ResetStatistics();
      SlimTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      clock_t start_2, end;
      start_2 = clock();

      for (i = 0; i < size; i++) //size = 9999
      {
            result = SlimTree->RangeQuery(queryObjects[i], 0.267626657835);

            //Ra and Dec from object
             //cout << "\n\nObject: \n";
             //cout << "RA: " << queryObjects[i]->GetRa() << "\tDec: "<< queryObjects[i]->GetDec() << "\n\n";


           //escreve em disco o Ra e Dec do objeto e dos vizinhos dele
            ofstream arquivo_1;
            arquivo_1.open("objetos_e_vizinhos/objetos_e_vizinhos_0267626657835.txt",ios::app);
            arquivo_1 << "\n\nObject: \n" << "RA: " << queryObjects[i]->GetRa() << "\tDec: " << queryObjects[i]->GetDec() << "\n\n" << "Neighbors (Ra,Dec): \n";
            arquivo_1.close();
            result->GetRa_Dec_Neighbors_RangeQuery_0267626657835();


            //Ra and Dec from neighbors
             //cout << "Neighbors (Ra,Dec): \n";
            // cout << result->GetRa_Dec_Neighbors_RangeQuery() << "\n\n";


            //distancias
             //cout << "\nRadius: " << result->GetRadius();
             //cout << "\nDistances from neighbors:\n" << result->GetDistancesRangeQuery();
            result->GetDistancesRangeQuery_0267626657835();



            /*
             //tempo de cada um / qtd de objetos

            if(i == 0)
            {
                time_1 = ((double )end-(double )start_2) / 1000000.0;
                cout <<( (double)time_1) / size << "(s)\n";
            }else if(i == 1){
                time_2 = ((double )end-(double )start_2) / 1000000.0;
                time_4 = ((double)time_2);
                time_3 = ((double )time_2-(double )time_1) / size;
                cout << ( (double)time_3) << "(s)\n";
            }else{
                time_2 = ((double )end-(double )start_2) / 1000000.0;
                time_3 = ((double )time_2-(double )time_4) / size;
                time_4 = ((double)time_2);
                std::cout << std::fixed << std::setprecision(15);
                cout << ( (double)time_3) << "(s)\n";
            }

            end = clock();
            */

/*--------------------


           //tempo
            ofstream arquivo;
            arquivo.open("soma_dos_tempos/soma_dos_tempos_0.267626657835.txt",ios::app);
            // soma do tempo de cada um
            std::cout << std::fixed << std::setprecision(15);
            //cout << "\nTotal Time: " << ((double )end-(double )start_2) / 1000000.0 << "(s)\n";
            end = clock();
            time_1 = ((double )end-(double )start_2) / 1000000.0;
            arquivo << time_1 << "\n";
            arquivo.close();

            delete result;
      }//end for

      end = clock();
      //cout << "\nRadius: " << result->GetRadius();

      //cout << "\nDistances: \n" << result->GetDistancesRangeQuery(); //pega o ultimo

      cout << "\n\nRadius: " << result->GetRadius();

      cout << "\nAverage: " << time_1/size << "(s)";

      cout << "\nVariance: " << (time_1 - (time_1/size))/size << "(s)";

      cout << "\nTotal Time: " << ((double )end-(double )start) / 1000000.0 << "(s)";
      // is divided for queryObjects to get the everage
      cout << "\nAvg Disk Accesses: " << (double )PageManager->GetReadCount() / (double )size;
      // is divided for queryObjects to get the everage
      cout << "\nAvg Distance Calculations: " <<
         (double )SlimTree->GetMetricEvaluator()->GetDistanceCount() / (double )size;

    }//end if


      if (SlimTree){
      size = queryObjects.size();
      // reset the statistics
      PageManager->ResetStatistics();
      SlimTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      clock_t start_2, end;
      start_2 = clock();
      for (i = 0; i < size; i++) //size = 9999
      {
            result = SlimTree->RangeQuery(queryObjects[i], 0.66137703749);


            //Ra and Dec from object
             //cout << "\n\nObject: \n";
             //cout << "RA: " << queryObjects[i]->GetRa() << "\tDec: "<< queryObjects[i]->GetDec() << "\n\n";


           //escreve em disco o Ra e Dec do objeto e dos vizinhos dele
            ofstream arquivo_1;
            arquivo_1.open("objetos_e_vizinhos/objetos_e_vizinhos_066137703749.txt",ios::app);
            arquivo_1 << "\n\nObject: \n" << "RA: " << queryObjects[i]->GetRa() << "\tDec: " << queryObjects[i]->GetDec() << "\n\n" << "Neighbors (Ra,Dec): \n";
            arquivo_1.close();
            result->GetRa_Dec_Neighbors_RangeQuery_066137703749();


            //Ra and Dec from neighbors
             //cout << "Neighbors (Ra,Dec): \n";
            // cout << result->GetRa_Dec_Neighbors_RangeQuery() << "\n\n";


            //distancias
             //cout << "\nRadius: " << result->GetRadius();
             //cout << "\nDistances from neighbors:\n" << result->GetDistancesRangeQuery();
            result->GetDistancesRangeQuery_066137703749();


           //tempo
            ofstream arquivo;
            arquivo.open("soma_dos_tempos/soma_dos_tempos_0.66137703749.txt",ios::app);
            // soma do tempo de cada um
            std::cout << std::fixed << std::setprecision(15);
            //cout << "\nTotal Time: " << ((double )end-(double )start_2) / 1000000.0 << "(s)\n";
            end = clock();
            time_1 = ((double )end-(double )start_2) / 1000000.0;
            arquivo << time_1 << "\n";
            arquivo.close();
            delete result;
      }//end for

      end = clock();
      //cout << "\nRadius: " << result->GetRadius();

      //cout << "\nDistances: \n" << result->GetDistancesRangeQuery(); //pega o ultimo

      cout << "\n\nRadius: " << result->GetRadius();

      cout << "\nAverage: " << time_1/size;

      cout << "\nVariance: " << (time_1 - (time_1/size))/size;

      cout << "\nTotal Time: " << ((double )end-(double )start) / 1000000.0 << "(s)";
      // is divided for queryObjects to get the everage
      cout << "\nAvg Disk Accesses: " << (double )PageManager->GetReadCount() / (double )size;
      // is divided for queryObjects to get the everage
      cout << "\nAvg Distance Calculations: " <<
         (double )SlimTree->GetMetricEvaluator()->GetDistanceCount() / (double )size;


   }//end if



      if (SlimTree){
      size = queryObjects.size();
      // reset the statistics
      PageManager->ResetStatistics();
      SlimTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      clock_t start_2, end;
      start_2 = clock();
      for (i = 0; i < size; i++) //size = 9999
      {
            result = SlimTree->RangeQuery(queryObjects[i], 0.799373869089);



            //Ra and Dec from object
             //cout << "\n\nObject: \n";
             //cout << "RA: " << queryObjects[i]->GetRa() << "\tDec: "<< queryObjects[i]->GetDec() << "\n\n";


           //escreve em disco o Ra e Dec do objeto e dos vizinhos dele
            ofstream arquivo_1;
            arquivo_1.open("objetos_e_vizinhos/objetos_e_vizinhos_0799373869089.txt",ios::app);
            arquivo_1 << "\n\nObject: \n" << "RA: " << queryObjects[i]->GetRa() << "\tDec: " << queryObjects[i]->GetDec() << "\n\n" << "Neighbors (Ra,Dec): \n";
            arquivo_1.close();
            result->GetRa_Dec_Neighbors_RangeQuery_0799373869089();


            //Ra and Dec from neighbors
             //cout << "Neighbors (Ra,Dec): \n";
            // cout << result->GetRa_Dec_Neighbors_RangeQuery() << "\n\n";


            //distancias
             //cout << "\nRadius: " << result->GetRadius();
             //cout << "\nDistances from neighbors:\n" << result->GetDistancesRangeQuery();
            result->GetDistancesRangeQuery_0799373869089();


           //tempo
            ofstream arquivo;
            arquivo.open("soma_dos_tempos/soma_dos_tempos_0.799373869089.txt",ios::app);
            // soma do tempo de cada um
            std::cout << std::fixed << std::setprecision(15);
            //cout << "\nTotal Time: " << ((double )end-(double )start_2) / 1000000.0 << "(s)\n";
            end = clock();
            time_1 = ((double )end-(double )start_2) / 1000000.0;
            arquivo << time_1 << "\n";
            arquivo.close();


            delete result;
      }//end for

      end = clock();
      //cout << "\nRadius: " << result->GetRadius();

      //cout << "\nDistances: \n" << result->GetDistancesRangeQuery(); //pega o ultimo

      cout << "\n\nRadius: " << result->GetRadius();

      cout << "\nAverage: " << time_1/size;

      cout << "\nVariance: " << (time_1 - (time_1/size))/size;

      cout << "\nTotal Time: " << ((double )end-(double )start) / 1000000.0 << "(s)";
      // is divided for queryObjects to get the everage
      cout << "\nAvg Disk Accesses: " << (double )PageManager->GetReadCount() / (double )size;
      // is divided for queryObjects to get the everage
      cout << "\nAvg Distance Calculations: " <<
         (double )SlimTree->GetMetricEvaluator()->GetDistanceCount() / (double )size;


   }//end if




      if (SlimTree){
      size = queryObjects.size();
      // reset the statistics
      PageManager->ResetStatistics();
      SlimTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      clock_t start_2, end;
      start_2 = clock();
      for (i = 0; i < size; i++) //size = 9999
      {
            result = SlimTree->RangeQuery(queryObjects[i], 0.624763269697);


            //Ra and Dec from object
             //cout << "\n\nObject: \n";
             //cout << "RA: " << queryObjects[i]->GetRa() << "\tDec: "<< queryObjects[i]->GetDec() << "\n\n";


           //escreve em disco o Ra e Dec do objeto e dos vizinhos dele
            ofstream arquivo_1;
            arquivo_1.open("objetos_e_vizinhos/objetos_e_vizinhos_0624763269697.txt",ios::app);
            arquivo_1 << "\n\nObject: \n" << "RA: " << queryObjects[i]->GetRa() << "\tDec: " << queryObjects[i]->GetDec() << "\n\n" << "Neighbors (Ra,Dec): \n";
            arquivo_1.close();
            result->GetRa_Dec_Neighbors_RangeQuery_0624763269697();


            //Ra and Dec from neighbors
             //cout << "Neighbors (Ra,Dec): \n";
            // cout << result->GetRa_Dec_Neighbors_RangeQuery() << "\n\n";


            //distancias
             //cout << "\nRadius: " << result->GetRadius();
             //cout << "\nDistances from neighbors:\n" << result->GetDistancesRangeQuery();
            result->GetDistancesRangeQuery_0624763269697();


           //tempo
            ofstream arquivo;
            arquivo.open("soma_dos_tempos/soma_dos_tempos_0.624763269697.txt",ios::app);
            // soma do tempo de cada um
            std::cout << std::fixed << std::setprecision(15);
            //cout << "\nTotal Time: " << ((double )end-(double )start_2) / 1000000.0 << "(s)\n";
            end = clock();
            time_1 = ((double )end-(double )start_2) / 1000000.0;
            arquivo << time_1 << "\n";
            arquivo.close();

            delete result;
      }//end for

      end = clock();
      //cout << "\nRadius: " << result->GetRadius();

      //cout << "\nDistances: \n" << result->GetDistancesRangeQuery(); //pega o ultimo

      cout << "\n\nRadius: " << result->GetRadius();

      cout << "\nAverage: " << time_1/size;

      cout << "\nVariance: " << (time_1 - (time_1/size))/size;

      cout << "\nTotal Time: " << ((double )end-(double )start) / 1000000.0 << "(s)";
      // is divided for queryObjects to get the everage
      cout << "\nAvg Disk Accesses: " << (double )PageManager->GetReadCount() / (double )size;
      // is divided for queryObjects to get the everage
      cout << "\nAvg Distance Calculations: " <<
         (double )SlimTree->GetMetricEvaluator()->GetDistanceCount() / (double )size;


   }//end if




      if (SlimTree){
      size = queryObjects.size();
      // reset the statistics
      PageManager->ResetStatistics();
      SlimTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      clock_t start_2, end;
      start_2 = clock();
      for (i = 0; i < size; i++) //size = 9999
      {
            result = SlimTree->RangeQuery(queryObjects[i], 1.0);


            //Ra and Dec from object
             //cout << "\n\nObject: \n";
             //cout << "RA: " << queryObjects[i]->GetRa() << "\tDec: "<< queryObjects[i]->GetDec() << "\n\n";


           //escreve em disco o Ra e Dec do objeto e dos vizinhos dele
            ofstream arquivo_1;
            arquivo_1.open("objetos_e_vizinhos/objetos_e_vizinhos_010.txt",ios::app);
            arquivo_1 << "\n\nObject: \n" << "RA: " << queryObjects[i]->GetRa() << "\tDec: " << queryObjects[i]->GetDec() << "\n\n" << "Neighbors (Ra,Dec): \n";
            arquivo_1.close();
            result->GetRa_Dec_Neighbors_RangeQuery_010();


            //Ra and Dec from neighbors
             //cout << "Neighbors (Ra,Dec): \n";
            // cout << result->GetRa_Dec_Neighbors_RangeQuery() << "\n\n";


            //distancias
             //cout << "\nRadius: " << result->GetRadius();
             //cout << "\nDistances from neighbors:\n" << result->GetDistancesRangeQuery();
            result->GetDistancesRangeQuery_10();


           //tempo
            ofstream arquivo;
            arquivo.open("soma_dos_tempos/soma_dos_tempos_1.0.txt",ios::app);
            // soma do tempo de cada um
            std::cout << std::fixed << std::setprecision(15);
            //cout << "\nTotal Time: " << ((double )end-(double )start_2) / 1000000.0 << "(s)\n";
            end = clock();
            time_1 = ((double )end-(double )start_2) / 1000000.0;
            arquivo << time_1 << "\n";
            arquivo.close();

            delete result;
      }//end for

      end = clock();
      //cout << "\nRadius: " << result->GetRadius();

      //cout << "\nDistances: \n" << result->GetDistancesRangeQuery(); //pega o ultimo

      cout << "\n\nRadius: " << result->GetRadius();

      cout << "\nAverage: " << time_1/size;

      cout << "\nVariance: " << (time_1 - (time_1/size))/size;

      cout << "\nTotal Time: " << ((double )end-(double )start) / 1000000.0 << "(s)";
      // is divided for queryObjects to get the everage
      cout << "\nAvg Disk Accesses: " << (double )PageManager->GetReadCount() / (double )size;
      // is divided for queryObjects to get the everage
      cout << "\nAvg Distance Calculations: " <<
         (double )SlimTree->GetMetricEvaluator()->GetDistanceCount() / (double )size;


   }//end if





      if (SlimTree){
      size = queryObjects.size();
      // reset the statistics
      PageManager->ResetStatistics();
      SlimTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      clock_t start_2, end;
      start_2 = clock();
      for (i = 0; i < size; i++) //size = 9999
      {
            result = SlimTree->RangeQuery(queryObjects[i], 0.763196789371);


            //Ra and Dec from object
             //cout << "\n\nObject: \n";
             //cout << "RA: " << queryObjects[i]->GetRa() << "\tDec: "<< queryObjects[i]->GetDec() << "\n\n";


           //escreve em disco o Ra e Dec do objeto e dos vizinhos dele
            ofstream arquivo_1;
            arquivo_1.open("objetos_e_vizinhos/objetos_e_vizinhos_0763196789371.txt",ios::app);
            arquivo_1 << "\n\nObject: \n" << "RA: " << queryObjects[i]->GetRa() << "\tDec: " << queryObjects[i]->GetDec() << "\n\n" << "Neighbors (Ra,Dec): \n";
            arquivo_1.close();
            result->GetRa_Dec_Neighbors_RangeQuery_0763196789371();


            //Ra and Dec from neighbors
             //cout << "Neighbors (Ra,Dec): \n";
            // cout << result->GetRa_Dec_Neighbors_RangeQuery() << "\n\n";


            //distancias
             //cout << "\nRadius: " << result->GetRadius();
             //cout << "\nDistances from neighbors:\n" << result->GetDistancesRangeQuery();
            result->GetDistancesRangeQuery_0763196789371();


           //tempo
            ofstream arquivo;
            arquivo.open("soma_dos_tempos/soma_dos_tempos_0.763196789371.txt",ios::app);
            // soma do tempo de cada um
            std::cout << std::fixed << std::setprecision(15);
            //cout << "\nTotal Time: " << ((double )end-(double )start_2) / 1000000.0 << "(s)\n";
            end = clock();
            time_1 = ((double )end-(double )start_2) / 1000000.0;
            arquivo << time_1 << "\n";
            arquivo.close();

            delete result;
      }//end for

      end = clock();
      //cout << "\nRadius: " << result->GetRadius();

      //cout << "\nDistances: \n" << result->GetDistancesRangeQuery(); //pega o ultimo

      cout << "\n\nRadius: " << result->GetRadius();

      cout << "\nAverage: " << time_1/size;

      cout << "\nVariance: " << (time_1 - (time_1/size))/size;

      cout << "\nTotal Time: " << ((double )end-(double )start) / 1000000.0 << "(s)";
      // is divided for queryObjects to get the everage
      cout << "\nAvg Disk Accesses: " << (double )PageManager->GetReadCount() / (double )size;
      // is divided for queryObjects to get the everage
      cout << "\nAvg Distance Calculations: " <<
         (double )SlimTree->GetMetricEvaluator()->GetDistanceCount() / (double )size;


   }//end if
*/

//pega as 100 distancias geradas aleatóriamente

void TApp::PerformRangeQuery(){

std::cout << std::fixed << std::setprecision(25);

      double v[100];

      for(int p = 0 ; p <= 99 ; p++)
      {

         ifstream arquivo_distancias;
         string linha;

         arquivo_distancias.open("/home/demori/teste/arboretumR2/sample/sample-01_slimtree_2/datasets/Gerador/TestDist.csv");

         if(arquivo_distancias.is_open())
         {
           while(getline(arquivo_distancias,linha))
           {
              double linha_double = atof(linha.c_str());

                v[p] = linha_double;
           }
         }
      }

   myResult * result;
   stDistance radius;
   unsigned int size;
   unsigned int i;
   long double time_1;
   long double time_2;
   float temp[10000];
   unsigned int contador = 0;
   float soma = 0;


      if (SlimTree)
      {
          size = queryObjects.size();
          // reset the statistics
          PageManager->ResetStatistics();
          SlimTree->GetMetricEvaluator()->ResetStatistics();


          for(int k = 0 ; k <= 99 ; k++)
          {
                contador = 0;

                  for (i = 0; i < size; i++)
                  {

                            clock_t t;
                            int f;
                            t = clock();

                            result = SlimTree->RangeQuery(queryObjects[k], v[i]);

                            t = clock() - t;
                            temp[contador] = ((float)t)/CLOCKS_PER_SEC;
                            contador = contador + 1;

                    delete result;
                  }//end for

                  float somador = temp[0];
                  float media = 0;

                  for(int u = 0 ; u < 99 ; u++)
                  {
                        somador = somador + temp[u+1];
                  }

                  media = somador / size;
                  cout << "\n\nObjeto: " << queryObjects[k]->GetID() << "\n";
                  cout << "Total time: " << somador << "\n";
                  cout << "Average: " << media << "\n";
                  cout << "Variance: " << (somador - media)/size << "\n";
                  cout << "Standart deviation: " << sqrt((somador - media)/size);
                  cout << "\n\n";


            }//end for

       }//end if

}//end TApp::PerformRangeQuery

//------------------------------------------------------------------------------
void TApp::PerformNearestQuery(){

   myResult * result;
   clock_t start, end;
   unsigned int size;
   unsigned int i;

   if (SlimTree){
      size = queryObjects.size();
      PageManager->ResetStatistics();
      SlimTree->GetMetricEvaluator()->ResetStatistics();
      start = clock();
      for (i = 0; i < size; i++){
         result = SlimTree->NearestQuery(queryObjects[i], 15);
          cout << "\nK: " << result->GetK();
          cout << "\nDistances: \n" << result->GetDistancesNearestQuery();

         delete result;
      }//end for
      end = clock();

      cout << "\nTotal Time: " << ((double )end-(double )start) / 1000.0 << "(s)";
      // is divided for queryObjects to get the everage
      cout << "\nAvg Disk Accesses: " << (double )PageManager->GetReadCount() / (double )size;
      // is divided for queryObjects to get the everage
      cout << "\nAvg Distance Calculations: " <<
         (double )SlimTree->GetMetricEvaluator()->GetDistanceCount() / (double )size;
   }//end if
}//end TApp::PerformNearestQuery
