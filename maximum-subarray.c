#include <stdio.h>
#include <stdlib.h>

int* findMaxCrossingSubarray(int* arr, int low, int mid, int high) {
    int* result = (int*)malloc(3 * sizeof(int));
    int left_sum = -1000000, sum = 0, max_left = mid;
    
    for (int i = mid; i >= low; i--) {
        sum += arr[i];
     
	if (sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    
    }
    
    int right_sum = -1000000;
    sum = 0;
    int max_right = mid + 1;
    
    for (int i = mid + 1; i <= high; i++) {
        sum += arr[i];
    
	    if (sum > right_sum) {
            right_sum = sum;
            max_right = i;
        }
    
    }
    
    result[0] = max_left;
    result[1] = max_right;
    result[2] = left_sum + right_sum;
    
    return result;
}

int* findMaxSubarray(int* arr, int low, int high) {
    int* result = (int*)malloc(3 * sizeof(int));
    
    if (low == high) {
        result[0] = low;
        result[1] = high;
        result[2] = arr[low];
        return result;
    }
    
    int mid = (low + high) / 2;
    
    int* left = findMaxSubarray(arr, low, mid);
    int* right = findMaxSubarray(arr, mid + 1, high);
    int* cross = findMaxCrossingSubarray(arr, low, mid, high);
    
    if (left[2] >= right[2] && left[2] >= cross[2]) {
        free(right);
        free(cross);
        return left;
    } else if (right[2] >= left[2] && right[2] >= cross[2]) {
        free(left);
        free(cross);
        return right;
    } else {
        free(left);
        free(right);
        return cross;
    }
}

const int main(void) {
    int arr1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int* result1 = findMaxSubarray(arr1, 0, n1 - 1);
    
    printf("Test 1: Max sum = %d, from index %d to %d\n", result1[2], result1[0], result1[1]);
    free(result1);
    
    int arr2[] = {1};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int* result2 = findMaxSubarray(arr2, 0, n2 - 1);
    
    printf("Test 2: Max sum = %d, from index %d to %d\n", result2[2], result2[0], result2[1]);
    free(result2);
    
    int arr3[] = {-1, -2, -3, -4};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int* result3 = findMaxSubarray(arr3, 0, n3 - 1);
    
    printf("Test 3: Max sum = %d, from index %d to %d\n", result3[2], result3[0], result3[1]);
    free(result3);
    
    return 0;
}
