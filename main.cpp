#include <iostream>
#define MAX 20
#define INFINITY 2147483647

using namespace std;

struct Connection;
struct Network;

struct Connection {
    char* IP = new char[MAX];
    int coast;
    Connection* next;
};

class List {
    public:
        List();
        void add(char IP[MAX], int coast);
        void print();
        Connection* start;
};

struct Network {
    char IP[MAX];
    int priority;
    List list;
};

class Heap {
    public:
        Heap();
        void makeConnections();
        void print();
        int minimumCoastNetwork();

    private:
        int sizeVector;
        Network* vector;

        int search(char IP[MAX]);
        bool compareStrings(char str1[MAX], char str2[MAX]);
        int sizeOfString(char str1[MAX]);
        int daddy(int i);
        int left(int i);
        int right(int i);
        void down(int i);
        void up(int i);
        void shift(int i, int j);
        void createMinHeap();
        Network getMin();
        void decreasesPriority(int i, int priority); 
};

// Métodos da classe Heap
Heap::Heap() {
    cin >> sizeVector;

    vector = new Network[sizeVector];

    for (int i = 0; i < sizeVector; i++) {
        cin >> vector[i].IP;
        vector[i].priority = INFINITY;
        vector[i].list = List();
    }
}

int Heap::search(char* IP) {
    for (int i = 0; i < sizeVector; i++) {
        if (compareStrings(vector[i].IP, IP)) return i;
    }

    return -1;
}

bool Heap::compareStrings(char* str1, char* str2) {
    bool isEquals = true;

    int sizeStr1, sizeStr2;

    for (sizeStr1 = 0; str1[sizeStr1]; sizeStr1++);
    for (sizeStr2 = 0; str1[sizeStr2]; sizeStr2++);

    if (sizeStr1 != sizeStr2) {
        isEquals = false;
    } else {
        for (int i = 0; i < sizeStr1; i++) {
            if (str1[i] != str2[i]) {
                isEquals = false;
                break;
            }
        }
    }

    return isEquals;
}

void Heap::makeConnections() {
    int sizeConnections;

    cin >> sizeConnections;

    for (int i = 0; i < sizeConnections; i++) {
        char* IP1 = new char[MAX];
        char* IP2 = new char[MAX];
        int coast;

        cin >> IP1;
        cin >> IP2;
        cin >> coast;

        int indexIP1 = search(IP1);
        int indexIP2 = search(IP2);

        vector[indexIP1].list.add(IP2, coast);
        vector[indexIP2].list.add(IP1, coast);
    }
}

void Heap::print() {
    for (int i = 0; i < sizeVector; i++) {
        cout << "IP: " << vector[i].IP << endl;
        cout << "PRIORIDADE: " << vector[i].priority << endl;
        cout << "CONEXÕES:" << endl;
        vector[i].list.print();
    }
    cout << endl;
}

int Heap::daddy(int i) {
    return (i - 1) / 2;
}

int Heap::left(int i) {
    return 2 * i + 1;
}

int Heap::right(int i) {
    return 2 * i + 2;
}

void Heap::down(int i) {
    int L, R, smaller = i;

    L = left(i);
    R = right(i);

    if (L < sizeVector && vector[L].priority < vector[i].priority) {
        smaller = L;
    }

    if (R < sizeVector && vector[R].priority < vector[smaller].priority) {
        smaller = R;
    }

    if (smaller != i) {
        shift(i, smaller);
        down(smaller);
    }
}

void Heap::up(int i) {
    while (vector[daddy(i)].priority > vector[i].priority) {
        shift(i, daddy(i));
        i = daddy(i);
    }
}

void Heap::shift(int i, int j) {
    Network aux = vector[i];
    vector[i] = vector[j];
    vector[j] = aux;
}

void Heap::createMinHeap() {
    for (int i = sizeVector / 2 - 1; i >= 0; i--) {
        down(i);
    }
}

Network Heap::getMin() {
    Network host;

    if (sizeVector > 0) {
        host = vector[0];
        vector[0] = vector[sizeVector - 1];
        sizeVector--;

        Network* newVector = new Network[sizeVector];

        for (int i = 0; i < sizeVector; i++) {
            newVector[i] = vector[i];
        }

        delete[] vector;

        vector = new Network[sizeVector];

        for (int i = 0; i < sizeVector; i++) {
            vector[i] = newVector[i];
        }

        delete[] newVector;

        down(0);

        return host;
    }

    Network net = {{""}, 0, List()};

    return net;
}

void Heap::decreasesPriority(int i, int priority) {
    if (vector[i].priority < priority) {
        cout << "ERRO: nova prioridade é maior que a existente" << endl;
    } else {
        vector[i].priority = priority;

        up(i);
    }
}

int Heap::minimumCoastNetwork() {
    vector[0].priority = 0;
    int total = 0;

    createMinHeap();

    while(sizeVector != 0) {
        Network min = getMin();

        total += min.priority;

        for (Connection* conn = min.list.start; conn != nullptr; conn = conn->next) {
            int indexNetwork = search(conn->IP);
            if (indexNetwork != -1 && conn->coast < vector[indexNetwork].priority) {
                decreasesPriority(indexNetwork, conn->coast);
            }
        }
    }

    return total;
}

// Métodos da classe List
List::List() {
    start = nullptr;
}

void List::add(char* IP, int coast) {
    Connection* conn = new Connection;

    conn->IP = IP;
    conn->coast = coast; 
    conn->next = start;

    start = conn;
}

void List::print() {
    for (Connection* current = start; current != nullptr; current = current->next) {
        cout << "IP: " << current->IP << endl;
        cout << "CUSTO: " << current->coast << endl;
    }
}

int main() {
    Heap h = Heap();
    h.makeConnections();

    cout << h.minimumCoastNetwork() << endl;

    return 0;
}