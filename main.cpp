
//
//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright © 2016 James Shockey. All rights reserved.
//

/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array.
 *
 */

#include "slist.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

//////////////////////////////////Reference Coordinates


class Airport {
public:
  char code[20];
  double longitude;
  double latitude;

  Airport() {
    strcpy(code, " ");
    longitude = 0;
    latitude = 0;
  }
  ~Airport() {}
};

slist *simpleSortTotal(slist *, double, double);
slist *merge(slist *, slist *, double, double);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

int main() {
  double refLat;
  double refLong;
  ifstream infile;
  int i = 0;
  char cNum[40];
  char temp[40];
  slist *airportArr = new slist(); // Replace array with Linked List

  int airportCount;
  // Airport* a[13500];
  // cout<<"A"<<endl;
  infile.open("airport-codes_US.csv", ifstream::in);
  if (infile.is_open()) {

    int c = 0;
    while (infile.good()) 
    {
      //cout << "loop: " << c << endl;

      Airport *newA = new Airport();

      for (int x = 0; x < 12; x++) {
        //cout<<x<<": ";
        //cout<<"A "<<endl;

        //cout<<infile.good()<<endl;
        if (x == 3) {
          infile.getline(cNum, 256, ',');
          newA->longitude = atof(cNum);
          //cout<<newA->longitude<<endl;
          continue;
        }
        if (x == 4) {
          infile.getline(cNum, 256, ',');
          newA->latitude = atof(cNum);
          //cout<<newA->latitude<<endl;
          continue;
        }
        if (x == 0) {
          infile.getline(newA->code, 256, ',');
          continue;
        }
        if (x == 11) {
         // cout<<infile.good()<<"A"<<endl;
          infile.getline(temp, 256, ',');
          infile.getline(temp, 256, ',');
          //cout<<temp<<endl;
          //cout<<infile.good()<<"B"<<endl;
          continue;
        } else {
          infile.getline(temp, 256, ',');
        }
      }
      //cout<<strcmp(newA->code,"KAUS")<<endl;
      //cout<<newA->code<<" KAUS"<<endl;
      
      if(i==13558){      
        refLong=newA->longitude;
        refLat=newA->latitude;
        //cout<<refLong<<", "<<refLat<<endl;
      }
     
      airportArr->add(newA);

      Airport* airportPointer = static_cast<Airport *>(airportArr->get(c)->data);
      if (!(c % 1000))
        cout << airportPointer->code << " long: " << airportPointer->longitude
             << " lat: " << airportPointer->latitude << endl;

      /*
      if (!(c % 1000))
      {
          cout << airportArr[c]->code << " long: " << airportArr[c]->longitude
      << " lat: " << airportArr[c]->latitude <<  endl; cout <<
      airportArr[c+1]->code << endl; //" long: " << airportArr[c+1]->longitude
      << " lat: " << airportArr[c+1]->latitude <<  endl;
      }
      */

      i++;
      c++;
    }
    airportCount = c - 1;
    infile.close();
    
    Airport * currentAirport;
    Airport * currentAirportPlus1;

    slist * sortedAirportArr = simpleSortTotal(airportArr, refLat,refLong);
    
    for (int c = 0; c < airportCount; c++)
      if (!(c % 1000)) {
        //cout<<c<<endl;

        currentAirport = static_cast<Airport *>(airportArr->get(c)->data);

        //cout<<"B"<<endl;

        currentAirportPlus1 = static_cast<Airport *>(airportArr->get(c+1)->data);
        
        //cout<<"C"<<endl;
      
        cout << currentAirport->code << " long: " << currentAirport->longitude
             << " lat: " << currentAirport->latitude << endl;

        //cout<<"D"<<endl;

        cout << currentAirportPlus1->code
             << " long: " << currentAirportPlus1->longitude
             << " lat: " << currentAirportPlus1->latitude << endl;

        //cout<<"E"<<endl;

        cout << "Distance between " << currentAirport->code << " and "
             << currentAirportPlus1->code << " is "
             << distanceEarth(currentAirport->longitude,
                              currentAirport->latitude,
                              currentAirportPlus1->longitude,
                              currentAirportPlus1->latitude)
             << endl;
        
        //cout<<"F"<<endl;

      }

    for (int c = 0; c < 30; c++)
      {
        Airport *airportA = static_cast<Airport *>(sortedAirportArr->get(c)->data);
        double alat = airportA->latitude;
        double along = airportA->longitude;
        if(distanceEarth(alat, along, refLat, refLong)<100)
          cout<<c+1<<": "<< airportA->code<<": "<<distanceEarth(alat, along, refLat, refLong) << " kilometers" << endl;
      }
    for(int c = 1; c<20;c++){
    Airport* farthestAirport = static_cast<Airport *>(sortedAirportArr->get(sortedAirportArr->size()-c)->data);
    double alat = farthestAirport->latitude;
    double along = farthestAirport->longitude;
    cout<<"\n Farthest Away: "<<farthestAirport->code<<": "<<distanceEarth(alat, along, refLat, refLong)<<"kilometers";
    }
  } else {
    cout << "Error opening file";
  }
}

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) { return (deg * pi / 180); }

//  This function converts radians to decimal degrees
double rad2deg(double rad) { return (rad * 180 / pi); }

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r) / 2);
  v = sin((lon2r - lon1r) / 2);
  return 2.0 * earthRadiusKm *
         asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

/*
        Provide sort routine on linked list
*/


///////mergesort :DDDDDDDDDDDD
slist *simpleSortTotal(slist *s, double refLat, double refLong) {
  int size = s->size();
  if (size == 1)
    return s;

  slist *slist1 = s->subList(0, size / 2);
  slist *slist2 = s->subList(size / 2 , size);

  slist1 = simpleSortTotal(slist1, refLat, refLong);
  slist2 = simpleSortTotal(slist2, refLat, refLong);

  return merge(slist1, slist2, refLat, refLong);
}

slist *merge(slist *a, slist *b, double refLat, double refLong) {
  slist *c = new slist();
  //cout<<"A"<<endl;
  while (a->size() > 0 && b->size() > 0) {
    Airport *airportA = static_cast<Airport *>(a->get(0)->data);
    Airport *airportB = static_cast<Airport *>(b->get(0)->data);
    //cout<<"B"<<endl;

    //cout<<"Airport A Latitude "<<airportA->latitude<<endl;
    //cout<<"Airport A Longitude "<<airportA->longitude<<endl;
    //cout<<"Airport B Latitude "<<airportA->latitude<<endl;
    //cout<<"Airport B Longitude "<<airportA->longitude<<endl;

    double alat = airportA->latitude;
    double along = airportA->longitude;
    double blat = airportB->latitude;
    double blong = airportB->longitude;
    //cout<<"C"<<endl;

    if (distanceEarth(alat, along, refLat, refLong) >
        distanceEarth(blat, blong, refLat, refLong)) {
      c->add(airportB);
      b->remove(0);
    } else {
      c->add(airportA);
      a->remove(0);
    }
    //cout<<"D"<<endl;

  }

  while (a->size() > 0) {
    c->add(a->get(0)->data);
    a->remove(0);
  }

  while (b->size() > 0) {
    c->add(b->get(0)->data);
    b->remove(0);
  }

  return c;
}