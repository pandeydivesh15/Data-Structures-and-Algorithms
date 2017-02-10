#include <iostream>
#include <vector>
#include <iterator>
#include <stack>

using namespace std;

void merge(vector<int> &v, int left_start, int right_start, int right_end){
	//cout<<"$"<<left_start<<right_start<<right_end<<"\n";
	vector<int>::iterator itr = v.begin();
	vector<int> v1(itr + left_start, itr + right_start);
	vector<int> v2(itr + right_start, itr + right_end + 1);
	
	int i = 0, j = 0 , k = left_start;
	int l1 = right_start - left_start;
	int l2 = right_end - right_start + 1;

	while(i < l1 && j < l2){
		if (v1[i] <= v2[j])
        {
            v[k] = v1[i];
            i++;
        }
        else
        {
            v[k] = v2[j];
            j++;
        }
        k++;
	}
	while (i < l1){
        v[k] = v1[i];
        i++;
        k++;
    }
    while (j < l2){
        v[k] = v2[j];
        j++;
        k++;
    }
}

void  merge_sort(vector<int> &v){
	int size = v.size();

	int left_start, right_start, right_end; 
	for(int i = 1; i < size ; i = 2*i) {
		for(left_start = 0; left_start < size - 1; left_start += 2*i) {
			//cout<<left_start<<"\t"<<i<<"\n";
			right_start = left_start + i;

			right_end = left_start + 2*i - 1;

			if(right_end > size - 1) {
				right_end = size - 1;
			}
			//cout<<"$"<<left_start<<right_start<<right_end<<'\n';
			merge(v,left_start, right_start, right_end);
		}
	}
}

int create_partition(vector<int> &v, int left, int right){
	int x = v[right];
	int i = left - 1;

	for(int j = left; j < right; ++j) {
		if(v[j] <  x) {
			i++;
			int temp = v[j];
			v[j] = v[i];
			v[i] = temp;
		}
	}
	int temp = v[i+1];
	v[i+1] = v[right];
	v[right] = temp;

	return i+1;
}

void quick_sort(vector<int> &v){
	stack<int> S;
	int start = 0;
	int end = v.size() - 1;

	S.push(start);
	S.push(end);

	int part_index;

	while(!S.empty()){
		end = S.top();
		S.pop();
		start = S.top();
		S.pop();

		part_index = create_partition(v, start, end);

		if(part_index - 1 > start) {
			S.push(start);
			S.push(part_index - 1);
		}

		if(part_index + 1 < end) {
			S.push(part_index + 1);
			S.push(end);
		}
	}

}

int main()
{
	vector<int> v;
	cout<<"Enter size, choice for sorting method and finally your array.\n";
	int n;
	int ch;
	cin>>n>>ch;
	int input_count=0;
	int temp_input;
	while(input_count<n){
			cin>>temp_input;
			v.push_back(temp_input);
			input_count++;
	}
	if (ch)
		merge_sort(v);
	else
		quick_sort(v);
	copy(v.begin(), v.end(),
			ostream_iterator<int>(cout," "));
	
	return 0;
}