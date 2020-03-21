// Monika Wielgus

void sort(int arr[], int l, int r){
    int s=arr[(l+r)/2];
    int i;
    int j;
    int x;
    i=l;
    j=r;
    do{
        while(arr[i]<s) i++;
        while(arr[j]>s) j--;
        if (i<=j){
            x=arr[i];
            arr[i]=arr[j];
            arr[j]=x;
            i++;
            j--;
        }
    }
    while(i<=j);

    if(j>l) sort(arr, l, j);
    if(i<r) sort(arr, i, r);
}

int delete_rep(int arr[], int siz){
    if(siz==0||siz==1) return siz;

    int j=0;
    int temp[siz];
    for(int i=0; i<siz-1; i++)
        if (arr[i]!=arr[i+1])
            temp[j++]=arr[i];

    temp[j++]=arr[siz-1];

    for(int i=0; i<j; i++)
        arr[i]=temp[i];

    return j;
}

bool median(unsigned int n, const int *t, int (*f)(int), bool (*p)(int), double &r){
    int arr[n];
    int j=-1;
    for(unsigned int i=0; i<n; i++)
        if(p(t[i])==true){
            j++;
            arr[j]=f(t[i]);
        }
    if(j==-1)
        return false;
    else{
        sort(arr, 0, j);
        j=delete_rep(arr,j+1);
        if(j%2==0){
            r=(double)(arr[(j-2)/2]+(double)arr[((j-2)/2)+1])/2;
            return true;
        }
        else{
            r=arr[(j-1)/2];
            return true;
        }
    }
}

unsigned int help_gcd(int x, int y){
    if(x==0)
        return y;

    return help_gcd(y%x, x);
}

unsigned int gcd(unsigned int n, const int *t, int *r=nullptr){
    int *Z=new int[n];
    int p=-1;
    int n2=1;
    if(n==0) return 0;

    for(unsigned int i=0; i<n; i++)
        if(t[i]==t[i+1]) n2++;

    if(n2==n) return t[0];
    for (unsigned int i=0; i<n; i++)
        Z[i]=t[i];

    for(unsigned int i=0; i<n; i++){
        if(Z[i]==0){
            for (unsigned int j=i; j<n; j++){
                Z[j]=Z[j+1];
            }
        }
        else p++;
    }

    for(unsigned int i=0; i<=p; i++){
        if(Z[i]<0)
            Z[i]=-Z[i];

        else
            Z[i]=Z[i];
    }

    if(p==-1)
        return 0;
    else{
        int result=Z[0];
        for(unsigned int i=1; i<=p; i++)
            result=help_gcd(result, Z[i]);

        if(r!=nullptr){
            for(unsigned int i=0; i<n; i++)
                r[i]=t[i]/result;

            return result;
        }
    else
        return result;
    }
}
bool expval(unsigned int n, const double *x, const double *p, double (*f)(double), double &r){
    double sum=0;
    double first=0;
    double second=1.0;
    for(int i=0; i<n; i++){
        if (p[i]<0) return false;
        else sum+=p[i];
    }

    if(sum>=1) return false;
    else{
        for(int i=0; i<n; i++){
            first+=f(x[i])*p[i];
            second-=p[i];
        }

        r=first+f(x[n])*second;

        return true;
    }
}

unsigned int count(unsigned int n, const int *t, bool (*p)(int, int)=nullptr){

    unsigned int number=0;
    int arr[n];
    unsigned int d;
    for (unsigned int i=0; i<n; i++)
        arr[i]=t[i];

    sort(arr, 0, n-1);
    d=delete_rep(arr, n);
    if(p==nullptr){
        number=d*d;
        return number;
    }
    else{
        for (int i=0; i<d; i++){
            for (int j=0; j<d; j++){
                if(p(arr[i],arr[j])==true)
                    number++;
            }
        }
        return number;
    }
}

