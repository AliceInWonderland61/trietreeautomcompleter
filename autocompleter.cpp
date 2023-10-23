//
//  autocompleter.cpp
//  hwAC2
//
//  
//

#include "autocompleter.h"

Autocompleter::Autocompleter() {
    //node that i'm going to be using
    //set it to a new node
    root = new Node;
    count = 0;
}

// Must run in O(1) time.
void Autocompleter::insert(string x, int freq) {
    //something with count++
  ////add to the top of the vector
    //somehow use pushback
    //somehow use top vector
    //make an entry
    count++;
    Entry entering;
    entering.s = x;
    entering.freq = freq;

    Node* pushing;
    pushing = root;
    //sorting from highest to lowest frequency
    //make a control variable for the index that is the vector size -1
    pushing->top.push_back(entering);
    int control = pushing->top.size() - 1;

    //make a for loop
    for (int i = 0; i < pushing->top.size(); i++) {
        //if there's a frequency bigger than the control variable, swap
        if (pushing->top[control].freq > pushing->top[i].freq) {
            swap(pushing->top[control], pushing->top[i]);
        }
    }
    //only want 3 items in the top vector,
    if (pushing->top.size() > 3) {
        //so pop back last one when there are 4 items
        pushing->top.pop_back();
    }

    //something with Mark = true ->video comm
    for (int i = 0; i < x.size(); i++) {
        if (pushing->children[x[i]] == nullptr) {
            pushing->children[x[i]] = new Node;
        }
        pushing = pushing->children[x[i]];
        pushing->top.push_back(entering);
        int control = pushing->top.size() - 1;
        for (int i = 0; i < pushing->top.size(); i++) {
            //if there's a frequency bigger than the control variable, swap
            if (pushing->top[control].freq > pushing->top[i].freq) {
                swap(pushing->top[control], pushing->top[i]);
            }
        }
        if (pushing->top.size() > 3) {
            //so pop back last one when there are 4 items
            pushing->top.pop_back();
        }
    }
}

// Must run in O(1) time.
int Autocompleter::size() {
    return count;
}
// Fills the vector T with the three most-frequent completions of x.
// If x has less than three completions, then
// T is filled with all completions of x.
// The completions appear in T from most to least frequent.
//
// Must run in O(1) time.
void Autocompleter::completions(string x, vector<string>& T) {
    //first clear
    T.clear();
    vector<Entry> temp;
    Node* r = root;
    //when nullptr, return 0
    if (r == nullptr) {
        return;
    }
    else {//iterate through the string
        //min(unsigned(r.size()),unsigned(3))
        for (int i = 0; i < x.size(); i++) {
            if (r->children[x[i]] == nullptr) {
                return;
            }

            r = r->children[x[i]];
        }
        //iterate through the top vector, up to 3, no sorting here
          //r->top.size()
        for (int i = 0; i < r->top.size(); i++) {
            T.push_back(r->top[i].s);
        }
    }
}
