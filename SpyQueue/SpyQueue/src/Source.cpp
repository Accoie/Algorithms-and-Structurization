#include "QueueSpy.h"



void QueueSpy::addToQueue(int val1, int val2, int number) {
    Spy* newSpy = new Spy(val1, val2, number);
    if (last) {
        last->next = newSpy;
    }
    else {
        first = newSpy;
    }
    last = newSpy;
}

void QueueSpy::checkSpy(int& curr_time) {
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
    }
}

void QueueSpy::removeTimeOutSpies(int curr_time) {
    while (first && (first->queue_time - curr_time <= 0)) {
        std::cout << "����� #" << first->number << " ���� � ���������.\n";
        Spy* temp = first;
        first = first->next;
        delete temp;
        if (!first) {
            last = nullptr;
        }
    }
}

void QueueSpy::makeProtocol() {
    int curr_time = 0;
    while (first) {
        checkSpy(curr_time);
        removeTimeOutSpies(curr_time);
    }
}