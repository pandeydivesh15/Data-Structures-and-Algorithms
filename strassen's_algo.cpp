#include <iostream>
#include <cmath>
/*
 *STL headers
 */
#include <vector>
#include <iterator>

using namespace std;

vector< vector<int> > add_matrices(vector< vector<int> >A, vector< vector<int> >B){
	int l = A.size();
	for(unsigned i = 0; i < l; ++i) {
		for(unsigned j = 0; j < l; ++j) {
			A[i][j] = A[i][j] + B[i][j];
		}
	}
	return A;
}

vector< vector<int> > sub_matrices(vector< vector<int> > A, vector< vector<int> > B){
	int l = A.size();
	for(unsigned i = 0; i < l; ++i) {
		for(unsigned j = 0; j < l; ++j) {
			A[i][j] = A[i][j] - B[i][j];
		}
	}
	return A;
}

void add_zero_padding(vector< vector<int> > &A, vector< vector<int> > &B){
	int l = A.size();
	for(unsigned i = 0; i < l; ++i) {
		A[i].push_back(0);
		B[i].push_back(0);
	}
	A.push_back(vector<int>(l+1));
	B.push_back(vector<int>(l+1));
	return;

}

vector< vector<int> > multiply_matrix(vector< vector<int> > A, vector< vector<int> > B){
	
	int l = A.size();
	if(l == 1) {
		A[0][0] = A[0][0] * B[0][0] ;
		return A;
	}
	if(l % 2 != 0){
		add_zero_padding(A, B);
		l++;
	}
	
	int separator = l/2;

	vector< vector<int> > A11(separator, vector<int>(separator));
	vector< vector<int> > B11(separator, vector<int>(separator));
	vector< vector<int> > A12(separator, vector<int>(l-separator));
	vector< vector<int> > B12(separator, vector<int>(l-separator));
	vector< vector<int> > A21(l-separator, vector<int>(separator));
	vector< vector<int> > B21(l-separator, vector<int>(separator));
	vector< vector<int> > A22(l-separator, vector<int>(l-separator));
	vector< vector<int> > B22(l-separator, vector<int>(l-separator));  

	for(unsigned i = 0; i < separator; ++i) {
		for(unsigned j = 0; j < separator; ++j) {
			A11[i][j] = A[i][j];
			B11[i][j] = B[i][j];
		}
	}
	for(unsigned i = 0; i < separator; ++i) {
		for(unsigned j = 0; j < l-separator; ++j) {
			A12[i][j] = A[i][separator + j];
			B12[i][j] = B[i][separator + j];
		}
	}

	for(unsigned i = 0; i < l-separator; ++i) {
		for(unsigned j = 0; j < separator; ++j) {
			A21[i][j] = A[separator + i][j];
			B21[i][j] = B[separator + i][j];
		}
	}
	for(unsigned i = 0; i < separator; ++i) {
		for(unsigned j = 0; j < l-separator; ++j) {
			A22[i][j] = A[separator + i][separator + j];
			B22[i][j] = B[separator + i][separator + j];
		}
	}

	vector< vector<int> > S1 = sub_matrices(B12, B22);
	vector< vector<int> > S2 = add_matrices(A11, A12);
	vector< vector<int> > S3 = add_matrices(A21, A22);
	vector< vector<int> > S4 = sub_matrices(B21, B11);
	vector< vector<int> > S5 = add_matrices(A11, A22);
	vector< vector<int> > S6 = add_matrices(B11, B22);
	vector< vector<int> > S7 = sub_matrices(A12, A22);
	vector< vector<int> > S8 = add_matrices(B21, B22);
	vector< vector<int> > S9 = sub_matrices(A11, A21);
	vector< vector<int> > S10 = add_matrices(B11, B12);

	vector< vector<int> > P1 = multiply_matrix(A11, S1);
	vector< vector<int> > P2 = multiply_matrix(S2, B22);
	vector< vector<int> > P3 = multiply_matrix(S3, B11);
	vector< vector<int> > P4 = multiply_matrix(A22, S4);
	vector< vector<int> > P5 = multiply_matrix(S5, S6);
	vector< vector<int> > P6 = multiply_matrix(S7, S8);
	vector< vector<int> > P7 = multiply_matrix(S9, S10);

	vector< vector<int> > ANS(l, vector<int>(l));

	for(unsigned i = 0; i < separator; ++i) {
		for(unsigned j = 0; j < separator; ++j) {
			ANS[i][j] = P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j];
		}
	}
	for(unsigned i = 0; i < separator; ++i) {
		for(unsigned j = 0; j < l-separator; ++j) {
			ANS[i][separator + j] = P1[i][j] + P2[i][j];
		}
	}

	for(unsigned i = 0; i < l-separator; ++i) {
		for(unsigned j = 0; j < separator; ++j) {
			ANS[separator + i][j] = P3[i][j] + P4[i][j];
		}
	}
	for(unsigned i = 0; i < l-separator; ++i) {
		for(unsigned j = 0; j < l-separator; ++j) {
			ANS[separator + i][separator + j] = P5[i][j] + P1[i][j] - P3[i][j] - P7[i][j];
		}
	}

	return ANS;
}

int main()
{
	int n;
	cin>>n;
	int checked_n = n;
	vector< vector<int> > v1(n, vector<int>(n)), v2(n, vector<int>(n)) ;
	cout<<"Enter first matrix:\n";
	for(unsigned i = 0; i < n; ++i) {
		for(unsigned j = 0; j < n; ++j) {
			cin>>v1[i][j];
		}
	}
	cout<<"Enter second matrix:\n";
	for(unsigned i = 0; i < n; ++i) {
		for(unsigned j = 0; j < n; ++j) {
			cin>>v2[i][j];
		}
	}
	vector< vector<int> > ans = multiply_matrix(v1,v2);
	cout<<"Ans:\n";
	for(unsigned i = 0; i < n; ++i) {
		for(unsigned j = 0; j < n; ++j) {
			cout<<ans[i][j]<<' ';
		}
		cout<<"\n";
	}
	return 0;
}