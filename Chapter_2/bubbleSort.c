/*
 * Program 2.5 on page 41
 * A function that sorts an array of integers and counts
 * the number of interchanges made in the process
 */

static int count = 0;

// return true if interchanges are made
static int onePass(int a[], int n){
    int i;
    int interChanges = 0;
    int temp;

    for(i = 0; i < n-1; i++){
        if(a[i] > a[i + 1]){
            temp = a[i];
            a[i] = a[i + 1];
            a[i + 1] = temp;
            interChanges = 1;
            count++;
        }
    }
    return interChanges;
}

void clearCount(void){
    count = 0;
}

int getCount(void){
    return count;
}

// Sort a in ascending order
void bubbleSort(int a[], int n){
    int i;
    for(i = 0; i < n - 1; i++){
        if(!onePass(a, n - i)){
            break;
        }
    }
}