#pragma once
namespace Metro_line {

	template <class T>
	class list_iter;
	
	template <class T>
	struct B_list {
		B_list* next;
		T info;
		B_list<T>() : next(nullptr) {}
		B_list<T>(const B_list<T>& lst)  {
			if (lst) {
				info = lst->info;
				next = lst->next;
			}
		}
		B_list<T>* copy() {
			return new B_list<T>(*this);
		}
		
	};

	template <class T>
	class My_list {
		friend class list_iter<T>;
	protected:
		B_list<T>* first;
	public:
		My_list() : first(nullptr) {}

		~My_list();
		My_list(const My_list<T>& lst);
		My_list(My_list<T>&& second);
		My_list<T>& operator = (const My_list<T>& second);
		My_list<T>& operator = (My_list<T>&& second);
	

		void splice(list_iter<T> it, My_list<T> lst);
		void insert(list_iter<T> it, T elem);
		void push_back(T elem);
		void push_front(T elem);
		bool empty() const;
		list_iter<T> erase(list_iter<T> it);

		typedef list_iter<T> Iterator;
		Iterator begin() const;
		Iterator end() const;
	};
	template <class T>
	class list_iter {
	private:
		My_list<T>* st;
		B_list<T>* ptr;
	public:
		list_iter(My_list<T>* a) : st(a), ptr(a->first) {}
		const list_iter<T> operator ++ (int) {         
			list_iter<T> old = *this;
			if (ptr) {
				ptr = ptr->next;
			}
			return old;
		}
		B_list<T>* operator * () const {
			return this->ptr;
		}
		bool operator != (const list_iter<T>& it) const {
			if ((*it) == (get_ptr())) {
				My_list<T>* a = it.get_st(), *b = get_st();
				if (a->first == b->first) {
					return false;
				}
			}
			return true;
		}
		My_list<T>* get_st() const{
			return this->st;
		}
		B_list<T>* get_ptr() const{
			return this->ptr;
		}
		void set_ptr(B_list<T>* ptr) {
			this->ptr = ptr; 
		}
		void set_st(My_list<T>* st) {
			this->st = st;
		}
	};

	
	

	template <class T>
	list_iter<T> My_list<T>::begin() const {
		list_iter<T> it(const_cast<My_list<T>*>(this));
		return it; //инициализирующий конструктор
	}

	template <class T>
	list_iter<T> My_list<T>::end() const {
		My_list<T>* lst = new My_list<T>;
		lst->first = this->first;
		list_iter<T> it = list_iter<T>(const_cast<My_list<T>*>(lst));
		it.set_ptr(nullptr);
		return it;
	}

	template <class T>
	void My_list<T>::push_back(T elem) {
		B_list<T>* ptr = this->first;
		if (!ptr) {
			B_list<T>* n_elem = new B_list<T>;
			n_elem->info = elem;
			n_elem->next = nullptr;			//нуль при пустом списке
			this->first = n_elem;
			return;
		}
		while (ptr->next) {
			ptr = ptr->next;
		}
		B_list<T>* n_elem = new B_list<T>;
		n_elem->info = elem;
		n_elem->next = nullptr;
		ptr->next = n_elem;
	}

	template <class T>
	void My_list<T>::push_front(T elem) {
		B_list<T>* ptr = this->first;
		if (!ptr) {
			B_list<T>* n_elem = new B_list<T>;
			n_elem->info = elem;
			n_elem->next = nullptr;			//нуль при пустом списке
			this->first = n_elem;
			return;
		}
		B_list<T>* prev = ptr;
		while (ptr->next) {
			prev = ptr;
			ptr = ptr->next;
		}
		B_list<T>* n_elem = new B_list<T>;
		n_elem->info = elem;
		prev->next = n_elem;
		n_elem->next = ptr;
	}

	template <class T>
	bool My_list<T>::empty() const {
		if (this->first) {
			return false;
		}
		else {
			return true;
		}
	}

	template <class T>
	void My_list<T>::insert(list_iter<T> it, T elem) {
		B_list<T>* n_elem = new B_list<T>;
		n_elem->info = elem;
		Iterator iter = My_list<T>::begin(), prev_it = My_list<T>::begin();//error
		prev_it.set_ptr(nullptr);
		for (; iter != it; iter++) {
			prev_it = iter;
		}
		if (*prev_it) { //check if element is not first
			(*prev_it)->next = n_elem;
		}
		n_elem->next = it.get_ptr();
		if (it.get_ptr() == first) { //if inserted before first
			first = n_elem;
		}
	}

	template <class T>
	My_list<T>::~My_list() {
		Iterator it = My_list<T>::begin();
		for (; it != My_list<T>::end();) {
			delete (*it++);
		}
	}

	template <class T>
	My_list<T>::My_list(const My_list<T>& lst) {
		Iterator it = lst.My_list<T>::begin();

		for (; it != lst.My_list<T>::end(); it++) {
			T data_copy = (*it)->info;
			My_list<T>::push_back(data_copy);
		}
	}
	template <class T>
	My_list<T>::My_list(My_list<T>&& second) {
		Iterator it = My_list<T>::begin();
		for (; it != My_list<T>::end(); it++) {
			delete (*it);
		}

		first = second.first;
	}

	template <class T>
	My_list<T>& My_list<T>::operator = (My_list<T>&& second) {
		Iterator it;
		for (it = My_list<T>::begin(); it != My_list<T>::end(); it++) {
			delete (*it);
		}

		first = second.first;
		return *this;
	}

	template <class T>
	My_list<T>& My_list<T>::operator = (const My_list<T>& second) {
		Iterator it;
		for (it = My_list<T>::begin(); it != My_list<T>::end(); it++) {
			delete (*it);
		}

		for (it = second.My_list<T>::begin(); it != second.My_list<T>::end(); it++) {
			T data_copy = (*it)->info;
			My_list<T>::push_back(data_copy);
		}
		return *this;
	}

	template <class T>
	list_iter<T> My_list<T>::erase(list_iter<T> it) {
		Iterator iter = My_list<T>::begin(), prev_it = My_list<T>::begin();
		prev_it.set_ptr(nullptr);
		for (iter = My_list<T>::begin(); iter != it; iter++) {
			prev_it = iter;
		}
		if (!(*prev_it)) { //check if necessary to delete first element
			iter++;
			first = (*it)->next;
			delete (*it);
			return iter;
		}
		(*prev_it)->next = (*it)->next;
		iter++;
		delete (*it);
		return iter;
	}

	template <class T>
	void My_list<T>::splice(list_iter<T> it, My_list<T> lst) {
		Iterator iter = My_list<T>::begin();
		for (; iter != My_list<T>::end(); iter++) {
			My_list<T>::insert(it, (*iter)->info);
			delete(*iter);
		}
	}
}
