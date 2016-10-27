#include <iostream>
#include <map>

using namespace std;

typedef struct node_t {
    int key;
    int value;
    node_t* prev;
    node_t* next;
} node_t;

class LRUCache
{
    private:
        node_t *head, *tail;
        size_t capacity;
        map <int, node_t*> cache_map;
    public:
        LRUCache (size_t s) {
            capacity = s;
            head = NULL;
            tail = NULL;
        }
        int get (int key);
        void set (int key, int value);
        void updateLRU (node_t* node);
        void displayCache ();
};

int LRUCache::get (int key)
{
    map<int, node_t*>::iterator it;

    if (cache_map.empty()) {
        return -1;
    }
    it = cache_map.find(key);
    if (it != cache_map.end()) {
        if (it->second != NULL) {
            updateLRU(it->second);
            return it->second->value;
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

void LRUCache::set (int key, int value)
{
    /*
     * Update the value of the key if the key is present.
     * Otherwise, check if the cache is full. If so, find the LRU key and replace it.
     * Update the LRU tag for all the keys.
     * If cache isn't full, insert the key at the end of the queue.
     */
    map <int, node_t*>::iterator it;
    node_t* nav = NULL, *tmpHead = NULL;

    it = cache_map.find(key);

    if (it != cache_map.end()) {
        /* Cache hit */
        it->second->value = value;
        updateLRU(it->second);
    } else {
        /* Cache miss*/
        if (cache_map.empty()) {
            head = new node_t;
            if (head == NULL) {
                cout << "Unable to create list\n";
                return;
            }
            head->key = key;
            head->value = value;
            head->next = NULL;
            head->prev = NULL;
            tail = head;
            cache_map[key] = head;
        } else {
            /* Cache miss */
            nav = new node_t;
            if (nav == NULL) {
                cout << "Failed to create node\n";
                return;
            }
            nav->key = key;
            nav->value = value;
            nav->next = NULL;
            nav->prev = tail;
            tail->next = nav;
            tail = nav;
            cache_map[key] = tail;
            if (cache_map.size() > capacity) {
                /* Cache full; replace LRU key */
                tmpHead = head;
                head->next->prev = head->prev;
                head = head->next;
                cache_map.erase(tmpHead->key);
                delete tmpHead;
            }
        }
    }
    return;
}

void LRUCache::updateLRU (node_t* node)
{
    if (head != tail) {
        if (node != head && node != tail) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            node->prev = tail;
            tail->next = node;
            node->next = NULL;
            tail = node;
        } else if (node == head) {
            node->next->prev = node->prev;
            head = node->next;
            node->next = NULL;
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
    }
    return;
}

void LRUCache::displayCache ()
{
    node_t* nav = NULL;

    if (head == NULL) {
        cout << "List is empty\n";
        return;
    }

    nav = head;

    cout << "Contents of cache\n";

    while (nav != NULL) {
        cout << nav->key << " " << nav->value << " " << endl;
        nav = nav->next;
    }
    return;
}
int main ()
{
    LRUCache cache(2);
    cache.set(2, 1);
    cache.set(1, 1);
    cache.displayCache();
    cout << "Value of key 2 is: " << cache.get(2) << endl;
    cache.set(4, 1);
    cache.displayCache();
    cout << "Value of key 1 is: " << cache.get(1) << endl;
    cout << "Value of key 2 is: " << cache.get(2) << endl;
    return 0;
}
