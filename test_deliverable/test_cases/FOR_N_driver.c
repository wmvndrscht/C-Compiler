int f(int a, int b);

int main(){
	return !( (f(0,0)==10) && (f(10,-5)==15));
}