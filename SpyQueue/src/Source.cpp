#include "SpyQueueProcessing.h"
#include <iostream>
#include <vector>

using namespace std;

void QueueSpy::addToQueue(int val1, int val2, int number) {
    Spy* newSpy = new Spy(val1, val2, number);
    if (last) {
        last->next = newSpy;
        newSpy->prev = last; 
    }
    else {
        first = newSpy;
    }
    last = newSpy;
}

void QueueSpy::checkSpy(int &curr_time) {
    /*
    if (first && (first->queue_time - curr_time > 0)) {
        curr_time += first->spec_time;
        first->queue_time += first->spec_time;
        if (first != last) {
            std::cout << "Шпион #" << first->number << " понаблюдал за объектом " << first->spec_time << " минут.\n";
            last->next = first;
            last = first;
            first = first->next;
            last->next = nullptr;
        }
        else {
            std::cout << "Шпион #" << first->number << " понаблюдал за объектом " << first->spec_time << " минут.\n";
            delete first;
            first = nullptr;
            last = nullptr;
        }
    }*/
    if (first){
        cout << curr_time << " минут: Шпион #"<< first->number << " взял бинокль. \n\n";
        if (first->spec_time >= first->queue_time - curr_time) {
            curr_time += first->queue_time - curr_time;
        } else {
            curr_time += first->spec_time;
        }
        int prev_first_deleted = removeTimeOutSpies(curr_time);
        if (first == last && prev_first_deleted == 0) {
            cout << first->queue_time << " минут: Шпион #" << first->number << " сдал бинокль и ушел к резиденту.\n\n";
            delete first;
            first = nullptr;
            last = nullptr;
        } else if (first && prev_first_deleted == 0) {
            cout << curr_time << " минут: Шпион #" << first->number << " сдал бинокль.\n\n";
            last->next = first;
            Spy* temp = last;
            last = first;
            last->prev = temp;
            first = first->next;
            first->prev = nullptr;
            last->next = nullptr;
        }
        
    }
}

bool QueueSpy::clearTimeOutSpies(vector<Spy*> vec) {
    for (int i = 0; i != vec.size(); ++i) {
        if (vec[i]->prev && vec[i]->next) {
            Spy* temp = vec[i]->prev;
            temp->next = vec[i]->next;
            temp = vec[i]->next;
            temp->prev = vec[i]->prev;
        } else if (vec[i] == first) {
            first = vec[i]->next;
            first->prev = nullptr;
            return true;
        } else if (vec[i] == last) {
            last = vec[i]->prev;
            last->next = nullptr;
        }
        delete vec[i];
    }
    return false;
}
vector<Spy*> addAndSortIntoVector(vector<Spy*> vec, Spy* ptr){
    if (!vec.empty()) {
        int pos = 0;
        while (ptr->queue_time < vec[pos]->queue_time && pos != vec.size()) {
            pos++;
        }
        vec.resize(vec.size() + 1);
        for (int i = vec.size() - 1; i > pos; --i ) {
            vec[i] = vec[i - 1];
        }
        vec[pos] = ptr;
    } else {
        vec.push_back(ptr);
    }
    return vec;
}
void QueueSpy::printTimeOutSpies(vector<Spy*> vec) {
    for (int i = 0; i != vec.size(); ++i) {
        if (vec[i] == first) {
            cout << vec[i]->queue_time << " минут: Шпион #" << vec[i]->number << " сдал бинокль и ушел к резиденту.\n\n";
        } else {
            cout << vec[i]->queue_time << " минут: Шпион #" << vec[i]->number << " ушел к резиденту.\n\n";
        }
    }
}
int QueueSpy::removeTimeOutSpies(int curr_time) {
    vector<Spy*> timeOutSpies_vector = {};
    for (Spy* temp = first; temp != nullptr; temp = temp->next) {
        if (temp->queue_time <= curr_time) {
            timeOutSpies_vector = addAndSortIntoVector(timeOutSpies_vector, temp);
        }
    }
    printTimeOutSpies(timeOutSpies_vector);
    bool first_deleted = clearTimeOutSpies(timeOutSpies_vector);
    if (first_deleted) {
        return 1;
    } else {
        return 0;
    }
    /*while (first && (first->queue_time - curr_time <= 0)) {
        std::cout << "Шпион #" << first->number << " ушел к резиденту.\n";
        Spy* temp = first;
        first = first->next;
        delete temp;
        if (!first) {
            last = nullptr;
        }
    }*/
}

void QueueSpy::makeProtocol() {
    int curr_time = 0;
    while (first) {
        checkSpy(curr_time);
        
    }
}