#include <iostream>
#include "../../../External/include/VectorN.hpp"
#include "../../../External/include/MatrixNM.hpp"
#include "../../../External/include/Matrix4.hpp"
#define _USE_MATH_DEFINES
#include "math.h"

int main()
{
    //VECTOR
    /*
    Vector v(3, {5,7,8});
    std::cout << v << std::endl;
    Vector m(3, {5,3,1});
    //std::cout << m << std::endl;
    //std::cout << -m << std::endl;
    //Vector p = m + v;
    //std::cout << p << std::endl;
    //Vector o = v - m;
    //std::cout << o << std::endl;
    //Vector a = v.Opp();
    //std::cout << a << std::endl;
    //std::cout << v.Norm() << std::endl;
    //std::cout << v.Add(m) << std::endl;
    //std::cout << v.DotProduct(m) << std::endl;
    //std::cout << Vector::Determinant(v,m) << std::endl;
    std::cout << Vector::CrossProduct(v,m) << std::endl;
    //std::cout << Vector::Angle(v,m) << std::endl;
    //std::cout << Vector::Dist(v,m) << std::endl;
    Vector v(3, { 1,5,3 });
    Vector v2(3, { 1,3,3 });

    std::cout << Vector::CrossProduct(v,v2) << std::endl;
    */


    //MATRIX
    /*
    Matrix matrix(10, 10, { 
        {1,2,3,4,5,6,7,8,9,10},
        {1,2,3,4,5,6,7,8,9,10},
        {1,2,3,4,5,6,7,8,9,10},
        {1,2,3,4,5,6,7,8,9,10},
        {1,2,3,4,5,6,7,8,9,10},
        {1,2,3,4,5,6,7,8,9,10},
        {1,2,3,4,5,6,7,8,9,10},
        {1,2,3,4,5,6,7,8,9,10},
        {1,2,3,4,5,6,7,8,9,10},
        {1,2,3,4,5,6,7,8,9,10},
        {1,2,3,4,5,6,7,8,9,10},
        {1,2,3,4,5,6,7,8,9,10}
        });

    Matrix matrix2(9, 10, {
        {1,2,3,4,5,6,7,8,9,10},
        {1,2,3,4,5,6,7,8,9,10},
        {1,2,3,4,5,6,7,8,9,10},
        {1,2,3,4,5,6,7,8,9,10},
        {1,2,3,4,5,6,7,8,9,10},
        {1,2,3,4,5,6,7,8,9,10},
        {1,2,3,4,5,6,7,8,9,10},
        {1,2,3,4,5,6,7,8,9,10},
        {1,2,3,4,5,6,7,8,9,10},
        {1,2,3,4,5,6,7,8,9,10}
        });
    Matrix matrix1(3, 3, {
        {1,-1,2},
        {3, 2, 1},
        {2,-3,-2}
        });

    Matrix matrix2(3, 3, {
        {2,-1,0},
        {-1,2,-1},
        {0,-1,2}
        });

    Matrix matrix3(2, 2, {
        {1,2},
        {3,4}
        });

    Matrix matrix4(3, 3, {
        {1,2,3},
        {4,5,6},
        {7,8,9}
        });
        */
    /*
    std::cout << matrix1 << std::endl;
    std::cout << matrix1.Diag() << std::endl;
    std::cout << matrix1.Trace() << std::endl;
    std::cout << matrix1.Opp() << std::endl;
    std::cout << matrix1.Transpose() << std::endl;
    //std::cout << Matrix::Add(matrix1, matrix2) << std::endl;
    std::cout << Matrix::MultiplyBy(matrix1, 10) << std::endl;
    //std::cout << Matrix::MultiplyBy(matrix1, matrix2) << std::endl;
    //std::cout << Matrix::MultiplyBy(matrix1, Matrix::Rotation2D(30)) << std::endl;
    //std::cout << Matrix::MultiplyBy(Matrix::Scaling2D(Vector(2,2)), matrix1) << std::endl;
    //std::cout << Matrix::Rotation3D(M_PI/6, Vector(3,{1,0,0})) << std::endl;
    //std::cout << Matrix::Rotation3D(M_PI / 6, Vector(3, { 0,1,0 })) << std::endl;
    //std::cout << Matrix::Rotation3D(M_PI / 6, Vector(3, { 0,0,1 })) << std::endl;
    std::cout << Matrix::Scaling3D(Vector(3, { 2,3,12 })) << std::endl;
    std::cout << Matrix::MultiplyBy(matrix1, Matrix::Scaling3D(Vector(3, { 2,3,12 }))) << std::endl;
    //std::cout << matrix.matrixData.size() << std::endl;
    //std::cout << matrix.row << " " << matrix.column << std::endl;
    */
    //std::cout << Matrix::PivotGaussJordan(matrix1.Augment(Matrix::Identity(3))) << std::endl;
    //std::cout << Matrix::Inverse(matrix1) << std::endl;
    //std::cout << Matrix::TRS(Vector(3, { 1,1,1 }), Vector(3, { M_PI, M_PI / 4, M_PI / 3 }), Vector(3, { 1,2,3 })) << std::endl;
    //M_PI, M_PI/4, M_PI/3, 1,1,1, 1,2,3
    /*
    std::cout << matrix1.IsSquare() << std::endl;
    std::cout << matrix1.IsDiagonal() << std::endl;
    */
}
