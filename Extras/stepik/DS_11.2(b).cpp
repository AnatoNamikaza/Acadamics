
void Combi(vector<int> a, vector<int> b, int reqLen, int s, int currLen, bool check[], int l, int w, int sum_w, int sum_v, int& max)
{
    if (currLen > reqLen)
        return;
    else if (currLen == reqLen) {
        //cout << "\t";
        for (int i = 0; i < l; i++) {
            if (check[i] == true) {
                //cout << a[i] << " ";
                sum_w += a[i];
                sum_v += b[i];

                if (sum_w <= w)
                    if (sum_v > max)
                        max = sum_v;
            }
        }
        //cout << "\n";
        return;
    }
    if (s == l) {
        return;
    }
    check[s] = true;
    Combi(a, b, reqLen, s + 1, currLen + 1, check, l, w, sum_w, sum_v, max);
    check[s] = false;
    Combi(a, b, reqLen, s + 1, currLen, check, l, w, sum_w, sum_v, max);
}

int backpack(int W, vector<int> weights, vector<int> values) {
        
    int i, 
        n = weights.size(),
        sum_w = 0,
        sum_v = 0,
        max = 0;
    
    bool* check = new bool [n] {false};

    for (i = 1; i <= n; i++) 
        Combi(weights, values, i, 0, 0, check, n, W, sum_w, sum_v, max);
    
    return max;
}


int main() {

	int w = 4;
	vector<int> weights_of_item = { 1, 1, 2, 2 };
	vector<int> cost_of_item = { 1, 2, 4, 5 };

    cout << backpack(w, weights_of_item, cost_of_item);

    w = 10;
    weights_of_item = { 2, 3, 8 };
    cost_of_item = { 2, 5, 8 };

	cout << backpack(w, weights_of_item, cost_of_item);
}