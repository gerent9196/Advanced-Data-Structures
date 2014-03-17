#include "RTree.h"
#include <iostream>
using namespace std;


void RTree::hilbertSort(std::vector<IPoint *>& points){
    long long max_x = points[0]->getX();
    long long max_y = points[0]->getY();
//    for(int i=0; i<points.size(); i++){
 //       cout<< "\t"<< points.at(i)->getX() << " "<< points.at(i)->getY();
 //   }
  //  cout << "\n points size:"<< points.size();
    for(int i=1; i<points.size(); i++){
        if (points.at(i)->getX() > max_x)
            max_x = points.at(i)->getX();
        if (points.at(i)->getY() > max_y)
            max_y = points.at(i)->getY();
    }
    long long max_xy = (long long) max_x> max_y ? max_x : max_y;
   // cout << "\nMax xy:"<< max_xy;
    long long temp_max_xy ;
    temp_max_xy = 2;
    while(true){
        if (temp_max_xy>= max_xy)
            break;
        temp_max_xy*=2; 
    }
    //cout << "\n power of 2:" << temp_max_xy << "\n";
    long long w,d;
    std::vector<long long> distance;
    for(int i=0; i< points.size(); i++){
        long long x = points.at(i)->getX();
        long long y = points.at(i)->getY();
      //  cout << "\n x: "<<x<<"y: "<<y;
        long long dist = 0;
            w = temp_max_xy/2;
        while(w!=0){
            
            //finding the quadrant;
            int quad;
            if(((x < w)) and (y < w))
               quad = 0;
            else if(((x < w)) and (y >= w))
               quad = 1;
            else if(((x >= w)) and (y >= w))
               quad = 2;
            else if(((x >= w)) and (y < w))
               quad =3;
            else 
                cout <<"Out of quadrant range";

            dist+=(quad*w*w);
       //     cout <<"\n cumulative distance is:"<< dist;
        //    cout << "\n quad is :"<<quad << " w is :"<< w;
            long long temp;
            if(quad == 0){
                temp = x;
                x = y;
                y = temp;
            }
            else if( quad == 1){
                y = y-w;
            }
            else if (quad == 2){
                x = x-w;
                y = y-w;
            }
            else if (quad == 3){
                temp = x;
                x = w-y-1;
                y = w*2- temp -1;
            }
            w = w/2;
         //   cout << "new x: "<< x<< " new y: "<<y;
       } 
//       cout << "\ndist is:"<< dist;
       distance.push_back(dist);
       cout << "\ndist:"<< dist;
    }
    shellSort(points, distance);
}

void RTree::insertionSort(long long inc, long long start, std::vector<IPoint*>& points , std::vector<long long>& distance){
    for(long long key_index = start; key_index < distance.size(); key_index += inc){
     long long key = distance[key_index];
     IPoint* key2 = points[key_index];
     long long other_index = key_index - inc;
     while(other_index >= 0 && distance[other_index] > key){
       distance[other_index + inc] = distance[other_index];
       points[other_index + inc] = points[other_index];
       other_index -= inc;
     }
     distance[other_index + inc] = key;
     points[other_index + inc] = key2;
   }
 }
 
 void RTree::shellSort(std::vector<IPoint *>& points ,std::vector<long long>& distance){
   std::vector<long long> increments;
   //produce the h's
   for(long long h = 1; h < distance.size(); ){
     increments.push_back(h);
     h = (3 * h) + 1;
   }
   //loop over the different h's
   for(long long i = increments.size() - 1; i >= 0; --i){
     long long h = increments[i];
     //loop over the number of sub-arrays produced by the current h
     for(long long start = 0; start <= h; ++start){
       insertionSort(h, start, points, distance);
     }
   }
 }
 
void RTree::bulkInsert(std::vector<IPoint *>& points){
    hilbertSort(points);
    this->RPoints = points;
    }
std::vector<IPoint *> RTree::findWithin(IPoint * top_left, IPoint * bottom_right){
     
    std::vector<IPoint*> final;
    for(int i=0; i< RPoints.size(); i++){
        if ((RPoints.at(i)->getX() >= top_left->getX()) and (RPoints.at(i)->getX() <= bottom_right->getX())
            and (RPoints.at(i)->getY()>=top_left->getY()) and (RPoints.at(i)->getY() <= bottom_right->getY()))
            final.push_back(RPoints.at(i));
    }

    return final;

}
