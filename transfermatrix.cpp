#include "transfermatrix.h"  // player.h must be in the current directory. or use relative or absolute path to it. e.g #include "include/player.h"
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

//Longitudinal separation at contact of two disks
double a(double s){
    return sqrt(1.0-s*s);
}

// y(i) when discretizing the problem
double y(int i,double eps,int nsize){
    return eps*((double)i/(nsize-1)-0.5);
}

//Given epsilon, p and nsize, it computes the linear density and the eigenvector (show squared value gives the density profile)
int computeDensity(double eps, double p, int nsize, double *density,Eigen::Matrix<double, Eigen::Dynamic, 1> *eigvec){
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> K;
    //Create matrix K
    K.resize(nsize, nsize);
    for (int i=0; i<nsize; i++){
        for(int j=0; j<nsize; j++){
            K(i,j) = eps/nsize*exp(-p * a(y(i,eps,nsize)-y(j,eps,nsize)));
        }
    }
    //The matrix is symmetric, compute its eigenvalues and eigenvectors
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> es;
    es.compute(K);
    *eigvec = es.eigenvectors().col(nsize-1);
    double eigval = es.eigenvalues()(nsize-1);

    //Compute the density
    double stemp = 0;
    for (int i=0; i<nsize; i++){
        for(int j=0; j<nsize; j++){
            stemp = stemp + eigvec->coeffRef(i)*eigvec->coeffRef(j)*K(i,j)*a(y(i,eps,nsize)-y(j,eps,nsize));
        }
    }

    *density = p/(1.0+p*stemp/eigval); //density
    //*density = 1.0+p*stemp/eigval; //Z

    return 0;
}