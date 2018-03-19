int f(int a,int b,int c,int d){
  int a1 = a+b+c+d;
  return a1;
}

int main(){
  return f(1,2,3,4) + f(1,2,3,4);
}
