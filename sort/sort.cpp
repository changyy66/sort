// maopao.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <iostream>
using namespace std;

void Bubble(vector<int>& v)
{
	int k = v.size() - 1;
	for (int i=0;i<v.size()-1;i++)
	{
		bool flag = false;
		int pos = k;
		for (int j=0;j<k;j++)
		{
			if (v[j]>v[j+1])
			{
				int t = v[j];
				v[j] = v[j+1];
				v[j+1] = t;
				flag = true;
				pos = j;
			}
		}
		k = pos;
		if (!flag)
		{
			return;
		}
	}
}

void selectSort(vector<int>& nums)
{
	for (int i=0;i<nums.size();i++)
	{
		for (int j=i+1;j<nums.size();j++)
		{
			if (nums[i]>nums[j])
			{
				int t = nums[i];
				nums[i] = nums[j];
				nums[j] = t;
			}
		}
	}
}

void insertSort(vector<int>& nums)
{
	for (int i=1;i<nums.size();i++)
	{
		for (int j = i-1; j >=0; j--)
		{
			if (nums[j]>nums[j+1])
			{
				int t = nums[j];
				nums[j] = nums[j + 1];
				nums[j + 1] = t;
			}
		}
	}
}

void shellSort(vector<int>& nums)
{
	int k = nums.size() / 2;
	while (k>0)
	{
		for (int i=k;i<nums.size();i++)
		{
			for (int j=i-k;j>=0;j-=k)
			{
				if (nums[j]>nums[j+k])
				{
					int t = nums[j];
					nums[j] = nums[j + k];
					nums[j + k] = t;
				}
			}
		}
		k /= 2;
	}
}

void quickSortHelper(vector<int> &nums,int start,int end)
{
	if (start >= end)return;
	int flag = nums[start];
	bool l2r = false;
	int i = start;
	int j = end;
	while (i<j)
	{
		while(i<j && nums[j]>flag)
		{
			j--;
		}
		nums[i] = nums[j];
		nums[j] = flag;
		while (i<j&&nums[i]<flag)
		{
			i++;
		}
		nums[j] = nums[i];
		nums[i] = flag;
	}
	quickSortHelper(nums,start, i-1);
	quickSortHelper(nums, i + 1, end);
}

void quickSort(vector<int> &nums)
{
	quickSortHelper(nums, 0, nums.size()-1);
}

void merge(vector<int> &nums,int start1,int end1,int start2,int end2 )
{
	vector<int> res(end2 - start1 + 1, 0);
	int i = start1;
	int j = start2;
	int k = 0;
	while (i<=end1&&j<=end2)
	{
		if (nums[i]>nums[j])
		{
			res[k++] = nums[j++];
		}
		else
		{
			res[k++] = nums[i++];
		}
	}
	while (i<=end1)
	{
		res[k++] = nums[i++];
	}
	while (j<=end2)
	{
		res[k++] = nums[j++];
	}
	i = start1;
	k = 0;
	while (i<=end2)
	{
		nums[i++] = res[k++];
	}
}

void mergeSortHelper(vector<int> &nums, int start, int end)
{
	if (start >= end)return;
	int mid = (start + end) / 2;
	mergeSortHelper(nums, start, mid);
	mergeSortHelper(nums, mid + 1, end);
	merge(nums, start, mid, mid + 1, end);
}

void mergeSort(vector<int> &nums)
{
	mergeSortHelper(nums, 0, nums.size() - 1);
}

void fixupMaxheap(vector<int> &nums, int root,int size)
{
	int parent = root;
	int child = root * 2 + 1;
	while (child<size)
	{
		if (child + 1 < size)
		{
			if (nums[child] < nums[child + 1])
			{
				child++;
			}
		}
		if (nums[parent]<nums[child])
		{
			int t = nums[parent];
			nums[parent] = nums[child];
			nums[child] = t;
		}
		parent = child;
		child = child * 2 + 1;
	}
}

void makeMaxHeap(vector<int> &nums)
{
	for (int i = nums.size()/2;i>=0;i--)
	{
		fixupMaxheap(nums, i,nums.size());
	}
}

void heap(vector<int> &nums)
{
	makeMaxHeap(nums);
	for (int i=nums.size()-1;i>=0;i--)
	{
		int t = nums[0];
		nums[0] = nums[i];
		nums[i] = t;
		fixupMaxheap(nums, 0,i);
	}
}

int findMax(vector<int> &nums)
{
	int d = 1;
	int p = 10;
	for (int i=0;i<nums.size();i++)
	{
		if (nums[i]>=p)
		{
			d++;
			p *= 10;
		}
	}
	return d;
}

void radixSort(vector<int> &nums)
{
	int maxN = findMax(nums);
	vector<int> count(10, 0);
	vector<int> tmp(nums.size(), 0);
	int radix = 1;
	for (int i=0;i<maxN;i++)
	{
		for (int j = 0; j < 10; j++)
		{
			count[j] = 0;
		}
		for (int j=0;j<nums.size();j++)
		{
			count[nums[j] / radix % 10]++;
		}
		for (int j=1;j<10;j++)
		{
			count[j] += count[j - 1];
		}
		for (int j=nums.size()-1;j>=0;j--)
		{
			int k = nums[j] / radix % 10;
			tmp[count[k] - 1] = nums[j];
			count[k]--;
		}
		for (int j=0;j<nums.size();j++)
		{
			nums[j] = tmp[j];
		}

		radix *= 10;
	}
}

int main()
{
	vector<int> nums = { 0,3,5,6,4,8,56,45,35,55,653,44,54,64 };
	//vector<int> nums1 = { 0,1,2,3,4,5,6,7,8,9};
	vector<int> nums1 = { 0,2,4,6,8,9,7,5,3,1,11};
	//Bubble(nums1);
	//selectSort(nums1);
	//shellSort(nums1);
	//quickSort(nums1);
	//mergeSort(nums1);
	radixSort(nums1);
	for each (auto var in nums1)
	{
		cout << var << " ";
	}
    return 0;
}

