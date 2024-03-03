#include "find.h"

#include <algorithm>
#include <string_view>


using std::vector;
using std::wstring;
using std::wstring_view;

struct InterCallState {
    int i;
    int j;
    WordsTrie::iterator it;
    unsigned int score;
    unsigned int word_multiplier;
};

void findWordsDfs(
        const WordsTrie& trie,
        const Board& board,
        InterCallState state,
        vector<Char>& path,
        vector<FoundWord>& words,
        vector<vector<bool>>& visited) {

    const auto& [i, j, it, score, w_mul] = state;
    if (it == trie.end()) {
        return;
    }

    const auto& cell = board[i][j];
    path.push_back(cell.letter);
    visited[i][j] = true;

    if (it.get().isEndOfWord) {
        words.emplace_back(wstring{path.begin(), path.end()}, score * w_mul);
    }

    auto rows = static_cast<int>(board.size());
    auto cols = static_cast<int>(board[0].size());
    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            if (di == 0 && dj == 0) {
                continue;
            }

            int ni = i + di;
            int nj = j + dj;

            if (ni < 0 || ni >= rows || nj < 0 || nj >= cols) {
                continue;
            }

            if (visited[ni][nj]) {
                continue;
            }

            const auto& next_cell = board[ni][nj];
            auto next_it = trie.find_next(it, next_cell.letter);

            if (next_it != trie.end()) {
                int step_cost = static_cast<int>(path.size() + 1);
                auto updated_score = (score + step_cost * next_cell.step_multiplier());
                findWordsDfs(
                    trie,
                    board,
                    { ni, nj, next_it, updated_score, w_mul * next_cell.word_multiplier() },
                    path,
                    words,
                    visited);
            }
        }
    }

    visited[i][j] = false;
    path.pop_back();
}

vector<FoundWord> findWordsStartingFromCell(const Board& board, const WordsTrie& trie, int i, int j) {
    auto it = trie.begin();
    const auto& cell = board[i][j];
    vector<FoundWord> words;
    it = trie.find_next(it, cell.letter);
    if (it == trie.end()) {
        return words;
    }
    vector<Char> path;
    vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), false));
    findWordsDfs(trie, board, {i, j, it, cell.step_multiplier(), 1}, path, words, visited);
    return words;
}

vector<FoundWord> findWords(const Board& board, const WordsTrie& trie) {
    vector<FoundWord> words;
    auto rows = static_cast<int>(board.size());
    auto cols = static_cast<int>(board[0].size());
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          const auto ij_words = findWordsStartingFromCell(board, trie, i, j);
          words.insert(words.end(), ij_words.begin(), ij_words.end());
        }
    }
    sort(begin(words), end(words), [](const auto& a, const auto& b) {
        if (a.cost == b.cost) {
            return a.word < b.word;
        }
        return a.cost > b.cost;
    });
    auto unique_by = unique(words.begin(), words.end(), [](const auto& a, const auto& b) {
        return a.word == b.word;
    });
    words.erase(unique_by, words.end());
    return words;
}
