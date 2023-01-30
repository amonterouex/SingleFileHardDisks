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

    std::cout << "Excess pore size width (0-0.866] : ";
    std::getline(std::cin, tempvalue);
    double eps = std::stod(tempvalue);
    if(eps<=0.0 || eps>sqrt(3)/2){
        std::cout << "ERROR: Value of excess pore size parameter must be larger than 0 and lower than 0.866" << std::endl;
        return 1;
    }

    std::cout << "Minimum pressure (reduced units)) : ";
    std::getline(std::cin, tempvalue);
    double pmin = std::stod(tempvalue);
    if(pmin<=0.0){
        std::cout << "ERROR: Value of pressure must be a positive number" << std::endl;
        return 1;
    }

    std::cout << "Maximum pressure (reduced units)) : ";
    std::getline(std::cin, tempvalue);
    double pmax = std::stod(tempvalue);
    if(pmax <= pmin){
        std::cout << "ERROR: Value of pmax must be higher than pmin" << std::endl;
        return 1;
    }

    std::cout << "Number of p values computed in between : ";
    std::getline(std::cin, tempvalue);
    int pnum = std::stoi(tempvalue);
    if( fmod(std::stod(tempvalue),1) != 0 || pnum<2){
        std::cout << "ERROR: Number of computed pvalues must be an integer > 1" << std::endl;
        return 1;
    }

    std::cout << "Discretization paremeter : ";
    std::getline(std::cin, tempvalue);
    int nsize = std::stoi(tempvalue);
    if( fmod(std::stod(tempvalue),1) != 0 || nsize<2){
        std::cout << "ERROR: Value of discretization parameter must be a positive integer > 1" << std::endl;
        return 1;
    }

    /*
    std::cout << "Do you wish to export equation of ? (y/n)";
    std::getline(std::cin, tempvalue);
    std::string outfiles = tempvalue;
    if( outfiles != "y" && outfiles != "n"){
        std::cout << "ERROR: Input character not recognized." << std::endl;
        return 1;
    }
    */

    std::string outfiles="y";

    double density;
    Eigen::Matrix<double, Eigen::Dynamic, 1> eigvec;
    //Divide pressure interval in equally spaced values
    std::vector<double> pvalues (pnum, 0.0);
    std::vector<double> dvalues (pnum, 0.0);
    double pstep = (pmax-pmin)/(pnum-1);
    for(int pidx=0;pidx<pnum;pidx++){
        pvalues[pidx] = pmin + pstep * (double)pidx;
        computeDensity(eps, pvalues[pidx], nsize, &dvalues[pidx], &eigvec);
    }

   
    std::cout << "\n************************" << std::endl;
    std::cout << "Epsilon =   " << eps << std::endl;
    std::cout << "Pressure =  [" << pmin << ", " << pmax << "]" << std::endl;
    std::cout << "************************" << std::endl;
    if (outfiles == "n"){
        std::cout << "No output files produced" << std::endl;
    }
    if (outfiles == "y"){
        std::cout << "Writing file equation_of_state.txt..." << std::endl;
        std::cout << "   ...exporting in a column-like format without headers:" << std::endl;
        std::cout << "\t (density) \t (Z)" << std::endl;
        double dy = (eps/(nsize-1));
        std::ofstream ofile;
        ofile.open ("equation_of_state.txt");
        for(int i=0;i<pvalues.size();i++){
            if (i<=4)  std::cout << std::fixed << std::setprecision(6)<<  "\t" <<dvalues[i] << "\t" << pvalues[i]/dvalues[i] << std::endl;
            ofile << dvalues[i] << "\t" << pvalues[i]/dvalues[i] << std::endl;           
        }
        ofile.close();
        std::cout << "    ...done." << std::endl;
        
    }
    std::cout << "************************" << std::endl;

    return 0;
    
}