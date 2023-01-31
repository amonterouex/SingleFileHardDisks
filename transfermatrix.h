#ifndef TRANSFERMATRIX_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define TRANSFERMATRIX_H

#include <Eigen/Eigenvalues>

double a(double s);
double y(int i,double eps,int nsize);

int computeDensity(double eps, double p, int nsize, double *density,Eigen::Matrix<double, Eigen::Dynamic, 1> *eigvec);

#endif