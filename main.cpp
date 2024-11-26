#include "LidarDriver.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    LidarDriver lidar = LidarDriver(0.5, 10);
    vector<double> scansione;
    vector<double> scansione2;
    vector<double> scansione3;
    vector<double> scansione4;
    
    for (int i =1; i<400; i++) scansione.push_back(i);
    for (int i =1; i<300; i++) scansione2.push_back(-1);
    for (int i =1; i<400; i++) scansione3.push_back(-2);
    for (int i =1; i<400; i++) scansione4.push_back(5);
    
    lidar.new_scan(scansione3);
    lidar.new_scan(scansione4);
    lidar.new_scan(scansione);
    lidar.new_scan(scansione2);
    lidar.new_scan(scansione);
    lidar.new_scan(scansione2);
    lidar.new_scan(scansione);
    lidar.new_scan(scansione2);
    lidar.new_scan(scansione);
    lidar.new_scan(scansione);
    
    lidar.get_memory();
    
    /*cout<<"-----------------------" <<endl;
    cout<   lidar.get_distance(5)<<endl;
    cout<<"-----------------------" <<endl;
    vector<double> scan =   lidar.get_scan();
    for (int i =0; i<scan.size(); i++) cout<<scan[i]<<" ";
    cout<<endl;
    cout<<"-----------------------" <<endl;
    lidar.get_puntatori();
    lidar.new_scan(scansione);
    lidar.get_puntatori();
    lidar.new_scan(scansione2);
    lidar.get_puntatori();
    cout<<"-----------------------" <<endl;
    lidar.get_memory();
    cout<<"-----------------------" <<endl;
    scan =  lidar.get_scan();
    for (int i =0; i<scan.size(); i++) cout<<scan[i]<<" ";
    cout<<endl;
    cout<<"-----------------------" <<endl;

    
    cout<<endl;
    cout<   lidar;
    cout<<endl;
    
    lidar.clear_buffer();
    cout<   lidar;*/
    
    vector<double> app;
    cout<<"---------------------------1------------------------------"<<endl;
    app =   lidar.get_scan();
    for (int i =0; i<app.size(); i++) cout<<app[i]<<" ";
    cout<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    lidar.get_memory();
    cout<<"---------------------------2------------------------------"<<endl;
    app =   lidar.get_scan();
    for (int i =0; i<app.size(); i++) cout<<app[i]<<" ";
    cout<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    lidar.get_memory();
    cout<<"---------------------------3------------------------------"<<endl;
    app =   lidar.get_scan();
    for (int i =0; i<app.size(); i++) cout<<app[i]<<" ";
    cout<<endl;
    cout<<"----------------------------------------------------------"<<endl;
    lidar.get_memory();
    return 0;
}

