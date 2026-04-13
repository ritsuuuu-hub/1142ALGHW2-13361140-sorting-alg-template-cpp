#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ==============================
// 工具函式
// ==============================
void printArray(const vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << "\n";
}

void printTitle(const string& title) {
    cout << "\n==============================\n";
    cout << title << "\n";
    cout << "==============================\n";
}

// ==============================
// 1. Selection Sort
// ==============================
void selectionSort(vector<int>& arr) {
    int n = arr.size();

    // TODO:
    // 使用挑選排序法將 arr 由小到大排序

    for(int i=0;i<n-1;i++){// 1. 外圈從 i = 0 到 n-2
        int minIndex=i;
        for(int o=i+1;o<n;o++){
            if(arr[o]<arr[minIndex]) minIndex=o;// 2. 在未排序區間中找最小值的位置 minIndex
        }
        swap(arr[i],arr[minIndex]);// 3. 將 arr[i] 與 arr[minIndex] 交換
    }
    

}

// ==============================
// 2. Insertion Sort
// ==============================
void insertionSort(vector<int>& arr) {
    int n = arr.size();

    // TODO:
    // 使用插入排序法將 arr 由小到大排序

    for(int i=1;i<n;i++){// 1. 外圈從 i = 1 到 n-1
        int key=arr[i];// 2. 設 key = arr[i]
        int o=i-1;
        while(o>=0 && arr[o]>key){
            arr[o+1]=arr[o];// 3. 將比 key 大的元素往右移
            o--;
        }
        arr[o+1]=key;// 4. 把 key 插入正確位置
    }
    
    
    
    
}

// ==============================
// 3. Bubble Sort
// ==============================
void bubbleSort(vector<int>& arr) {
    int n = arr.size();

    // TODO:
    // 使用氣泡排序法將 arr 由小到大排序
    
    for(int i=0;i<n-1;i++){
        bool swapped=false;
        for(int o=0;o<n-1;o++){
            if(arr[o]>arr[o+1]){
                swap(arr[o],arr[o+1]);// 1. 每一輪把最大值往右推
                swapped=true;
            }
        }
        if(swapped==false)break;// 2. 可使用 swapped 變數判斷是否提早結束
    }
    
    
}

// ==============================
// 4. Shell Sort
// ==============================
void shellSort(vector<int>& arr) {
    int n = arr.size();

    // TODO:
    // 使用 Shell 排序法將 arr 由小到大排序
    
    for(int gap=n/2;gap>0;gap/=2){
        // 1. gap 先設為 n/2
        // 2. 每次 gap /= 2
        for(int i=gap;i<n;i++){
            int temp=arr[i];
            int o;
            for(o=i;o>=gap && arr[o-gap]>temp;o-=gap){// 3. 對每個 gap 做類似 insertion sort
                arr[o]=arr[o-gap];
            }
            arr[o]=temp;
        }
        

    }
    
}

// ==============================
// 5. Merge Sort
// ==============================
void merge(vector<int>& arr, int left, int mid, int right) {
    // TODO:
    // 合併 arr[left..mid] 與 arr[mid+1..right]
    
    int n1=mid-left+1;
    int n2=right-mid;
    vector<int>leftArr(n1),rightArr(n2);// 1. 先建立 leftArr 與 rightArr
    for(int i=0;i<n1;i++)leftArr[i]=arr[left+i];
    for(int i=0;i<n2;i++)rightArr[i]=arr[mid+1+i];

    int i=0,o=0,k=left;
    while(i<n1 && o<n2){
        if(leftArr[i]<=rightArr[o]){
            arr[k]=leftArr[i];
            i++;
        }else{
            arr[k]=rightArr[o];
            o++;
        }k++;
    }// 2. 比較兩邊元素，小的先放回 arr

    while(i<n1){
        arr[k]=leftArr[i];
        i++;
        k++;
    }
    while(o<n2){
        arr[k]=rightArr[o];
        o++;
        k++;
    }// 3. 最後把剩餘元素補回 arr
    
}

void mergeSort(vector<int>& arr, int left, int right) {
    // TODO:
    // 使用遞迴完成 merge sort
        
    if(left>=right)return;// 1. 終止條件：left >= right
    int mid=left+(right-left)/2;// 2. 找中間 mid
    
    mergeSort(arr,left,mid);// 3. 遞迴排序左半部
    mergeSort(arr,mid+1,right);// 4. 遞迴排序右半部
    merge(arr,left,mid,right);// 5. 呼叫 merge()
}

// ==============================
// 6. Quick Sort
// ==============================
int partitionArray(vector<int>& arr, int low, int high) {
    // TODO:
    // 以 arr[high] 作為 pivot，完成 partition
    
    int pivot=arr[high];// 1. pivot = arr[high]
    int i=low-1;// 2. i = low - 1
    
    for(int j=low;j<high;j++){// 3. 掃描 j = low 到 high - 1
        if(arr[j]<pivot){// 4. 若 arr[j] < pivot，則交換到左側
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[high]);// 5. 最後將 pivot 放到正確位置
    
    return i+1;// 6. 回傳 pivot 的索引
}

void quickSort(vector<int>& arr, int low, int high) {
    // TODO:
    // 使用遞迴完成 quick sort
    
    if(low<high){// 1. 若 low < high
        int pi=partitionArray(arr,low,high);// 2. 呼叫 partitionArray()
        quickSort(arr,low,pi-1);// 3. 遞迴排序左半部與
        quickSort(arr,pi+1,high);//右半部
    }
}

// ==============================
// 7. Radix Sort
// 僅處理非負整數
// ==============================
void countingSortByDigit(vector<int>& arr, int exp) {
    // TODO:
    // 依照指定位數 exp 進行 counting sort
    
    int n=arr.size();
    vector<int>output(n);
    int count[10]={0};
    for(int i=0;i<n;i++){
        count[(arr[i]/exp)%10]++;// 1. digit = (arr[i] / exp) % 10(我省掉digit這個變數，而直接用內容)
    }// 2. count[10] 紀錄各數字出現次數
    for(int i=1;i<10;i++){
        count[i]+=count[i-1];
    }// 3. 轉成累計次數
    for(int i=n-1;i>=0;i--){
        output[count[(arr[i]/exp)%10]-1]=arr[i];
        count[(arr[i]/exp)%10]--;
    }// 4. 由右往左放入 output，保持穩定性
    for(int i=0;i<n;i++){
        arr[i]=output[i];
    }// 5. 將 output 複製回 arr
    
}

void radixSort(vector<int>& arr) {
    // TODO:
    // 使用 radix sort 將 arr 由小到大排序
    
    if(arr.empty())return;
    int maxVal=*max_element(arr.begin(),arr.end());// 1. 找出最大值 maxVal
    for(int exp=1;maxVal/exp>0;exp*=10){// 2. 從個位數開始 exp = 1    // 3. 每次乘以 10，直到 maxVal / exp == 0
        countingSortByDigit(arr,exp);// 4. 每次呼叫 countingSortByDigit(arr, exp)
    }
    
}

// ==============================
// 8. Heap Sort
// ==============================
void heapify(vector<int>& arr, int n, int i) {
    // TODO:
    // 維護以 i 為根的 max-heap
    
    int largest=i;// 1. largest = i
    int left=2*i+1,right=2*i+2;// 2. left = 2*i + 1, right = 2*i + 2
    if(left<n && arr[left]>arr[largest])largest=left;// 3. 找出三者中最大者
    if(right<n && arr[right]>arr[largest])largest=right;
    if(largest!=i){
        swap(arr[i],arr[largest]);
        heapify(arr,n,largest);// 4. 若最大者不是 i，交換後遞迴 heapify
    }
    
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    // TODO:
    // 使用 heap sort 將 arr 由小到大排序
    
    for(int i=n/2-1;i>=0;i--)heapify(arr,n,i);// 1. 先建立 max heap
    for(int i=n-1;i>0;i--){
        swap(arr[0],arr[i]);// 2. 再把堆頂元素和最後元素交換
        heapify(arr,i,0);// 3. 縮小 heap 範圍後重新 heapify
    }
}

// ==============================
// 執行單一排序並輸出
// ==============================
void runSingleTest(const string& sortName, void (*sortFunc)(vector<int>&), const vector<int>& data) {
    vector<int> arr = data;
    cout << sortName << "\n";
    cout << "Before: ";
    printArray(arr);
    sortFunc(arr);
    cout << "After : ";
    printArray(arr);
    cout << "\n";
}

void runMergeSortTest(const vector<int>& data) {
    vector<int> arr = data;
    cout << "Merge Sort\n";
    cout << "Before: ";
    printArray(arr);
    mergeSort(arr, 0, arr.size() - 1);
    cout << "After : ";
    printArray(arr);
    cout << "\n";
}

void runQuickSortTest(const vector<int>& data) {
    vector<int> arr = data;
    cout << "Quick Sort\n";
    cout << "Before: ";
    printArray(arr);
    quickSort(arr, 0, arr.size() - 1);
    cout << "After : ";
    printArray(arr);
    cout << "\n";
}

// ==============================
// 主程式
// ==============================
int main() {
    vector<int> bestCase1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> bestCase2 = {1, 2, 3, 4, 6, 5, 7, 8, 9, 10};
    vector<int> worstCase1 = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> worstCase2 = {100, 90, 80, 70, 60, 50, 40, 30, 20, 10};
    vector<int> radixCase  = {329, 457, 657, 839, 436, 720, 355};
    vector<int> mixedCase  = {42, 17, 93, 8, 23, 55, 4, 16, 77, 61};

    printTitle("Test Data 1: Best Case - Sorted");
    runSingleTest("Selection Sort", selectionSort, bestCase1);
    runSingleTest("Insertion Sort", insertionSort, bestCase1);
    runSingleTest("Bubble Sort", bubbleSort, bestCase1);
    runSingleTest("Shell Sort", shellSort, bestCase1);
    runMergeSortTest(bestCase1);
    runQuickSortTest(bestCase1);
    runSingleTest("Radix Sort", radixSort, bestCase1);
    runSingleTest("Heap Sort", heapSort, bestCase1);

    printTitle("Test Data 2: Near Best Case - Almost Sorted");
    runSingleTest("Selection Sort", selectionSort, bestCase2);
    runSingleTest("Insertion Sort", insertionSort, bestCase2);
    runSingleTest("Bubble Sort", bubbleSort, bestCase2);
    runSingleTest("Shell Sort", shellSort, bestCase2);
    runMergeSortTest(bestCase2);
    runQuickSortTest(bestCase2);
    runSingleTest("Radix Sort", radixSort, bestCase2);
    runSingleTest("Heap Sort", heapSort, bestCase2);

    printTitle("Test Data 3: Worst Case - Reverse Sorted");
    runSingleTest("Selection Sort", selectionSort, worstCase1);
    runSingleTest("Insertion Sort", insertionSort, worstCase1);
    runSingleTest("Bubble Sort", bubbleSort, worstCase1);
    runSingleTest("Shell Sort", shellSort, worstCase1);
    runMergeSortTest(worstCase1);
    runQuickSortTest(worstCase1);
    runSingleTest("Radix Sort", radixSort, worstCase1);
    runSingleTest("Heap Sort", heapSort, worstCase1);

    printTitle("Test Data 4: Another Reverse Large Values");
    runSingleTest("Selection Sort", selectionSort, worstCase2);
    runSingleTest("Insertion Sort", insertionSort, worstCase2);
    runSingleTest("Bubble Sort", bubbleSort, worstCase2);
    runSingleTest("Shell Sort", shellSort, worstCase2);
    runMergeSortTest(worstCase2);
    runQuickSortTest(worstCase2);
    runSingleTest("Radix Sort", radixSort, worstCase2);
    runSingleTest("Heap Sort", heapSort, worstCase2);

    printTitle("Test Data 5: Radix Test");
    runSingleTest("Selection Sort", selectionSort, radixCase);
    runSingleTest("Insertion Sort", insertionSort, radixCase);
    runSingleTest("Bubble Sort", bubbleSort, radixCase);
    runSingleTest("Shell Sort", shellSort, radixCase);
    runMergeSortTest(radixCase);
    runQuickSortTest(radixCase);
    runSingleTest("Radix Sort", radixSort, radixCase);
    runSingleTest("Heap Sort", heapSort, radixCase);

    printTitle("Test Data 6: Random Mixed");
    runSingleTest("Selection Sort", selectionSort, mixedCase);
    runSingleTest("Insertion Sort", insertionSort, mixedCase);
    runSingleTest("Bubble Sort", bubbleSort, mixedCase);
    runSingleTest("Shell Sort", shellSort, mixedCase);
    runMergeSortTest(mixedCase);
    runQuickSortTest(mixedCase);
    runSingleTest("Radix Sort", radixSort, mixedCase);
    runSingleTest("Heap Sort", heapSort, mixedCase);

    return 0;
}