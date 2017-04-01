/*Linear system QX = B is solved using the Cholesky decomposition of Q 
Eigen library is used to perform the computation*/
#include<iostream>
#include<fstream>
#include<Eigen/Sparse>
#include<Eigen/Dense>
#include<vector>
#include<string>

typedef Eigen::Triplet<double> Trip;

int main(int argc, char* argv[])
{ 
	int p = atoi(argv[2]), n= atoi(argv[3]), d = atoi(argv[4]), ND = n*d;

	// Read Q matrix from file into an Eigen::SparseMatrix object
	std::ifstream input(argv[1],std::ios::in);
	if(!input)
	{
		std::cout << "ERROR: Q matrix data not defined" << std::endl;
		return 0;
	}
	std::vector<Trip> coefficients;
	int row, col;
	double value;
	std::string line;
	while(std::getline(input,line))
	{
		std::stringstream entry(line);	
		entry >> row >> col >> value;
		coefficients.push_back(Trip(row-1,col-1,value));
	}
	input.close();
	Eigen::SparseMatrix<double> Q(ND,ND);
	Q.setFromTriplets(coefficients.begin(), coefficients.end());

	Eigen::MatrixXd B(ND, p);                   // the right hand side-vector
	if(argc == 6)				// read B from given data
	{
		std::ifstream input(argv[5],std::ios::in);
		if(!input)
		{
			std::cout << "ERROR: B matrix could not be initialized" << std::endl;
			return 0;
		}

		
		while(std::getline(input,line))
		{
			std::stringstream entry(line);	
			entry >> row >> col >> value;
			*(B.data() + (row-1) + (col-1)*ND) = value;
		}
		input.close();
	}
	else					//Randomly initialize B
	{
		B = Eigen::MatrixXd::Random(ND,p);
	}

	// Solving:
	Eigen::SimplicialCholesky<Eigen::SparseMatrix<double> > chol(Q);  // performs a Cholesky factorization of Q
	Eigen::MatrixXd x = chol.solve(B);         // use the factorization to solve for the given right hand side

	// Save the result in a file:
	std::ofstream outfile;
	outfile.open("/home/gaurav/solution.txt"); //Required path should be defined here
	if(!outfile) {
    		std::cout << "Cannot open file to save the solution of the linear system";
	}
	for(row = 0; row < ND; ++row){
		for(col = 0; col < p; ++col){
			outfile << (row+1) << " " << (col+1) << " " << *(x.data() + row + col*ND);	
			outfile << std::endl;
	}
	}
	outfile.close();

	return 0;
}
