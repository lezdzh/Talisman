const int N=1010;
const int INF = 1e9;
int n;
struct KM{
int w[N][N];
int lx[N], ly[N], match[N],way[N], slack[N];
bool used[N];
void initialization(){
    for(int i = 1; i <= n; i++){
        match[i] = 0;
        lx[i] = 0;
        ly[i] = 0;
        way[i] = 0;
    }
}
void hungary(int x){//for i(1 -> n) : hungary(i);
    match[0] = x;
    int j0 = 0;
    for(int j = 0; j <= n; j++){
        slack[j] = INF;
        used[j] = false;
    }
    do{
        used[j0] = true;
        int i0 = match[j0], delta = INF, j1;
        for(int j = 1; j <= n; j++){
            if(used[j] == false){
                int cur = -w[i0][j] - lx[i0] - ly[j];
                if(cur < slack[j]){
                    slack[j] = cur;
                    way[j] = j0;
                }
                if(slack[j] < delta){
                    delta = slack[j];
                    j1 = j;
                }
            }
        }
        for(int j = 0; j <= n; j++){
            if(used[j]){
                lx[match[j]] += delta;
                ly[j] -= delta;
            }
            else slack[j] -= delta;
        }
        j0 = j1;
    }while (match[j0] != 0);
    
    do{
        int j1 = way[j0];
        match[j0] = match[j1];
        j0 = j1;
    }while(j0);
}
    int get_ans(){//maximum ans
    int sum = 0;
    for(int i = 1; i<= n; i++)
        if(match[i] > 0) sum += -w[match[i]][i];
    return sum;
}
}KM_solver;
