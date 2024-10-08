#pragma once

#include <iostream>
#include <string>
#include <vector>

struct Spy {
    int spec_time, queue_time, number;
    Spy* next;
    Spy* prev;
    Spy(int spec_time = 0, int queue_time = 0, int number = 0) : spec_time(spec_time), queue_time(queue_time), number(number), next(nullptr), prev(nullptr) {};
};

class QueueSpy {
private:
    Spy* first;
    Spy* last;
    
public:
    QueueSpy() : first(nullptr), last(nullptr) {};
    void addToQueue(int val1, int val2, int number);
    void checkSpy(int &curr_time);
    void printTimeOutSpies(std::vector<Spy*> vec);
    int removeTimeOutSpies(int curr_time);
    bool clearTimeOutSpies(std::vector<Spy*> vec);
    void makeProtocol();
};