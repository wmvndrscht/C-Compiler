int f(int a);

int main(){
	return !( f(10)==42 && f(-1)==42 );
}