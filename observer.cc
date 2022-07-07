#include <iostream>
#include <list>

static int update_number = 0;
static int object_number = 0;
using namespace std;

class object {
    int _id;
public:
    object() : _id(object_number++) {}
    int getId() const {
        return _id;
    }
};

class update_object : public object {
private:
    int _id;
    std::string _ustr;
    // other update related data
public:
    update_object(int id, std::string ustr) : object(), _id(id), _ustr(ustr) {}

    int getId() const {
        return _id;
    }

    void print() const {
        cout << "oId: " << object::getId() << ", UId: " << getId() << ", update_str " << _ustr << endl;
    }
};

class observer {
public:
    virtual void update(const update_object *up) = 0;
};

class subject {
private:
public:
    virtual void attach(observer *ob) = 0;
    virtual void detach(observer *ob) = 0;
    virtual void set_message(std::string umess) = 0;
};

// each observer contains a subject
// observer can call subject APIs to make updates depending on new updates
class observer_imp : public observer, object {
private:
    subject *_s;
public:
    observer_imp(subject *s) : object(), _s(s) {
        this->_s->attach(this);
        cout << __FUNCTION__ << ", oId: " << object::getId() << endl;
    }
    
    void update(const update_object *up) {
        cout << "Received update ";
        up->print();
    }
};

// each subject contains a list of observers
// any update is propagated to all observers in the list
class subject_imp : public subject, object {
private:
    void notify() {
        update_object *u = new update_object(update_number++, message);
        std::list<observer*>::iterator it = observer_list.begin();
        while (it != observer_list.end()) {
            (*it)->update(u);
            it++;
        }
    }
public:
    subject_imp() : object() {
        cout << __FUNCTION__ << ", oId: " << object::getId() << endl;
    }
    
    void attach(observer *ab) {
        observer_list.push_back(ab);
    }

    void detach(observer *ab) {
        observer_list.remove(ab);
    }

    void set_message(std::string new_message) {
        message = new_message;
        notify();
    }
private:
    std::string message;
    std::list<observer*> observer_list;
};

int main(void) {
    subject *s1 = new subject_imp();
    observer *o1 = new observer_imp(s1);
    observer *o2 = new observer_imp(s1);
    observer *o3 = new observer_imp(s1);
    s1->set_message("hello world!");
    s1->set_message("hello world again!");
    return 0;
}
