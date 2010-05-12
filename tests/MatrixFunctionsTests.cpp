#include "UnitTest++/UnitTest++.h"
#include "UnitTest++/ReportAssert.h"
#include "../Matrix.h"
#include "../MatrixFunctions.h"
#include "boost/tuple/tuple.hpp"
#include <vector>
using namespace std;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

    These are tests for the functions in MatrixFunctions.h

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

struct TestMatrixFunctions
{
    TestMatrixFunctions()
    {
        m = new Matrix(3,3);
        I = new Matrix(3,3);
        I->populateIdentity();
    }
    ~TestMatrixFunctions()
    {
        delete m;
        delete I;
    }
        Matrix *m; // 3x3 matrix
        Matrix *I; // 3x3 identity matrix
};

TEST_FIXTURE(TestMatrixFunctions, TestGaussJordan)
{
    delete m;
    double ar[] = {1,2,3,3,4,5,7,2,5}; // non symmetric, non singular 3x3 matrix
    m = new Matrix(ar,3,3);
    Matrix n = m->inverse();
    Matrix sol = gaussJordan(*m,*I);
    CHECK(sol==n);
}

TEST_FIXTURE(TestMatrixFunctions, TestGaussianElimination)
{
    delete m;
    double ar[] = {1,2,3,3,4,5,7,2,5};
    m = new Matrix(ar,3,3);
    Matrix n = m->inverse();
    Matrix sol = gaussianElimination(*m,*I);
    CHECK(sol==n);
}


TEST_FIXTURE(TestMatrixFunctions, TestLUPDecompose)
{
    delete m;
    double ar[] = {1,2,3,3,4,5,7,2,5};
    m = new Matrix(ar,3,3);

    // get its decomposition
    boost::tuple<Matrix,Matrix,Matrix> lu = LUPDecompose(*m);
    Matrix L = lu.get<0>();
    Matrix U = lu.get<1>();
    Matrix P = lu.get<2>();
    
    Matrix newm = L*U*P;
    CHECK(newm==(*m));
}

TEST_FIXTURE(TestMatrixFunctions, TestIsSymmetric)
{
    CHECK(isSymmetric(*I));
}

TEST_FIXTURE(TestMatrixFunctions, TestIsSymmetricFalse)
{
    delete m;
    double ar[] = {1,2,3,3,4,5,7,2,5}; // non symmetric, non singular 3x3 matrix
    m = new Matrix(ar,3,3);
    CHECK(isSymmetric(*m)==false);
}


int main(int argc, char * argv[])
{
    return UnitTest::RunAllTests();
}