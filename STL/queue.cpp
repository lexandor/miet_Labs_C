#include <iostream>


using namespace std;

template <typename T> 
struct Queue{
    T* data;
    int size = 0;
    void push(T item){
        data = (T*) realloc (data,size+1);
        data[size] = item;
        size++;
    };
    T pop(){
        if(size > 0){
            size--;
            T tmp = data[0];

            for (int i = 0; i < size; i++){
                data[i] = data[i+1];
            }

            data = (T*) realloc (data,size);

            return tmp;
        } else {
            throw "You trying pop() from empty queue mother fucker!";
        };
    };
    bool is_empty(){
        if (size > 0){
            return false;
        } else {
            return true;
        }
    };
};

void check(Queue<int> S){
    cout << "==========" << endl;
    cout << "Size: "     << S.size << endl;
    cout << "Is_Empty: " << S.is_empty() << endl;
    cout << "Data: "     << endl;
    for (int i = 0; i < S.size; i++){
        cout << S.data[i] << "\t";
    };
    cout << endl;
}

int main(){
    system("cls");

    int pops[4];
    Queue<int> queue;
    
    check(queue);
    queue.push(2);
    queue.push(4);
    queue.push(6);
    queue.push(8);
    check(queue);
    queue.pop();
    check(queue);
    queue.push(10);
    check(queue);

    for (int i = 0; i < 4; i++){
        pops[i] = queue.pop();
        check(queue);
    }

    try
    {
        int a = queue.pop();
        cout << "A: " << a << endl;
    }
    catch(const char* e)
    {
        cerr << e << '\n';
    }
    
    for (int i = 0; i < 4; i++){
        cout << pops[i] << "\t";
    }; cout << "\n";
    
    
  

    system("pause");
    return 0;
}