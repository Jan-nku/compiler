int main()
{
    int a = 0;
    int b = 1;
    int c = 2;
    int i, j, k;
    i = a + b;
    j = 2 * b;
    k = a + c;
    if (j == k && j > i)
    {
        k = k % 2;
    }
}