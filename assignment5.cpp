#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <set>
#define not_found -1
using namespace std;

/* finds the 1st not common characters between 2 strings */
pair<char, char> find_first_not_common_chars(string a, string b)  {
    pair<char, char> first_not_common_chars = make_pair(not_found, not_found);
    int index_a = 0;
    int index_b = 0;
    
    while (index_a < a.length() && index_b < b.length()) {
        if (a[index_a] != b[index_b]) {
            first_not_common_chars.first = a[index_a];
            first_not_common_chars.second = b[index_b];
            break;
        }
        index_a++;
        index_b++;
    }
    
    return first_not_common_chars;
}

/* builds the adjacency matrix of the dag of chars */
map<char, vector<char> > build_adjacency_matrix(vector<string> dictionary) {
    map<char, vector<char> > adjacency_matrix;
    
    for (int i = 0; i < dictionary.size() - 1; i++) {
        pair<char, char> first_not_common_chars = find_first_not_common_chars(dictionary[i], dictionary[i + 1]);
        
        if (first_not_common_chars.first != not_found) {
            char first = first_not_common_chars.first;
            char second = first_not_common_chars.second;
            
            if (!adjacency_matrix.count(first)) {
                vector<char> adjacent_chars;
                adjacent_chars.push_back(second);
                adjacency_matrix.insert(make_pair(first, adjacent_chars));
            } else {
                adjacency_matrix[first].push_back(second);
            }
            
        }
        
    }
    
    return adjacency_matrix;
    
}

/* finds the in degrees of the nodes in the dag */
map<char, int> find_in_degrees(map<char, vector<char> > adjacency_matrix) {
    map<char, int> in_degrees;
    
    for (map<char, vector<char> >::iterator it = adjacency_matrix.begin(); it!=adjacency_matrix.end(); ++it) {
        vector<char> adj_chars = it -> second;
        for (int i = 0; i < adj_chars.size(); i++) {
            if (!in_degrees.count(adj_chars[i])) {
                in_degrees.insert(make_pair(adj_chars[i], 1));
            } else {
                in_degrees[adj_chars[i]]++;
            }
        }
    }
    
    return in_degrees;
}

/* visits node in the dag */
void visit(char char_to_visit, map<char, int> *in_degrees, set<char> *visited, map<char, vector<char> > adj_matrix, queue<char> *roots_of_dag) {
    vector<char> adj_chars = adj_matrix[char_to_visit];
    
    visited->insert(char_to_visit);
    
    for (int i = 0; i < adj_chars.size(); i++) {
        if (!visited->count(adj_chars[i])) {
            (*in_degrees)[adj_chars[i]]--;
            if ((*in_degrees)[adj_chars[i]] == 0) {
                roots_of_dag->push(adj_chars[i]);
            }
        }
    }
}

/* does the topological sorting and returns the ordered alphabet */
vector<char> topological_sort(map<char, vector<char> > adjacency_matrix, map<char, int> in_degrees, vector<string> dictionary) {
    vector<char> ordered_alphabet;
    set<char> visited;
    queue<char> roots_of_dag;
    
    /* adds all chars with 0 in degree to the queue */
    for (int i = 0; i < dictionary.size(); i++) {
        for (int j = 0; j < dictionary[i].size(); j++) {
            if (!in_degrees.count(dictionary[i][j])) {
                roots_of_dag.push(dictionary[i][j]);
            }
        }
    }
    
    while (!roots_of_dag.empty()) {
        char curr_node = roots_of_dag.front();
        roots_of_dag.pop();
        if (!visited.count(curr_node)) {
            ordered_alphabet.push_back(curr_node);
            visit(curr_node, &in_degrees, &visited, adjacency_matrix, &roots_of_dag);
        }
    }
    

    
    return ordered_alphabet;
}

/* returns ordered alphabet given a dictionary */
vector<char> alphabet(vector<string> dictionary) {
    vector<char> ordered_alphabet;
    map<char, vector<char> > adjacency_matrix;
    
    /* build adjacency matrix for graph */
    adjacency_matrix = build_adjacency_matrix(dictionary);
    
    /* find in degrees for topological sort */
    map<char, int> in_degrees = find_in_degrees(adjacency_matrix);
    
    /* topological sorting using dfs */
    ordered_alphabet = topological_sort(adjacency_matrix, in_degrees, dictionary);
    
    return ordered_alphabet;
}

void given_test() {
    vector<string> dictionary;
    string a = "ART";
    dictionary.push_back(a);
    a = "RAT";
    dictionary.push_back(a);
    a = "CAT";
    dictionary.push_back(a);
    a = "CAR";
    dictionary.push_back(a);
    
    vector<char> result = alphabet(dictionary);
    
    for (int i = 0; i < result.size(); i++) {
        cout<<result[i]<<" ";
    }
    cout << endl;
}

void test_all_chars_different() {
    vector<string> dictionary;
    string a = "ABC";
    dictionary.push_back(a);
    a = "DEF";
    dictionary.push_back(a);
    a = "GHI";
    dictionary.push_back(a);
    a = "JKL";
    dictionary.push_back(a);
    
    vector<char> result = alphabet(dictionary);
    
    for (int i = 0; i < result.size(); i++) {
        cout<<result[i]<<" ";
    }
    cout << endl;
}

void test_same_prefixes() {
    vector<string> dictionary;
    string a = "ABC";
    dictionary.push_back(a);
    a = "ABD";
    dictionary.push_back(a);
    a = "ABE";
    dictionary.push_back(a);
    a = "ABF";
    dictionary.push_back(a);
    
    vector<char> result = alphabet(dictionary);
    
    for (int i = 0; i < result.size(); i++) {
        cout<<result[i]<<" ";
    }
    cout << endl;
}

void test_same_word() {
    vector<string> dictionary;
    string a = "ABC";
    dictionary.push_back(a);
    a = "ABC";
    dictionary.push_back(a);
    a = "ABC";
    dictionary.push_back(a);
    a = "ABC";
    dictionary.push_back(a);
    
    vector<char> result = alphabet(dictionary);
    
    for (int i = 0; i < result.size(); i++) {
        cout<<result[i]<<" ";
    }
    cout << endl;
}

int main() {
    given_test();
    test_all_chars_different();
    test_same_prefixes();
    test_same_word();

    return 0;
}
