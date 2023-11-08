#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct board {
    char e[3][3];
};

int power(int base,int exponent) {
    if (exponent == 0)
        return 1;
    else if (exponent > 0)
        return base * power(base, exponent - 1);
    else
        return (1 / base) * power(base, exponent + 1);
}

int ord(const board& board)
{
    int a = 0;
    int n = 0;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            char v = board.e[r][c];
            if(v == 'Z'){
                a += 7*power(10,n);
            }
            else if(v=='U'){
                a += 1*power(10,n);
            }
            else if(v=='D'){
                a += 2*power(10,n);
            }
            else if(v=='N'){
                a += 3*power(10,n);
            }
            else if(v=='E'){
                a += 4*power(10,n);
            }
            else if(v=='W'){
                a += 5*power(10,n);
            }
            else if(v=='S'){
                a += 6*power(10,n);
            }
            n += 1;
        }
    }
    return a;
}

void print_board(const board& b){
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            printf("%c ", b.e[r][c]);
        }
        printf("\n");
    }
}

void read_board(board& b){
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            scanf("%c", &b.e[r][c]);
        }
    }
}

pair<int, int> find_space(const board& b){
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (b.e[r][c] == 'Z') return { r, c };
}

board up(const board& b)
{
    pair <int,int>p= find_space(b);
    int r=p.first; int c=p.second;
    if (r == 2) return b;
    board o = b;
    if (o.e[r+1][c] == 'U'){
        o.e[r][c] = 'N';
    }
    else if (o.e[r+1][c] == 'N'){
        o.e[r][c] = 'D';
    }
    else if (o.e[r+1][c] == 'D'){
        o.e[r][c] = 'S';
    }
    else if(o.e[r+1][c] == 'S'){
        o.e[r][c] = 'U';
    }
    else if (o.e[r+1][c] == 'E' or o.e[r+1][c] == 'W'){
        o.e[r][c] = o.e[r+1][c];
    }
    o.e[r+1][c] = 'Z';
    return o;
}

board down(const board& b)
{
    pair <int,int>p= find_space(b);
    int r=p.first; int c=p.second;
    if (r == 0) return b;
    board o = b;
    if (o.e[r-1][c] == 'U'){
        o.e[r][c] = 'S';
    }
    else if (o.e[r-1][c] == 'N'){
        o.e[r][c] = 'U';
    }
    else if (o.e[r-1][c] == 'D'){
        o.e[r][c] = 'N';
    }
    else if(o.e[r-1][c] == 'S'){
        o.e[r][c] = 'D';
    }
    else if (o.e[r-1][c] == 'E' or o.e[r-1][c] == 'W'){
        o.e[r][c] = o.e[r-1][c];
    }
    o.e[r-1][c] = 'Z';
    return o;
}

board left(const board& b)
{
    pair <int,int>p= find_space(b);
    int r=p.first; int c=p.second;
    if (c == 2) return b;
    board o = b;
    if (o.e[r][c+1] == 'U'){
        o.e[r][c] = 'W';
    }
    else if (o.e[r][c+1] == 'W'){
        o.e[r][c] = 'D';
    }
    else if (o.e[r][c+1] == 'D'){
        o.e[r][c] = 'E';
    }
    else if(o.e[r][c+1] == 'E'){
        o.e[r][c] = 'U';
    }
    else if (o.e[r][c+1] == 'N' or o.e[r][c+1] == 'S'){
        o.e[r][c] = o.e[r][c+1];
    }
    o.e[r][c+1] = 'Z';
    return o;
}

board right(const board& b)
{
    pair <int,int>p= find_space(b);
    int r=p.first; int c=p.second;
    if (c == 0) return b;
    board o = b;
    if (o.e[r][c-1] == 'U'){
        o.e[r][c] = 'E';
    }
    else if (o.e[r][c-1] == 'W'){
        o.e[r][c] = 'U';
    }
    else if (o.e[r][c-1] == 'D'){
        o.e[r][c] = 'W';
    }
    else if(o.e[r][c-1] == 'E'){
        o.e[r][c] = 'D';
    }
    else if (o.e[r][c-1] == 'N' or o.e[r][c-1] == 'S'){
        o.e[r][c] = o.e[r][c-1];
    }
    o.e[r][c-1] = 'Z';
    return o;
}

bool is_same1(const board& a, const board &b){
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (a.e[r][c] != b.e[r][c]) return false;

    return true;
}

enum move { L = 1, R = 2, U = 3, D = 4 };

vector<int> solve(const board& src, const board& dest){
    queue <board> q;
    int visited[power(10,10)];
    board parent[power(10,10)];

    q.push(src);
    visited[ord(src)] = L;

    while (!q.empty()){
        board u = q.front();
        q.pop();
        if (is_same1(u, dest)){
            std::vector<int> moves;
            board c = u;
            int o = ord(c);
            while (!is_same1(c, src)) {
                moves.push_back(visited[o]);
                 c = parent[o];
                 o = ord(c);
            }
            reverse(moves.begin(), moves.end());
            return moves;
        }

        board a = up(u);
        board b = down(u);
        board c = left(u);
        board d = right(u);

        int aord = ord(a);
        int bord = ord(b);
        int cord = ord(c);
        int dord = ord(d);

        if (!visited[aord]) {
            visited[aord] = U;
             parent[aord] = u;
             q.push(a);
        }
        if (!visited[bord]) {
            visited[bord] = D;
             parent[bord] = u;
             q.push(b);
        }
        if (!visited[cord]) {
            visited[cord] = L;
             parent[cord] = u;
             q.push(c);
        }
        if (!visited[dord]) {
            visited[dord] = R;
             parent[dord] = u;
             q.push(d);
        }
    }

}

void print_moves(const vector<int>& moves){
    for (auto m: moves) {
        switch (m) {
            case L: printf("L "); break;
            case R: printf("R "); break;
            case U: printf("U "); break;
            case D: printf("D "); break;
        }
    }
    printf("\n");
}

int main(){
    board src, dest;

    read_board(src);
    print_board(src);

    for (int r = 0; r < 3; ++r){
        for (int c = 0; c < 3; ++c){
            if (src.e[r][c] == 'U'){
                dest.e[r][c] = 'D';
            }
            else{
                dest.e[r][c] = 'Z';
            }
        }
    }

    auto moves = solve(src, dest);
    print_moves(moves);
    print_board(dest);

    return 0;
}