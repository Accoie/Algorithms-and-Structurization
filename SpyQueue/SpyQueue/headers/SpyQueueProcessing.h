#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Spy {
    int spec_time, queue_time;
    string name;
    Spy* next;
    Spy* prev;
    Spy(int spec_time = 0, int queue_time = 0, string name = "без имени ") : spec_time(spec_time), queue_time(queue_time), name(name), next(nullptr), prev(nullptr) {};
};

class QueueSpy {
private:
    Spy* first;
    Spy* last;
    
public:
    QueueSpy() : first(nullptr), last(nullptr) {};
    void addToQueue(int val1, int val2, string name);
    void checkSpy(int &curr_time);
    void printTimeOutSpies(vector<Spy*> vec);
    int removeTimeOutSpies(int curr_time);
    bool clearTimeOutSpies(vector<Spy*> vec);
    void makeProtocol();
};