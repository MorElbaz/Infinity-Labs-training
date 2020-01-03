
static void Merge(int *arr, size_t middle, size_t len)
{
    
int MergeSort(int *arr, size_t len)
{
    int *sorted_arr = malloc(len * sizeof(int));
    if(sorted_arr == NULL)
    {
        return (1);
    }
    
    if (len > 1)
    {
        if (MergeSort(sorted_arr, len/2) != 0)
        {
            return (1);
        }
    }
    
    if (len == 1)
    {
        
    }
    
    
