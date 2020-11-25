#include <bits/stdc++.h>
#include <chrono>
#include <fstream>

#include "PolygonTriangulation.h"
using namespace std;
using namespace std::chrono;

/*! The main function to demonstrate use of the PolygonTriangulation API*/
int main(int argc, char *argv[]) {
    auto start = high_resolution_clock::now();
    vector<pair<double, double> > vertices = readInput(argc, *argv);
    auto first_lap = high_resolution_clock::now();
    vector<pair<double, double > > output = PolygonTriangulation.triangulate(vertices);
    auto second_lap = high_resolution_clock::now();
    ofstream output_file;
    output_file.open("output.txt");
    for(auto coordinates : output) {
        cout << coordinates.first << " " << coordinates.second;
    }
    cout << "No of triangles: " << output.size() << "\n";
    auto input_time = duration_cast<microseconds>(first_lap - start);
    auto run_time = duration_cast<microseconds>(second_lap - first_lap);
    cout << "\nTime taken for input: " << input_time.count() << "microseconds\n";
    cout << "Total Time taken for Triangulating: " << run_time.count() << "microseconds\n";
    return 0;
}

vector<pair<double, double> > readInput(int size, char *file_name) {
    vector<pair<double, double> > vertices;
    fstream new_file;
    new_file.open(file_name, ios::in);
    if (new_file.is_open()){ 
        string line;
        while(getline(new_file, line)){
            vertices.push_back(make_pair(stod(line.substr(0, 4)), stod(line.substr(4, 8))));
        }
        new_file.close();
    }
    return vertices;
}
