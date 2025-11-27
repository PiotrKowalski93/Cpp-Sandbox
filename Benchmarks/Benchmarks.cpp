#include <iostream>
#include <list>
#include <vector>
#include <chrono>
#include <random>

using namespace std;


void ListVsVector_OneElement_push_back() {
    list<int> List = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
    vector<int> Vector = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };

    // Vector test
    auto startVector = chrono::high_resolution_clock::now();

    Vector.push_back(16);

    auto endVector = chrono::high_resolution_clock::now();
    auto timeVector = chrono::duration_cast<chrono::microseconds>(endVector - startVector).count();

    // List test
    auto startList = chrono::high_resolution_clock::now();

    List.push_back(16);

    auto endList = chrono::high_resolution_clock::now();
    auto timeList = chrono::duration_cast<chrono::microseconds>(endList - startList).count();

    cout << "1 Element:" << endl;
    cout << "vector.push_back() = " << timeVector << endl;
    cout << "list.push_back() = " << timeList << endl;
    cout << endl;
    cout << endl;
}

void ListVsVector_ManyElements_push_back() {
    list<int> List = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
    vector<int> Vector = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };

    // Vector test
    auto startVector = chrono::high_resolution_clock::now();

    for (size_t i = 0; i < 100; i++)
    {
        Vector.push_back(i);
    }

    auto endVector = chrono::high_resolution_clock::now();
    auto timeVector = chrono::duration_cast<chrono::microseconds>(endVector - startVector).count();

    // List test
    auto startList = chrono::high_resolution_clock::now();

    for (size_t i = 0; i < 100; i++)
    {
        List.push_back(16);
    }

    auto endList = chrono::high_resolution_clock::now();
    auto timeList = chrono::duration_cast<chrono::microseconds>(endList - startList).count();

    cout << "100 Elements:" << endl;
    cout << "vector.push_back() = " << timeVector << endl;
    cout << "list.push_back() = " << timeList << endl;
    cout << endl;
}

void ListVsVector_OneElement_push_front() {
    list<int> List = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
    vector<int> Vector = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };

    // Vector test
    auto startVector = chrono::high_resolution_clock::now();

    Vector.insert(Vector.begin(), 0);

    auto endVector = chrono::high_resolution_clock::now();
    auto timeVector = chrono::duration_cast<chrono::microseconds>(endVector - startVector).count();

    // List test
    auto startList = chrono::high_resolution_clock::now();

    List.push_front(16);

    auto endList = chrono::high_resolution_clock::now();
    auto timeList = chrono::duration_cast<chrono::microseconds>(endList - startList).count();

    cout << "1 Element:" << endl;
    cout << "vector.insert() = " << timeVector << endl;
    cout << "list.push_front() = " << timeList << endl;
    cout << endl;
    cout << endl;
}

void ListVsVector_ManyElements_push_front() {
    list<int> List = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
    vector<int> Vector = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };

    // Vector test
    auto startVector = chrono::high_resolution_clock::now();

    for (size_t i = 0; i < 100; i++)
    {
        Vector.insert(Vector.begin(), i);
    }

    auto endVector = chrono::high_resolution_clock::now();
    auto timeVector = chrono::duration_cast<chrono::microseconds>(endVector - startVector).count();

    // List test
    auto startList = chrono::high_resolution_clock::now();

    for (size_t i = 0; i < 100; i++)
    {
        List.push_front(i);
    }

    auto endList = chrono::high_resolution_clock::now();
    auto timeList = chrono::duration_cast<chrono::microseconds>(endList - startList).count();

    cout << "100 Elements:" << endl;
    cout << "vector.insert() = " << timeVector << endl;
    cout << "list.push_front() = " << timeList << endl;
    cout << endl;
}

void ListVsVector_Iteration() {
    list<int> List = { };
    vector<int> Vector = { };

    for (size_t i = 0; i < 3000; i++)
    {
        Vector.insert(Vector.begin(), i);
    }

    for (size_t i = 0; i < 3000; i++)
    {
        List.push_front(i);
    }

    // Vector test
    auto startVector = chrono::high_resolution_clock::now();

    for (int i : Vector)
    {   
    }

    auto endVector = chrono::high_resolution_clock::now();
    auto timeVector = chrono::duration_cast<chrono::microseconds>(endVector - startVector).count();

    // List test
    auto startList = chrono::high_resolution_clock::now();

    for (int i : List)
    {
    }

    auto endList = chrono::high_resolution_clock::now();
    auto timeList = chrono::duration_cast<chrono::microseconds>(endList - startList).count();

    cout << "300 Elements Iteration:" << endl;
    cout << "vector = " << timeVector << endl;
    cout << "list = " << timeList << endl;
    cout << endl;
}

/// <summary>
/// 80% Insert
/// 10% Erase
/// 10% Scan
/// </summary>
void List_SimulateOrderBookOperations() {
    
    int INITIAL_SIZE = 100'000;
    int OPS = 50'000;

    double INSERT_RATIO(0.80);
    double ERASE_RATIO(0.10);
    double SCAN_RATIO(0.10);
    
    mt19937 rng(123);
    uniform_int_distribution<int> value_gen(1, 1'000'000);

    list<int> List;

    for (int i = 0; i < INITIAL_SIZE; i++)
        List.push_back(value_gen(rng));

    uniform_real_distribution<double> op_pick(0.0, 1.0);
    uniform_int_distribution<int> index_pick(0, INITIAL_SIZE);

    // Start Count
    auto startList = chrono::high_resolution_clock::now();

    for (int i = 0; i < OPS; i++)
    {
        double operation = op_pick(rng);
    
        if (operation < INSERT_RATIO) {
            // Insert
            int pos = index_pick(rng) % (List.size() + 1);

            auto list_it = List.begin();
            advance(list_it, pos);

            List.insert(list_it, value_gen(rng));
        }
        else if (operation < INSERT_RATIO + ERASE_RATIO) {
            // Delete
            if (List.empty()) {
                continue;
            }

            int pos = index_pick(rng) % List.size();

            auto it = List.begin();
            std::advance(it, pos);

            List.erase(it);
        }
        else {
            // Iterate
            long long sum = 0;
            for (int x : List)
                sum += x;
        }
    }

    // End Count
    auto endList = chrono::high_resolution_clock::now();
    auto timeList = chrono::duration_cast<chrono::microseconds>(endList - startList).count();

    cout << "list = " << timeList << endl;
 }

void Vector_SimulateOrderBookOperations() {
    int INITIAL_SIZE = 100'000;
    int OPS = 50'000;

    double INSERT_RATIO = 0.80;
    double ERASE_RATIO = 0.10;
    double SCAN_RATIO = 0.10;

    mt19937 rng(123);
    uniform_int_distribution<int> value_gen(1, 1'000'000);

    vector<int> Vector;

    for (int i = 0; i < INITIAL_SIZE; i++)
        Vector.push_back(value_gen(rng));

    uniform_real_distribution<double> op_pick(0.0, 1.0);
    uniform_int_distribution<int> index_pick(0, INITIAL_SIZE);

    // Start Count
    auto startVector = chrono::high_resolution_clock::now();

    for (int i = 0; i < OPS; i++)
    {
        double operation = op_pick(rng);

        if (operation < INSERT_RATIO) {
            // Insert
            int pos = index_pick(rng) % (Vector.size() + 1);

            auto list_it = Vector.begin();
            advance(list_it, pos);

            Vector.insert(list_it, value_gen(rng));
        }
        else if (operation < INSERT_RATIO + ERASE_RATIO) {
            // Delete
            if (Vector.empty()) {
                continue;
            }

            int pos = index_pick(rng) % Vector.size();

            auto it = Vector.begin();
            std::advance(it, pos);

            Vector.erase(it);
        }
        else {
            // Iterate
            long long sum = 0;
            for (int x : Vector)
                sum += x;
        }
    }

    // End Count
    auto endVector = chrono::high_resolution_clock::now();
    auto timeVector = chrono::duration_cast<chrono::microseconds>(endVector - startVector).count();

    cout << "vector = " << timeVector << endl;
}

int main()
{
    // Adding at the end:
    ListVsVector_OneElement_push_back();
    ListVsVector_ManyElements_push_back();

    // Adding on front:
    ListVsVector_OneElement_push_front();
    ListVsVector_ManyElements_push_front();

    // Iterating:
    ListVsVector_Iteration();

    // Order Book like simulation
    cout << "Collection size: 100 000 | Operations: 50 000" << endl;
    List_SimulateOrderBookOperations();
    Vector_SimulateOrderBookOperations();
}