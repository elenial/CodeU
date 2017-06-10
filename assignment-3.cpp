#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#define f first
#define s second
using namespace std;

struct state {
    string word;
    pair<int, int> last_letter;
    vector<vector<bool> > visited;
};

/*Initializes an array of pairs that includes the different moves
we can make from a position in the grid*/

void initializemoves(pair<int, int> *moves) {
    moves[0] = make_pair(1, 0);
    moves[1] = make_pair(1, 1);
    moves[2] = make_pair(-1, 0);
    moves[3] = make_pair(-1, 1);
    moves[4] = make_pair(-1, -1);
    moves[5] = make_pair(0, 1);
    moves[6] = make_pair(0, -1);
    moves[7] = make_pair(1, -1);
}

/* Makes a state struct
word: the word formed
last_letter: the position in the grid of the last letter added to the word
parents_visited: the vector including which chars have been visited so far*/

state make_state(string word, pair<int, int> last_letter, vector<vector<bool> > parents_visited) {
    state st;
    st.word = word;
    st.last_letter = last_letter;
    st.visited.resize(parents_visited.size());
    for (int i = 0; i < st.visited.size(); i++) {
        st.visited[i].resize(parents_visited[i].size());
        for (int j = 0; j < parents_visited[i].size(); j++) {
            st.visited[i][j] = parents_visited[i][j];
        }
    }
    st.visited[last_letter.f][last_letter.s] = true;
    return st;
}


/*BFS from st with 
 nodes = the different words that can be formed
 and an edge exists between 2 nodes if
 we can get one word from the other in the grid*/

set<string> bfs(int r, int c, char **grid, pair<int, int> st) {
    pair<int, int> moves[8];
    initializemoves(moves);
    set<string> found;
    
    queue<state> Q;
    string k(1, grid[st.f][st.s]);
    if (!isPrefix(k)) {
        return found;
    }
    
    vector<vector<bool> > a(r, vector<bool>(c));
    
    Q.push(make_state(k, make_pair(st.f,st.s), a));
    
    while (!Q.empty()) {
        state curr = Q.front();
        Q.pop();
        
        if (isWord(curr.word) && !found.count(curr.word)) {
            found.insert(curr.word);
        }
        
        int curri = curr.last_letter.f;
        int currj = curr.last_letter.s;
        
        for (int i = 0; i < 8; i++) {
            int nexti = curri + moves[i].f;
            int nextj = currj + moves[i].s;
            if (nexti >= 0 && nexti < r && nextj >= 0 && nextj < c) {
                string adjacent(1, grid[nexti][nextj]);
                adjacent = curr.word + adjacent;
                if (!curr.visited[nexti][nextj] && isPrefix(adjacent)) {
                    state t = make_state(adjacent, make_pair(nexti, nextj), curr.visited);
                    Q.push(t);
                }
            }
        }
    }
    
    return found;
}

/*Word search by starting a BFS search from every 
char in the grid*/

set<string> word_search(int r, int c, char **grid) {
    set<string> found;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            set<string> se = bfs(r, c, grid, make_pair(i, j));
            set<string> :: iterator it;
            for (it = se.begin(); it != se.end(); it++) {
                if (!found.count(*it)) {
                    found.insert(*it);
                }
            }
        }
    }
    return found;
}
