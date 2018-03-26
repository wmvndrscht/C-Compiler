int f(int a, int b){
    return a + b;
}

int g()
{
	int a = 6;
	int b = 7;
    return f(0,0)+f(1,2)+f(4,3)+f(a,b);
}