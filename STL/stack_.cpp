#include <iostream>


using namespace std;

template <typename T> 
struct Stack{
    T* data;
    int size = 0;
    void push(T item){
        data = (T*) realloc (data,size+1);
        data[size] = item;
        size++;
        is_empty = false;
    };
    T pop(){
        if(!is_empty){
            size--;
            T tmp  = data[size];

            data = (T*) realloc (data,size);
            
            return tmp;
        } else {
            throw "You trying pop() from empty stack mother fucker!";
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

void check(Stack<int> S){
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
    Stack<int> stack;
    

    check(stack);
    stack.push(2);
    stack.push(4);
    stack.push(6);
    stack.push(8);
    check(stack);
    stack.pop();
    check(stack);
    stack.push(10);
    check(stack);

    for (int i = 0; i < 4; i++){
        pops[i] = stack.pop();
        check(stack);
    }

    try
    {
        int a = stack.pop();
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