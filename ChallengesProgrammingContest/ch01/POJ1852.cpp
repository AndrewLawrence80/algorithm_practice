#include <cstdio>
#include <vector>
#include <limits>

using namespace std;

void solve();

int main(int argc, char const *argv[])
{
    int num_case=0;
    scanf("%d",&num_case);
    while(num_case--){
        solve();
    }
    return 0;
}

void solve(){
    int length_pole=0,num_ants=0;
    scanf("%d %d",&length_pole,&num_ants);
    vector<int> ants(num_ants);
    for(int i=0;i<num_ants;i++){
        scanf("%d",&ants[i]);
    }
    int min_t=numeric_limits<int>::min();
    int max_t=numeric_limits<int>::min();
    for (int i=0;i<num_ants;i++){
        int candidate_min_t=min(length_pole-ants[i],ants[i]); // 当前蚂蚁掉落的最短时间
        int candidate_max_t=max(length_pole-ants[i],ants[i]); // 当前蚂蚁掉落的最长时间
        min_t=max(min_t,candidate_min_t); // 在所有蚂蚁掉落的最短时间中取大
        max_t=max(max_t,candidate_max_t); // 在所有蚂蚁掉落的最长时间中取大
    }
    printf("%d %d\n",min_t,max_t);
}
