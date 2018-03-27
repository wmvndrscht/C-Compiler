int f(const char *a);

int main(){
	return !( (f("42")==42) && (f("-5")==-5));
}