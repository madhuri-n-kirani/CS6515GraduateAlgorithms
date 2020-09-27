// C++ implementation for k-sorting the list of inputs

#include<iostream> 
#include<algorithm> 
#include<climits> 

using namespace std;

int partition(int arr[], int l, int r, int k);

// A simple function to find median of arr[]. This is called 
// only for an array of size 5 in this program. 
int findMedian(int arr[], int n)
{
	sort(arr, arr + n); // Sort the array 
	return arr[n / 2]; // Return middle element 
}

// Returns k'th smallest element in arr[l..r] in worst case 
// linear time. ASSUMPTION: ALL ELEMENTS IN ARR[] ARE DISTINCT 
int kthSmallest(int arr[], int l, int r, int k)
{
	// If k is smaller than number of elements in array 
	if (k > 0 && k <= r - l + 1)
	{
		int n = r - l + 1; // Number of elements in arr[l..r] 

		// Divide arr[] in groups of size 5, calculate median 
		// of every group and store it in median[] array. 
		int i, median[1000]; // There will be floor((n+4)/5) groups; 
		for (i = 0; i < n / 5; i++)
			median[i] = findMedian(arr + l + i * 5, 5);
		if (i * 5 < n) //For last group with less than 5 elements 
		{
			median[i] = findMedian(arr + l + i * 5, n % 5);
			i++;
		}

		// Find median of all medians using recursive call. 
		// If median[] has only one element, then no need 
		// of recursive call 
		int medOfMed = (i == 1) ? median[i - 1] :
			kthSmallest(median, 0, i - 1, i / 2);

		// Partition the array around a random element and 
		// get position of pivot element in sorted array 
		int pos = partition(arr, l, r, medOfMed);

		// If position is same as k 
		if (pos - l == k - 1)
			return arr[pos];
		if (pos - l > k - 1) // If position is more, recur for left 
			return kthSmallest(arr, l, pos - 1, k);

		// Else recur for right subarray 
		return kthSmallest(arr, pos + 1, r, k - pos + l - 1);
	}

	// If k is more than number of elements in array 
	return INT_MAX;
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

// It searches for x in arr[l..r], and partitions the array 
// around x. 
int partition(int arr[], int l, int r, int x)
{
	// Search for x in arr[l..r] and move it to end 
	int i;
	for (i = l; i < r; i++)
		if (arr[i] == x)
			break;
	swap(&arr[i], &arr[r]);

	// Standard partition algorithm 
	i = l;
	for (int j = l; j <= r - 1; j++)
	{
		if (arr[j] <= x)
		{
			swap(&arr[i], &arr[j]);
			i++;
		}
	}
	swap(&arr[i], &arr[r]);
	return i;
}
int partition_alt(int arr[], int low, int high , int pivot)
{
	//int pivot = arr[high];    // pivot 
	int i = (low - 1);  // Index of smaller element 

	for (int j = low; j <= (high); j++)
	{
		// If current element is smaller than or 
		// equal to pivot 
		if (arr[j] <= pivot)
		{
			i++;    // increment index of smaller element 
			swap(&arr[i], &arr[j]);
		}
	}
	//swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

int* ResizeArray(int **orig, int size) {
	int *resized = new int[size * 2];
	for (int i = 0; i < size; i++)
		resized[i] = (*orig)[i];
	return resized;
}

void k_groups(int arr[] , int low , int high)
{
	if ((high - low + 1 ) > 1)
	{
		int* med = ResizeArray(&arr, 16);
		int median = kthSmallest(med, low, high, (high - low + 1) / 2);
		delete[] med;
		partition_alt(arr, low, high, median);
		int part = low + (high - low + 1) / 2;
		k_groups(arr, low, part - 1 );
		k_groups(arr, part, high);
	}
}

// Driver program to test above methods 
int main()
{
	int arr[] = { 12, 3, 5, 7, 4, 19, 26 , 1 , 36,45,23,41,42,67,78,89 };
	int n = sizeof(arr) / sizeof(arr[0]), k = 4;
	cout << "K'th smallest element is ";
	k_groups(arr, 0, n - 1);
	return 0;
}
