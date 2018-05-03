#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

typedef struct mapStruct_t mapStruct;
struct mapStruct_t {
    int key;
    int value;
};

class LRUcache
{
private:
    list <mapStruct *> lruList;
    unordered_map <int, list <mapStruct *>::iterator> cache;
    size_t capacity;
public:
    LRUcache (size_t c) : capacity(c) {}
    void set (int key, int value);
    int get (int key);
};

void LRUcache::set (int key, int value)
{
    unordered_map <int, list <mapStruct *>::iterator>::iterator it;
    mapStruct *newNode = new mapStruct, *front;

    it = cache.find(key);

    if (it != cache.end()) {
        lruList.erase(it->second);
        newNode->key = key;
        newNode->value = value;
        lruList.push_back(newNode);
        it->second = --lruList.end();
    } else {
        if (lruList.size() >= capacity) {
            front = lruList.front();
            cache.erase(front->key);
            lruList.pop_front();
        }
        newNode->key = key;
        newNode->value = value;
        lruList.push_back(newNode);
        cache[key] = --lruList.end();
    }
}

int LRUcache::get (int key)
{
    unordered_map <int, list <mapStruct *>::iterator>::iterator it;
    int retVal = -1;
    mapStruct *newNode = new mapStruct;

    it = cache.find(key);
    if (it != cache.end()) {
        retVal = (*(it->second))->value;
        lruList.erase(it->second);
        newNode->key = key;
        newNode->value = retVal;
        lruList.push_back(newNode);
        it->second = --lruList.end();
    }

    return retVal;
}

int main ()
{
    LRUcache cache(2);

    cache.set(1, 1);
    cache.set(2, 2);
    printf("Key: 1, value: %d\n", cache.get(1));
    cache.set(3 ,3);
    printf("Key: 2, value: %d\n", cache.get(2));
    printf("Key: 3, value: %d\n", cache.get(3));

    return 0;
}
