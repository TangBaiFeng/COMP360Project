int sockMerchant(int n, vector<int> ar) {
    int evenSocks = 0;
    /* if the nested for loop finds a match, those two matches are placed together and        * adds a point to the number of evenSocks.
    */
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ar[i] == ar[j]) {
                ar[j] = ar[i + 1];
                ar[i + 1] = ar[i];
                i++;
                evenSocks++;
                break;
            }
        }
    }
    return evenSocks;
}