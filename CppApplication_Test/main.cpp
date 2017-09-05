/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: A.Iovbak
 *
 * Created on September 5, 2017, 1:00 PM
 */

#include "header.hpp"

int main(int argc, char** argv) {
    
    cout << "Hello from multifile project!" << endl;
    std::vector<int> v = {1, 2, 3, 4, 5, 10, 20, 90, 200, 77};
    for (int i = 0; i < 10; i++) {
        cout << v[i] << endl;
    }
    
    system("pause");
    
    return 0;
}




