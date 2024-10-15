#include <iostream>
using namespace std;

// Class for holding a value with a row and column index.
class SparseRow {
    protected:
        int row; // Row index
        int col; // Column index
        int value; // Assuming matrix value will be int.
    public:
        // Default constructor
        SparseRow() {}
        // Constructor for defining all instance variables.
        SparseRow(int n, int m, int nsv) {
            row = n;
            col = m;
            value = nsv;
        }
        // Display method (print row index, col index, and value).
        void display() const {
            cout << row << ", " << col << ", " << value << endl;
        }
        // Setters
        void setRow(int newRow) { row = newRow; }
        void setCol(int newCol) { col = newCol; }
        void setValue(int newValue) { value = newValue; }
        // Getters
        int getRow() const { return row; }
        int getCol() const { return col; }
        int getValue() const { return value; }
};

// Class for holding a 2D Matrix. Uses SparseRow objects to hold the row index and column index of any non-sparse values.
class SparseMatrix {
    protected:
        int noRows; // Number of rows of the matrix.
        int noCols; // Number of columns of the matrix.
        int commonValue; // Common value in matrix.
        int noNonSparseValues; // Number of non-common values.
        int noInitializedNSV; // Counter for initialized non-sparse values.
        SparseRow* myMatrix; // Array of SparseRow objects.
    public:
        // Default constructor
        SparseMatrix() {}
        // Constructor for defining noRows, noCols, commonValue, and noNonSparseValues.
        SparseMatrix(int n, int m, int cv, int noNSV) {
            noRows = n;
            noCols = m;
            commonValue = cv;
            noNonSparseValues = noNSV;
            noInitializedNSV = 0;
            myMatrix = new SparseRow[noNSV]; // Defines the initialized SparseRow pointer to a SparseRow array with the amount of elements specified.
        }
        // Initialize SparseRow objects as they are fed to the SparseMatrix.
        void initializeSparseRow(int row, int col, int nsv) {
            if (noInitializedNSV < noNonSparseValues) { // Checks to see if the amount of non-sparse values has been met.
                myMatrix[noInitializedNSV].setRow(row);
                myMatrix[noInitializedNSV].setCol(col);
                myMatrix[noInitializedNSV].setValue(nsv);
                noInitializedNSV++; // Increments the number of initialized non-sparse values.
            }
        }
        // Expands the size of MyMatrix (in the scenario where you may not know how many non-sparse values you will have before matrix creation).
        void setAmountInMyMatrixArray(int newSize) {
            SparseRow* result = new SparseRow[newSize]; // Create a result array with new size to return.
            for (int i = 0; i < noInitializedNSV; i++) { // Copy over existing non-sparse values (up to the current size).
                result[i] = myMatrix[i];
            }
            myMatrix = result; // Point to the new matrix and update the number of non-sparse values.
            noNonSparseValues = newSize; // Update the noNonSparseValues to reflect the new size.
        }
        // Matrix transpose (switches row and col values of non-sparse values).
        SparseMatrix* Transpose() {
            SparseMatrix* result = new SparseMatrix(noRows, noCols, commonValue, noNonSparseValues);// Create a result SparseMatrix to return.
            for (int i = 0; i < noNonSparseValues; i++) { // Copy over all of the values from the old matrix to the new SparseMatrix.
                (*result).myMatrix[i].setRow(myMatrix[i].getCol());
                (*result).myMatrix[i].setCol(myMatrix[i].getRow());
                (*result).myMatrix[i].setValue(myMatrix[i].getValue());
            }
            return result; // Return resulting SparseMatrix.
        }
        // Matrix multiplication (multiplies two matrices).
        SparseMatrix* Multiply(SparseMatrix& M) {
            if (noCols != M.noRows) { // Check if multiplication is possible.
                return nullptr;
            }
            SparseMatrix* result = new SparseMatrix(noRows, M.noCols, commonValue, 0); // Create result matrix with an initial assumption of zero non-sparse values.
            for (int i = 0; i < noRows; i++) { // For each row of the first matrix (this).
                for (int j = 0; j < M.noCols; j++) { // For each column of the second matrix (M).
                    int sum = 0;
                    for (int k = 0; k < noCols; k++) { // Calculate the dot product of row i of this matrix and column j of matrix M.
                        int valueA = commonValue;  // Assume common value for this matrix.
                        int valueB = M.commonValue;  // Assume common value for matrix M.
                        for (int idxA = 0; idxA < noNonSparseValues; idxA++) { // Search for a non-sparse value in the current row (i) and column (k) of this matrix.
                            if (myMatrix[idxA].getRow() == i && myMatrix[idxA].getCol() == k) {
                                valueA = myMatrix[idxA].getValue();
                                break;
                            }
                        }
                        for (int idxB = 0; idxB < M.noNonSparseValues; idxB++) { // Search for a non-sparse value in the current row (k) and column (j) of matrix M.
                            if (M.myMatrix[idxB].getRow() == k && M.myMatrix[idxB].getCol() == j) {
                                valueB = M.myMatrix[idxB].getValue();
                                break;
                            }
                        }
                        sum += valueA * valueB; // Add to the dot product.
                    }
                    if (sum != commonValue) { // If the sum is not equal to the common value, it's a non-sparse value.
                        // Dynamically add a new sparse row in the result matrix.
                        result->setAmountInMyMatrixArray(result->noInitializedNSV + 1);  // Resize result's matrix array.
                        result->initializeSparseRow(i, j, sum);  // Add the non-sparse value.
                    }
                }
            }
            return result; // Return resulting SparseMatrix.
        }
        // Matrix addition (adds two matrices).
        SparseMatrix* Add(SparseMatrix& M) {
            SparseMatrix* result; // Define result SparseMatrix.
            if (noRows != M.noRows || noCols != M.noCols) { // Determine whether the matrices can be added.
                return nullptr;
            }
            int index1 = 0; // Create an index tracker for this matrix.
            int index2 = 0; // Create an index tracker for M matrix.
            int indexTotal = 0; // Store how many total non-sparse values there will be.
            for (int i = 0; i < noRows; i++) { // Increment through the matrices' rows.
                for (int j = 0; j < noCols; j++) { // Increment through the matrices' columns.
                    if ((myMatrix[index1].getRow() == i && myMatrix[index1].getCol() == j)
                    && (M.myMatrix[index2].getRow() == i && M.myMatrix[index2].getCol() == j)) { // Determine whether both of the matrices have a non-sparse value in the same location.
                        indexTotal--;
                    }
                    if (myMatrix[index1].getRow() == i && myMatrix[index1].getCol() == j) { // Determine whether this matrix has a non-sparse value in this location.
                        index1++;
                    }
                    if (M.myMatrix[index2].getRow() == i && M.myMatrix[index2].getCol() == j) { // Determine whether M matrix has a non-sparse value in this location.
                        index2++;
                    }
                }
            }
            indexTotal += index1 + index2; // Add up all of the unique non-sparse value locations.
            result = new SparseMatrix(noRows, noCols, commonValue, indexTotal); // Initialize the result SparseMatrix.
            int index3 = 0; // Create an index tracker for this matrix.
            int index4 = 0; // Create an index tracker for M matrix.
            for (int i = 0; i < noRows; i++) { // Increment through the matrices' rows.
                for (int j = 0; j < noCols; j++) { // Increment through the matrices' columns.
                    int currentElementValue = 0;
                    if (myMatrix[index3].getRow() == i && myMatrix[index3].getCol() == j) { // Determine whether this matrix has a non-sparse value in this location.
                        currentElementValue = myMatrix[index3].getValue();
                        index3++;
                    }
                    if (M.myMatrix[index4].getRow() == i && M.myMatrix[index4].getCol() == j) { // Determine whether M matrix has a non-sparse value in this location.
                        currentElementValue += M.myMatrix[index4].getValue();
                        index4++;
                    }
                    if (currentElementValue > 0) { // If the current location has a value that is not the common value then add it to the result SparseMatrix.
                        result->initializeSparseRow(i, j, currentElementValue);
                    }
                }
            }
            return result; // Return resulting SparseMatrix.
        }
        // Displays matrix in original format.
        void displayMatrix() const {
            int index = 0; // int for incrementing through the non-sparse values.
            for (int i = 0; i < noRows; i++) { // Outer loop for rows.
                for (int j = 0; j < noCols; j++) { // Inner loop for columns.
                    if (myMatrix[index].getRow() == i && myMatrix[index].getCol() == j) {
                        cout << myMatrix[index].getValue();
                        index++;
                    } else {
                        cout << commonValue;
                    }
                    if (j < noCols - 1) {
                        cout << " ";
                    }
                }
            cout << endl;
            }
        }
        // Overloaded << operator.
        friend ostream& operator<<(ostream& s, const SparseMatrix& sm) {
            for (int i = 0; i < sm.noNonSparseValues; i++) {
                s << sm.myMatrix[i].getRow() << ", " 
                << sm.myMatrix[i].getCol() << ", " 
                << sm.myMatrix[i].getValue() << endl;
            }
        return s;
        }
};

int main () {
    int noRows, noCols, cv, noNSV; // Defining row, col, common value, and number of non-sparse values.
    SparseMatrix* temp; // Defining SparseMatrix pointer temp.
    cin >> noRows >> noCols >> cv >> noNSV; // Initializing number of rows, number of columns, common value, and number of non-sparse values through console.
    SparseMatrix* firstOne = new SparseMatrix(noRows, noCols, cv, noNSV); // Creating the first SparseMatrix with the given values.
    
    int input;
    for (int i = 0; i < noRows; i++) { // Loop through rows.
        for (int j = 0; j < noCols; j++) { // Loop through columns.
            cin >> input; // Get the value.
            if (input != cv) // If the value is not the common (sparse) value.
                firstOne->initializeSparseRow(i, j, input); // Initialize a sparse row with the row, col, and value.
        }
    }

    cin >> noRows >> noCols >> cv >> noNSV; // Initializing number of rows, number of columns, common value, and number of non-sparse values through console.
    SparseMatrix* secondOne = new SparseMatrix(noRows, noCols, cv, noNSV); // Creating the first SparseMatrix with the given values.

    for (int i = 0; i < noRows; i++) { // Loop through rows.
        for (int j = 0; j < noCols; j++) { // Loop through columns.
            cin >> input; // Get the value.
            if (input != cv) // If the value is not the common (sparse) value.
                secondOne->initializeSparseRow(i, j, input); // Initialize a sparse row with the row, col, and value.
        }
    }

    cout << "First one in sparse matrix format" << endl;
    cout << (*firstOne); // Print SparseMatrix firstOne to console in sparse matrix format.
    cout << "After transpose" << endl;
    cout << (*(*firstOne).Transpose()); // Print SparseMatrix firstOne to console in transposed sparse matrix format.
    cout << "First one in matrix format" << endl;
    (*firstOne).displayMatrix(); // Print SparseMatrix firstOne to console in matrix format.
    cout << "Second one in sparse matrix format" << endl;
    cout << (*secondOne); // Print SparseMatrix secondOne to console in sparse matrix format.
    cout << "After transpose" << endl;
    cout << (*(*secondOne).Transpose()); // Print SparseMatrix secondOne to console in transposed sparse matrix format.
    cout << "Second one in matrix format" << endl;
    (*secondOne).displayMatrix(); // Print SparseMatrix secondOne to console in matrix format.
    cout << "Matrix addition result" << endl;
    temp = (*firstOne).Add(*secondOne); // Add matrices firstOne and secondOne together.
    if (!temp) { // Determine whether matrix addition is possible by checking if temp has received a nullptr.
        cout << "Matrix addition is not possible" << endl;
    }
    else {
        (*temp).displayMatrix(); // Print out the resulting firstOne + secondOne result.
    }
    cout << "Matrix multiplication result" << endl;
    temp = (*firstOne).Multiply(*secondOne); // Multiply matrices firstOne and secondOne together.
    if (!temp) { // Determine whether matrix multiplication is possible by checking if temp has received a nullptr.
        cout << "Matrix multiplication is not possible" << endl;
    }
    else {
        (*temp).displayMatrix(); // Print out the resulting firstOne * secondOne result.
    }

    delete temp, firstOne, secondOne; // Free up memory.
    return 0;
}