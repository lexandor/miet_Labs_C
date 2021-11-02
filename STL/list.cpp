#include <iostream>


using namespace std;

template <typename T> 
struct List{
    T* data;
    int size = 0;
    void add(T item){
        data = (T*) realloc (data,size+1);
        data[size] = item;
        size++;
    };
    T remove(int index){
        int tmp;
        if(index >= 0 && index < size){
            int tmp = data[index];
            size--;

            for (int i = index; i < size; i++){
                data[i] = data[i+1];
            }

            data = (T*) realloc (data,size);

            return tmp;
        }
        else if (index < 0 && index < size){
            int tmp = data[size+index];
            size--;

            for (int i = size+1+index; i < size; i++){
                data[i] = data[i+1];
            }

            data = (T*) realloc (data,size);

            return tmp;
        } 
        else {
            throw "You trying remove() from empty list mother fucker!";
        };
    };
    T get(int index){
        if(index < size && index >= 0){
            return data[index];
        } else if (index < size && index < 0 && index+size > 0){
            return data[size+index];
        } else {
            throw "You trying get() in out of range list mother fucker!";
        }
    };
    void insert(int position, T item){
        if (position < size && position >= 0){
            data = (T*) realloc (data,size+1);
            size++;

            for (int i = position; i < size; i++){
                data[i+1] = data[i];
            };
            data[position] = item;
        }
        else if (position < size && position < 0 && position+size > 0){ //
            data = (T*) realloc (data,size+1);
            size++;

            for (int i = size+position; i < size; i++){
                data[i+1] = data[i];
            };

            data[size+position] = item;
        } 
        else if (position >= size){
            data = (T*) realloc (data,position);
            size = position + 1;
            data[position] = item;
        } else {
            throw "You trying insert() in out of range list mother fucker!";
        }
        
    };
    void set(int position, T item){
        if (position < size && position >= 0){
            data[position] = item;
        } 
        else if (position < size && position < 0 && position+size > 0){ //
            data[size+position] = item;
        } 
        else if (position >= size){
            data = (T*) realloc (data,position);
            size = position + 1; //
            data[position] = item;
        } else {
            throw "You trying set() in out of range list mother fucker!";
        }
        
    };
    int find(T item){
        for (int i = 0; i < size; i++){
            if (data[i] == item) return i;
        }
        return -1;
    }
    bool is_empty(){
        if (size > 0){
            return false;
        } else {
            return true;
        }
    };
};

void check(List<int> S){
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
    int pos;
    cout << "pos for ...: "; cin >> pos;
    int pops[4];
    List<int> list;
    

    check(list);
    list.add(2);
    list.add(4);
    list.add(6);
    list.add(8);
    check(list);

    
    int p = list.find(8);
    cout << "\nfind:--> " << p << endl;
    p = list.find(20);
    cout << "\nfind_e:--> " << p << endl;

    int t = list.get(1);
    cout << "\nget(1):--> " << t << endl;
    list.set(1,220);
    t = list.get(1);
    check(list);
    cout << "\nget(1):--> " << t << endl;
    t = list.get(-1);
    cout << "\nget(-1):--> " << t << endl;

    list.set(-3,77);
    check(list);

    list.insert(-2,0);
    check(list);

    for (int i = 0; i < 4; i++){
        try
        {
            pops[i] = list.remove(pos);
            cout << "\nremoved--> " << pops[i] << endl;
            check(list);
        }
        catch(const char* e)
        {
            cerr << e << '\n';
        }
    }
    for (int i = 0; i < 4; i++){
        cout << pops[i] << "\t";
    }; cout << "\n";

    

    system("pause");
    return 0;
}