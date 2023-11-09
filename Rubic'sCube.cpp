#include <bits/stdc++.h>
using namespace std;
#define pb push_back
struct cublet {int e[7]; };
struct colors {char c[6][4];};

void print_cublet(const cublet& b){
    for (int r = 0; r < 7; ++r) {
        printf("%3d", b.e[r]);
    }
    printf("\n");
}

void read_cublet(colors& b){
    for (int r = 0; r < 6; ++r) {
        for(int cl = 0; cl < 4; ++cl){
            scanf("%s", &b.c[r][cl]);
        }
    }
}
cublet convert(const colors& b){
    cublet ans;
    string str;
    string arr[21]={"rgw","wrg","gwr","rwb","brw","wbr","ryg",
                    "gry","ygr","rby","yrb","byr","owg","gow",
                    "wgo","obw","wob","bwo","oyb","boy","ybo"};
    str.pb(b.c[0][0]);
    str.pb(b.c[3][1]);
    str.pb(b.c[4][2]);
    for (int i=0;i<21;i++){ 
        if (str==arr[i]){
            ans.e[i/3]=(0)*3+(i%3);
        }
    }
    str.clear();
    str.pb(b.c[0][1]);
    str.pb(b.c[4][3]);
    str.pb(b.c[1][0]);
    for (int i=0;i<21;i++){
        if (str==arr[i]){
            ans.e[i/3]=(1)*3+(i%3);
        }
    }
    str.clear();
    str.pb(b.c[0][2]);
    str.pb(b.c[5][0]);
    str.pb(b.c[3][3]);
    for (int i=0;i<21;i++){
        if (str==arr[i]){
            ans.e[i/3]=(2)*3+(i%3);
        }
    }
    str.clear();
    str.pb(b.c[0][3]);
    str.pb(b.c[1][2]);
    str.pb(b.c[5][1]);
    for (int i=0;i<21;i++){
        if (str==arr[i]){
            ans.e[i/3]=(3)*3+(i%3);
        }
    }
    str.clear();
    str.pb(b.c[2][0]);
    str.pb(b.c[4][0]);
    str.pb(b.c[3][0]);
    for (int i=0;i<21;i++){
        if (str==arr[i]){
            ans.e[i/3]=(4)*3+(i%3);
        }
    }
    str.clear();
    str.pb(b.c[2][1]);
    str.pb(b.c[1][1]);
    str.pb(b.c[4][1]);
    for (int i=0;i<21;i++){
        if (str==arr[i]){
            ans.e[i/3]=(5)*3+(i%3);
        }
    }
    str.clear();
    str.pb(b.c[2][3]);
    str.pb(b.c[5][3]);
    str.pb(b.c[1][3]);
    for (int i=0;i<21;i++){
        if (str==arr[i]){
            ans.e[i/3]=(6)*3+(i%3);
        }
    }
    return ans;
}

cublet front(const cublet& b){
    cublet o = b;
    int arr[21]={3,4,5,9,10,11,0,1,2,6,7,8,12,13,14,15,16,17,18,19,20};
    for (int i=0;i<7;i++){
        o.e[i]=arr[o.e[i]];
    }
    return o;
}

cublet right(const cublet& b){
    cublet o = b;
    int arr[21]={0,1,2,17,15,16,6,7,8,4,5,3,12,13,14,19,20,18,11,9,10};
    for (int i=0;i<7;i++){
        o.e[i]=arr[o.e[i]];
    }
    return o;
}

cublet up(const cublet& b){
    cublet o = b;
    int arr[21]={14,12,13,1,2,0,6,7,8,9,10,11,16,17,15,5,3,4,18,19,20};
    for (int i=0;i<7;i++){
        o.e[i]=arr[o.e[i]];
    }
    return o;
}

enum move { R=1,U=2,F=3,R2=4,U2=5,F2=6,R1=7,U1=8,F1=9};

int ord(const cublet& cublet){
    int val=0;
    int k=6;
    for (int r = 0; r < 7; ++r) {
        int v=cublet.e[r];
        val+=v*pow(21,k);
        k-=1;
    }
    return val;
}

cublet inverse(int ord){
    cublet node;
    int temp=ord;
    for (int r = 6; r >=0; r--) {
        node.e[r]=temp%21;
        temp=temp/21;
    }
    return node;
}
#define maxi (1800000000) 
// #define maxi (180000)
void print_moves(const std::vector<int>& moves){
    for (auto m: moves) {
        switch (m) {
        case U: printf("U "); break;
        case F: printf("F "); break;
        case R: printf("R "); break;
        case U1: printf("U' "); break;
        case F1: printf("F' "); break;
        case R1: printf("R' "); break;
        case U2: printf("U2 "); break;
        case F2: printf("F2 "); break;
        case R2: printf("R2 "); break;
        }
    }
    printf("\n");
}
std::vector<int> solve(const cublet& src, const cublet& dest){ 
    queue <int> q;
    int visited[maxi];
    int parent[maxi];
    int initial=ord(src);
    int final=ord(dest);
    q.push(ord(src));
    visited[ord(src)] = U;
    int temp=0;
    while (!q.empty()) {
        int child = q.front();
        q.pop();
        cublet u=inverse(child);
        if (child==final) {
            std::vector<int> moves;
            while (child!=initial) {
                moves.pb(visited[child]);
                child=parent[child];
            }
            std::reverse(moves.begin(), moves.end());
            std::vector<int> ans;
            int prev=0;
            for (auto cur:moves){
                auto tem=cur;
                if (cur==prev){
                    int fla=ans.back();
                    ans.pop_back();
                    if(fla==cur){
                        tem+=3;
                    }else{
                        tem+=6;
                    }
                }
                prev=cur;
                ans.pb(tem);
            }
            return ans;
        }

        cublet a = front(u);
        cublet b = right(u);
        cublet c = up(u);

        int aord = ord(a);
        int bord = ord(b);
        int cord = ord(c);

        if (!visited[aord]) {
            visited[aord] = F;
            parent[aord] = child;
            q.push(aord);
        }
        if (!visited[bord]) {
            visited[bord] = R;
            parent[bord] = child;
            q.push( bord);
        }
        if (!visited[cord]) {
            visited[cord] = U;
            parent[cord] = child;
            q.push(cord);
        }
        temp+=1;
    }
    return std::vector<int>();
}

int main(){
    cublet  dest;
    colors src1;
    read_cublet(src1);
    cublet src=convert(src1);

    for (int i=0;i<7;i++){
        dest.e[i]=i*3;
    }
    cout<<endl;
    cout<<"Starting configuration: "<<endl;
    print_cublet(src);
    cout<<"End configuration: "<<endl;
    print_cublet(dest);
    cout<<endl;
    auto moves = solve(src, dest);
    print_moves(moves);
}