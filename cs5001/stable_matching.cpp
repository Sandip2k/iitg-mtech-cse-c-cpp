#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <queue>
#include <algorithm>
#include <numeric>

class PairHash {
public:
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};

class StableMatching {
private:
    int n; // <- size of the sets M and W
    std::vector<std::vector<int>> m_w_preferences; // <- preference given by all m in M to all w in W.
    std::vector<std::vector<int>> w_m_preferences; // <- preference given by all w in W to all m in M.
    std::vector<bool> free_m; // keep a track of all m in M which are free at a point t.
    std::vector<bool> free_w; // keep a track of all w in W which are free at a point t.
    std::vector<int> m_proposed_w; // keep a track of which m has currently proposed to which w in their list.
    std::vector<std::vector<int>> sorted_m_w_order; // arrange all the w in W by the preference of each m in M.
public:
    static StableMatching *input();
    bool validate();
    std::unordered_set<std::pair<int, int>, PairHash> galeShapley();
    void printPreferenceMatrix();
    void printOrderedPreferences();
    StableMatching(int, std::vector<std::vector<int>>, std::vector<std::vector<int>>);
};

StableMatching::StableMatching(
    int n, 
    std::vector<std::vector<int>> m_w_preferences, 
    std::vector<std::vector<int>> w_m_preferences
) {
    this->n = n;
    this->m_w_preferences = m_w_preferences;
    this->w_m_preferences = w_m_preferences;
    this->free_m = std::vector<bool>(n, true);
    this->free_w = std::vector<bool>(n, true);
    this->m_proposed_w = std::vector<int>(n, -1);
}

StableMatching *StableMatching::input() {
    int n, temp;
    std::vector<std::vector<int>> m_w_preferences;
    std::vector<std::vector<int>> w_m_preferences;
    
    std::cout << "Enter size n: ";
    std::cin >> n;

    std::cout << "\n";

    for (int i = 0; i < n; ++i) {
        m_w_preferences.push_back({});
        std::cout << "Enter the preferences given by m_" << i << " to all w: ";
        for (int j = 0; j < n; ++j) {
            std::cin >> temp;
            m_w_preferences.back().push_back(temp);
        }
    }

    std::cout << "\n";

    for (int i = 0; i < n; ++i) {
        w_m_preferences.push_back({});
        std::cout << "Enter the preferences given by w_" << i << " to all m: ";
        for (int j = 0; j < n; ++j) {
            std::cin >> temp;
            w_m_preferences.back().push_back(temp);
        }
    }

    std::cout << "\n";

    auto inputData = new StableMatching(n, m_w_preferences, w_m_preferences);
    if (inputData->validate()) {
        for (int i = 0; i < n; ++i) {
            inputData->sorted_m_w_order.push_back({});
            
            std::vector<int> indices(n);
            std::iota(indices.begin(), indices.end(), 0);
            std::sort(
                indices.begin(),
                indices.end(),
                [inputData, i](int i1, int i2) { 
                    return inputData->m_w_preferences[i][i1] < inputData->m_w_preferences[i][i2]; 
                }
            );
            inputData->sorted_m_w_order[i] = indices;
        }
        return inputData;
    } else {
        delete(inputData);
        return NULL;
    }
}

bool StableMatching::validate() {
    bool validity = true;
    std::unordered_map<int, int> lookup;
    for (int i = 0; i < this->n; ++i) {
        for (int j = 0; j < this->n; ++j) {
            if (lookup.contains(m_w_preferences[i][j])) {
                std::cout 
                    << "Non-unique preference " 
                    << m_w_preferences[i][j] << " given by m_" << i 
                    << " to w_" << lookup[m_w_preferences[i][j]] << " and w_" << j << "\n"; 
                validity = false;
            }
            lookup[m_w_preferences[i][j]] = j;
        }
        lookup.clear();
    }

    for (int i = 0; i < this->n; ++i) {
        for (int j = 0; j < this->n; ++j) {
            if (lookup.contains(w_m_preferences[i][j])) {
                std::cout 
                    << "Non-unique preference " 
                    << w_m_preferences[i][j] << " given by w_" << i 
                    << " to m_" << lookup[w_m_preferences[i][j]] << " and m_" << j << "\n";
                validity = false;
            }
            lookup[w_m_preferences[i][j]] = j;
        }
        lookup.clear();
    }

    return validity;
}

void StableMatching::printPreferenceMatrix() {
    for (int i = -1; i < n; ++i) {
        if (i == -1) {
            std::cout << "\t";
            for (int j = 0; j < n; ++j) {
                std::cout << "w_" << j << "\t";
            }
            std::cout << "\n";
        } else {
            std::cout << "m_" << i << "\t";
            for (int j = 0; j < n; ++j) {
                std::cout << m_w_preferences[i][j] << "\t";
            }
            std::cout << "\n";
        }
    }

    std::cout << "\n";

    for (int i = -1; i < n; ++i) {
        if (i == -1) {
            std::cout << "\t";
            for (int j = 0; j < n; ++j) {
                std::cout << "m_" << j << "\t";
            }
            std::cout << "\n";
        } else {
            std::cout << "w_" << i << "\t";
            for (int j = 0; j < n; ++j) {
                std::cout << w_m_preferences[i][j] << "\t";
            }
            std::cout << "\n";
        }
    }

    std::cout << "\n";
}

void StableMatching::printOrderedPreferences() {
    for (int i = 0; i < n; ++i) {
        std::cout << "m_" << i << ": ";
        for (int j = 0; j < n; ++j) {
            std::cout << "w_" << m_w_preferences[i][j];
            if (j != n - 1) {
                std::cout << " > ";
            }
        }
        std::cout << "\n";
    }

    std::cout << "\n";

    for (int i = 0; i < n; ++i) {
        std::cout << "w_" << i << ": ";
        for (int j = 0; j < n; ++j) {
            std::cout << "m_" << w_m_preferences[i][j];
            if (j != n - 1) {
                std::cout << " > ";
            }
        }
        std::cout << "\n";
    }

    std::cout << "\n";
}

std::unordered_set<std::pair<int, int>, PairHash> StableMatching::galeShapley() {
    // m-centric version.
    std::unordered_map<int, std::pair<int, int>> lookup;
    std::queue<int> queue;
    // initially, all m in M are free, so we add them to the queue.
    for (int i = 0; i < this->n; ++i) {
        queue.push(i);
    }

    while (!queue.empty()) {
        int m = queue.front();
        bool pop = true; // pop only when m has paired up, otherwise m can try again.
        if (this->free_m[m] && this->m_proposed_w[m] < n) { // m is free, and there is a w in m's preference list to whom m has not proposed.
            this->m_proposed_w[m]++; // increment the index to find the next w in m's preference list.
            int w = this->sorted_m_w_order[m][this->m_proposed_w[m]]; // get the next w from m's ordered preference list.
            if (this->free_w[w] && !lookup.contains(w)) { // if this w is free, just pair up.
                lookup[w] = {m, w}; // add the match to our set.
                this->free_m[m] = false; // mark as paired up.
                this->free_w[w] = false; // mark as paired up.
            } else { // if this w is not free, need to make a decision based on w's preference list of all m.
                auto m_dash = lookup.at(w).first; // get the already paired up m_dash
                if (this->w_m_preferences[w][m] < this->w_m_preferences[w][m_dash]) { // if w prefers m to m_dash
                    lookup[w] = {m, w}; // update the match.
                    this->free_m[m] = false; // mark as paired up.
                    this->free_m[m_dash] = true; // mark as free.
                    queue.push(m_dash); // push to the queue for further trials.
                } else {
                    pop = false; // w prefers m_dash to m, let m try again in the next iteration.
                }
            }
        }
        if (pop) {
            queue.pop();
        }
    }

    std::unordered_set<std::pair<int, int>, PairHash> result;

    for (const auto& it: lookup) {
        result.insert(it.second);
    }

    return result;
}

int main() {
    StableMatching *input = StableMatching::input();
    input->printPreferenceMatrix();
    input->printOrderedPreferences();
    
    auto result = input->galeShapley();
    for (const auto &it: result) {
        std::cout << "(m_" << it.first << ", w_" << it.second << ") ";
    }

    return 0;
}