int Copy(int x){// 可持久化
	id++;sz[id]=sz[x];L[id]=L[x];R[id]=R[x];
	v[id]=v[x];return id;}
int merge(int x,int y){
	// 合并x 和y 两颗子树, 可持久化到z 中
	if(!x||!y)return x+y;int z;
	int o=rand()%(sz[x]+sz[y]);// 注意rand 上限
	if(o<sz[x])z=Copy(y),L[z]=merge(x,L[y]);
	else z=Copy(x),R[z]=merge(R[x],y);
	ps(z);return z;
}
void split(int x,int&y,int&z,int k){
	// 将x 分成y 和z 两颗子树, y 的大小为k
	y=z=0;if(!x)return;
	if(sz[L[x]]>=k)z=Copy(x),split(L[x],y,L[z],k),ps(z);
	else y=Copy(x),split(R[x],R[y],z,k-sz[L[x]]-1),ps(y);}