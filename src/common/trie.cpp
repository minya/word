#include "trie.h"

using std::wstring;
using std::vector;
using std::make_unique;


TrieNode::TrieNode(Char data): data(data) {
    memset(children, 0, ALPHABET_SIZE * sizeof(TrieNode*));
    for (auto& child : children) {
        child = nullptr;
    }
    isEndOfWord = false;
}

WordsTrie::WordsTrie(const vector<wstring>& words) {
    _root = make_unique<TrieNode>(' ');
    for (const auto& word : words) {
        insert(word);
    }
}

WordsTrie::WordsTrie() {
    _root = make_unique<TrieNode>(' ');
}

void WordsTrie::insert(const wstring& word) {
    TrieNode* current = _root.get();
    for (auto c: word) {
        auto index = charIndex(c);
        if (current->children[index] == nullptr) {
            current->children[index] = make_unique<TrieNode>(c);
        }
        current = current->children[index].get();
    }
    current->isEndOfWord = true;
}

WordsTrie::iterator::iterator(const TrieNode* node) : _node(node) {}

WordsTrie::iterator WordsTrie::begin() const {
    return iterator(_root.get());
}

WordsTrie::iterator WordsTrie::end() const {
    return iterator(nullptr);
}

bool WordsTrie::iterator::operator==(const WordsTrie::iterator& other) const {
    return _node == other._node;
}

bool WordsTrie::iterator::operator!=(const WordsTrie::iterator& other) const {
    return _node != other._node;
}

const TrieNode& WordsTrie::iterator::get() const {
    return *_node;
}

WordsTrie::iterator WordsTrie::find_next(
    const WordsTrie::iterator& current, Char next_char) const {
    if (current == end()) {
        return end();
    }
    auto index = charIndex(next_char);
    const auto& children = current.get().children; 
    if (children[index] == nullptr) {
        return end();
    }
    return iterator(children[index].get());
}
