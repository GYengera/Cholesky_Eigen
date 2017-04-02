# Cholesky_Eigen
Solution of linear system QX = B using the Cholesky decomposition of matrix Q. Eigen library is used for the computations.

Compile the file. On ubuntu the command is:

$ g++ Cholesky.cpp -o Cholesky

To run the file with required parameters, the command is:

$ ./Cholesky < Q data path > < p > < n > < d > < B data path >

The path to initialization data for right hand side matrix B is optional. If data is not provided, then random initialization is performed.

Datasets for Q matrix are provided at: http://mapir.isa.uma.es/jbriales/GSOC_project8_data.zip
