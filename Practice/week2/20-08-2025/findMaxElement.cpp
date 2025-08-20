#include "findMaxElement.h"

int findMax(int arr[], int size)
{
    int maxElement = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > maxElement)
            maxElement = arr[i];
    }
    return maxElement;
}