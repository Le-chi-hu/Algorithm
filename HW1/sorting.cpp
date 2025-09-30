#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function prototypes
void insertion_sort(vector<int> &arr, int size);
void quick_sort(vector<int> &arr, int left, int right);
void merge_sort(vector<int> &arr, int size);  
void heap_sort(vector<int> &arr, int size);
void generate_random_data(vector<int> &arr, int size);
void print_results(const string &method, int size, double time);
void print_array(const vector<int> &arr);  
void run_sorting_experiment();

int main() {
    run_sorting_experiment();
    return 0;
}

// Insertion Sort
void insertion_sort(vector<int> &arr, int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];// take the element currently to be inserted
        int j = i - 1;// Set j to the previous index of the current element

        // Move elements larger than key to the right to make room for key
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Quick Sort
void quick_sort(vector<int> &arr, int left, int right) {
    if (left <right){
    int i = left;
    int j= right+1;
    int pivot =arr[left]; 
    
    do{
        do i++; while(arr[i] < pivot);
        do j--; while(arr[j] > pivot);
        // If i is still less than j, swap arr[i] and arr[j].
        if(i<j) swap (arr[i],arr[j]);
    }while(i<j);

    swap(arr[left], arr[j]);
    quick_sort(arr, left, j-1);
    quick_sort(arr, j + 1, right);
}
}

// Merge 
void merge(vector<int> &arr, int left, int mid, int right) {
    // Calculate the size of the left and right subarrays
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary left and right subarrays
    vector<int> left_arr(n1), right_arr(n2);

    // Copy data to temporary array
    for (int i = 0; i < n1; i++) left_arr[i] = arr[left + i];
    for (int i = 0; i < n2; i++) right_arr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    // Compare the elements of the left and right subarrays and merge them in order
    while (i < n1 && j < n2) {
        if (left_arr[i] <= right_arr[j]) arr[k++] = left_arr[i++];
        else arr[k++] = right_arr[j++];
    }
    // Process the remaining elements in the left and right subarrays
    while (i < n1) arr[k++] = left_arr[i++];
    while (j < n2) arr[k++] = right_arr[j++];
}

// Merge pass 
void merge_pass(vector<int> &arr, int size, int step) {
    for (int i = 0; i < size; i += 2 * step) {
        int left = i;
        int mid = min(i + step - 1, size - 1);// End index of left subarray
        int right = min(i + 2 * step - 1, size - 1);// End index of the right subarray
        
        // When mid < right, make sure there are at least two parts that can be merged
        if (mid < right) {
            merge(arr, left, mid, right);
        }
    }
}

//Merge Sort
void merge_sort(vector<int> &arr, int size) {
    for (int step = 1; step < size; step *= 2) {
        merge_pass(arr, size, step);
    }
}

// Heap Sort
void heapify(vector<int> &arr, int size, int root) {
    int largest = root;
    int left = 2 * root + 1;//Left child node
    int right = 2 * root + 2;// right child node

    if (left < size && arr[left] > arr[largest]) largest = left;
    if (right < size && arr[right] > arr[largest]) largest = right;
    if (largest != root) {
        swap(arr[root], arr[largest]);
        heapify(arr, size, largest);
    }
}

void heap_sort(vector<int> &arr, int size) {
    for (int i = size / 2 - 1; i >= 0; i--) heapify(arr, size, i);
    for (int i = size - 1; i > 0; i--) {
        swap(arr[0], arr[i]);//Move the maximum value to the end of the array
        heapify(arr, i, 0);//Adjusting subtrees
    }
}

// Generate random data
void generate_random_data(vector<int> &arr, int size) {
    arr.resize(size);
    for (int &num : arr) num = rand() % 50000 + 1;
}

// Print results
void print_results(const string &method, int size, double time) {
    cout << "Method: " << method << endl;
    cout << "Array Size: " << size << endl;
    cout << "Execution Time: " << time << " seconds" << endl;
}

// Print sorted array
void print_array(const vector<int> &arr) {
    cout << "Sorted Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Run sorting experiments
void run_sorting_experiment() {
    srand(time(0));

    //Allowed data size
    vector<int> sizes = {10, 50, 100, 1000, 5000, 10000, 50000};

    // Allow the user to enter the sorting method of their choice
    string method;
    cout << "Enter sorting method (insertion / quick / merge / heap): ";
    cin >> method;

    // Let the user enter the size of n and check whether it is legal
    int size;
    bool valid_input = false;
    
    while (!valid_input) {
        cout << "Enter the number of elements (";
        for (size_t i = 0; i < sizes.size(); i++) {
            cout << sizes[i];
            if (i < sizes.size() - 1) cout << ", ";
        }
        cout << "): ";
        cin >> size;

        // Check if the input n is in the sizes array
        if (find(sizes.begin(), sizes.end(), size) != sizes.end()) {
            valid_input = true;
        } else {
            cout << "Invalid size! Please enter a valid number.\n";
        }
    }

    vector<int> data;
    generate_random_data(data, size);

    vector<int> copy = data;
    // count time
    auto start = high_resolution_clock::now();

    if (method == "insertion") {
        insertion_sort(copy, size);
    } 
    else if (method == "quick") {
        quick_sort(copy, 0, size - 1);
    } 
    else if (method == "merge") {
        merge_sort(copy, size);
    } 
    else if (method == "heap") {
        heap_sort(copy, size);
    } 
    else {
        cout << "Invalid sorting method!" << endl;
        return;
    }

    auto end = high_resolution_clock::now();
    //get the time
    double elapsed_time=duration<double>(end - start).count(); 
   
    print_results(method, size, elapsed_time);
    
    print_array(copy);
}