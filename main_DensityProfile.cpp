#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h> 
#include <unistd.h>
#include <cmath>
#include "transfermatrix.h"
#include <Eigen/Eigenvalues>

int main() 
{
    std::string tempvalue;

    //Ask for the excess pore size and make sure the value is valid.
    std::cout << "Excess pore size width [0-0.866] : ";
    std::getline(std::cin, tempvalue);
    double eps = std::stod(tempvalue);
    if(eps<=0.0 || eps>sqrt(3)/2){
        std::cout << "ERROR: Value of excess pore size parameter must be larger than 0 and lower than 0.866" << std::endl;
        return 1;
    }

    //Ask for the pressure value and make sure it is valid.
    std::cout << "Pressure (reduced units) : ";
    std::getline(std::cin, tempvalue);
    double p = std::stod(tempvalue);
    if(p<=0.0){
        std::cout << "ERROR: Value of pressure must be a positive number" << std::endl;
        return 1;
    }

    //Discretization parameter.The user must make sure it is large enough to produce a converged output.
    std::cout << "Discretization paremeter : ";
    std::getline(std::cin, tempvalue);
    int nsize = std::stoi(tempvalue);
    if( fmod(std::stod(tempvalue),1) != 0 || nsize<2){
        std::cout << "ERROR: Value of discretization parameter must be a positive integer > 1" << std::endl;
        return 1;
    }

    //Ask whether the user whishes to export the density profile information
    std::cout << "Do you wish to export density profile information? (y/n) : ";
    std::getline(std::cin, tempvalue);
    std::string outfiles = tempvalue;
    if( outfiles != "y" && outfiles != "n"){
        std::cout << "ERROR: Input character not recognized." << std::endl;
        return 1;
    }

    double density;
    Eigen::Matrix<double, Eigen::Dynamic, 1> eigvec;
    //Compute density
    computeDensity(eps, p, nsize, &density, &eigvec);

    std::cout << "\n************************" << std::endl;
    std::cout << "*****  RESULTS  ********" << std::endl;
    std::cout << "************************" << std::endl;
    std::cout << "Epsilon =   " << eps << std::endl;
    std::cout << "Pressure =  " << p << std::endl;
    std::cout << "Density =   " << density << std::endl;
    std::cout << "************************" << std::endl;
    if (outfiles == "n"){
        std::cout << "No output files produced" << std::endl;
    }
    if (outfiles == "y"){
        std::cout << "Writing file density_profile.txt..." << std::endl;
        std::cout << "   ...exporting in a column-like format without headers:" << std::endl;
        std::cout << "\t (y) \t (normalized density profile)" << std::endl;
        double dy = (eps/(nsize-1));
        std::ofstream ofile;
        ofile.open ("density_profile.txt");
        for(int i=0;i<eigvec.size();i++){
            if (i<=4)  std::cout << std::fixed << std::setprecision(6)<<  "\t"<< y(i, eps, nsize) << "\t" << eigvec(i)*eigvec(i)/dy << std::endl;   
            ofile << y(i, eps, nsize) << "\t" << eigvec(i)*eigvec(i)/dy << std::endl;           
        }
        ofile.close();
        std::cout << "   ...done." << std::endl;
        
    }
    std::cout << "************************" << std::endl;

    return 0;
    
}