void revise()
{
	//pay attention to the order of tags
}
void pushdown()
{
	calculate current node
	revise sons
}
void maintain()
{
	pushdown(sons)
	update current node
}
void modify()
{
	if this is the segment
	{
		revise tags
		return
	}
	modify_subtree
	maintain()
}
int query()
{
	pushdown()
	query_subtree
}