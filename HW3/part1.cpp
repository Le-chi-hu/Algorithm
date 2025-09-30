#include <iostream>
#include <limits>
using namespace std;

class sparse_matrix;

struct element {
    int row, col, value; // Storing elements in a sparse matrix
};

void print_matrix(const sparse_matrix& matrix);

class sparse_matrix {
public:
    int rows, cols, terms; // Number of rows, columns, and non-zero elements
    element* sm_array;  // Dynamically allocated array of elements
    sparse_matrix(int r, int c, int t);
    ~sparse_matrix();
    sparse_matrix fast_transpose();
};

int main() {
    int rows, cols, terms;

    cout << "Please enter the number of rows, columns, and non-zero elements of the sparse matrix: ";

    while (!(cin >> rows >> cols >> terms) || rows <= 0 || cols <= 0 || terms < 0) {//enter how many rows and columns
        cout << "The input is invalid. Please enter the number of rows and columns with positive integers and the number of non-zero elements with non-negative integers: ";
        cin.clear(); // clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore incorrect input
    }

    cout << "Please enter " << terms << " non-zero elements (row,column,value):\n";

    sparse_matrix matrix(rows, cols, terms);  // Create a sparse matrix

    for (int i = 0; i < terms; ++i) { 
        int r, c, v;
        cout << "number " << (i + 1) << " Non-zero elements: ";
        
        while (!(cin >> r >> c >> v) || r < 0 || r >= rows || c < 0 || c >= cols) {
            cout << "Invalid input! Rows and columns must be within the range, please re-enter: ";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        matrix.sm_array[i] = {r, c, v}; // Store the non-zero elements of the input
    }

    cout << "Your input sparse matrix is:\n";
    print_matrix(matrix);

    sparse_matrix transpose_matrix = matrix.fast_transpose(); // Perform a transpose operation

    cout << "The transposed sparse matrix is:\n";
    print_matrix(transpose_matrix);

    return 0;
}

sparse_matrix::sparse_matrix(int r, int c, int t) : rows(r), cols(c), terms(t) {
    sm_array = new element[t]; // Allocate space for non-zero elements
}

sparse_matrix::~sparse_matrix() {
    delete[] sm_array; // 釋放記憶體
}

sparse_matrix sparse_matrix::fast_transpose() {
    sparse_matrix b(cols, rows, terms); // Create the transposed matrix b

    if (terms > 0) {
        int* row_info = new int[cols]();  // +1 To store the starting position

       //Initialize the array
        for (int i = 0; i < terms; i++) {
            row_info[sm_array[i].col]++;
        }

        // Calculate the starting position of each column in the transposed matrix
        int cumulative = 0;
        for (int i = 0; i < cols; i++) {
            int temp = row_info[i];
            row_info[i] = cumulative;
            cumulative += temp;
        }

        // Fill the transposed matrix
        for (int i = 0; i < terms; i++) {
            int col = sm_array[i].col;  // Find the column of the current element
            int pos = row_info[col];    // Find the insertion position of the column
            b.sm_array[pos].row = sm_array[i].col;
            b.sm_array[pos].col = sm_array[i].row;
            b.sm_array[pos].value = sm_array[i].value;
            row_info[col]++;            // Update Insert Position
        }

        delete[] row_info; // free memory
    }

    return b;
}

// print matrix
void print_matrix(const sparse_matrix& matrix) {
    for (int i = 0; i < matrix.terms; ++i) {
        cout << "Row: " << matrix.sm_array[i].row 
             << ", Col: " << matrix.sm_array[i].col 
             << ", Value: " << matrix.sm_array[i].value << endl;
    }
}
