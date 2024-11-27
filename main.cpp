#include "LidarDriver.h"
#include <iostream>
#include <string>
#include <vector>

int main()
{
    LidarDriver lidar = LidarDriver(0.5);
    vector<double> scansione;
    vector<double> scansione2;
    vector<double> scansione3;
    vector<double> scansione4;
    vector<double> oldScan;

    for (int i =1; i<400; i++) scansione.push_back(i);
    for (int i =1; i<300; i++) scansione2.push_back(-1);
    for (int i =1; i<400; i++) scansione3.push_back(-2);
    for (int i =1; i<400; i++) scansione4.push_back(5);
    
    cout<<lidar.get_distance(10)<<endl;

    lidar.new_scan(scansione);
    lidar.new_scan(scansione2);
    lidar.new_scan(scansione3);
    lidar.new_scan(scansione4);

    cout<<"\n Ultima scansione inserita: "<<lidar<<endl;

    oldScan = lidar.get_scan();

    lidar.new_scan(scansione4);
    lidar.new_scan(scansione3);

    lidar.clear_buffer();

    lidar.new_scan(scansione2);
    lidar.new_scan(scansione4);

    lidar.new_scan(scansione3);
    lidar.new_scan(scansione);

    cout<<"\nLettura all'angolo 10 gradi dell'ultima scansione inserita: "<<lidar.get_distance(10)<<endl;
    cout<<"\n Ultima scansione inserita: "<<lidar<<endl;

    return 0;
}
