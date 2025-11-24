#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

class Node {
public:
	int _key;
	string _value;

	Node* prev;
	Node* next;

	Node() {
		prev = nullptr;
		next = nullptr;
	}

	Node(int key, string value) {
		_key = key;
		_value = value;
		prev = nullptr;
		next = nullptr;
	}
};

class Cache {
	int cache_capacity;
	int cache_size;

	unordered_map<int, Node*> cache_store;

	Node head;
	Node tail;

	public:
		Cache(int capacity)	{
			cache_size = 0;
			cache_capacity = capacity;

			head.next = &tail;
			tail.prev = &head;
		}

		string get(int key) {
			auto node = cache_store.find(key);
			if (node == cache_store.end()) {
				// Key does not exist
				return "";

			}
			else {
				// Key exist -> Move in priority
				auto node_ptr = cache_store[key];

				// Add on top
				head.next->prev = node_ptr;
				node_ptr->next = head.next;

				head.next = node_ptr;
				node_ptr->prev = &head;

				// Return value
				return node->second->_value;
			}
		}

		void put(int key, string value) {
			// If exist, update
			if (cache_store.find(key) != cache_store.end()) {
				auto node_ptr = cache_store[key];
				node_ptr->_value = value;

				// Add on top
				head.next->prev = node_ptr;
				node_ptr->next = head.next;

				head.next = node_ptr;
				node_ptr->prev = &head;
			
				return;
			}

			if (cache_capacity == cache_size) {
				// Remove last
				tail.prev = tail.prev->prev;
				tail.prev->next = &tail;

				// Remove from hashmap
				cache_store.erase(key);
				cache_size--;
			}

			// Add
			Node new_node(key, value);

			cache_store[key] = &new_node;
			cache_size++;

			// Add on top
			head.next->prev = &new_node;
			new_node.next = head.next;

			head.next = &new_node;
			new_node.prev = &head;
		}

		void visualise_cache() {
			Node* current_ptr;
			current_ptr = head.next;
			while (current_ptr->next != nullptr) {
				cout << current_ptr->_value << " ";
				current_ptr = current_ptr->next;
			}
			cout << endl;
		}
};

