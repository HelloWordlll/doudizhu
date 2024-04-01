/*************************************************************************
	> File Name: canju.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

enum class PAI_TYPE {
    DAN,
    DUIZI,
    SHUNZI,
    SANDAI,
    BUCHU,
    ZHA,
    SHUANGSHUN
};

class PAI {
public :
    PAI(PAI_TYPE type) : type(type) {}
    PAI_TYPE type;
    virtual bool operator<(PAI &) = 0;
    virtual void take(int *) = 0;
    virtual void back(int *) = 0;
    virtual ostream &output() = 0;
    virtual ~PAI() {}
};

class Shuangshun : public PAI {
public :
    int x, len;
    Shuangshun(int x, int len) : x(x), len(len), PAI(PAI_TYPE::SHUANGSHUN) {}
    bool operator<(PAI &obj) override {
        if (obj.type == PAI_TYPE::BUCHU) return true;
        if (obj.type == PAI_TYPE::ZHA) return true;
        if (obj.type != PAI_TYPE::SHUANGSHUN) return false;
        Shuangshun &_obj = dynamic_cast<Shuangshun &>(obj);
        if (len != _obj.len) return false;
        return x < _obj.x;
    }
    ostream &output() override {
        cout << "Shuang Shun ";
        for (int i = x; i < x + len; i++) {
            cout << i << " " << i << " ";
        }
        return cout;
    }
    void take(int *arr) override {
        for (int i = x; i < x + len; i++) {
            arr[i] -= 2;
        }
        return ;
    }
    void back(int *arr) override {
        for (int i = x; i < x + len; i++) {
            arr[i] += 2;
        }
        return ;
    }
    static vector<Shuangshun *> get(int *arr, int x, int len) {
        vector<Shuangshun *> ret;
        for (int i = x; i <= 14 - len + 1; i++) {
            int flag = 1;
            for (int j = i; j < i + len && flag; j++) {
                if (arr[j] < 2) flag = 0;
            }
            if (flag) {
                ret.push_back(new Shuangshun(i, len));
            }
        }
        return ret;
    }
    static vector<Shuangshun *> get(int *arr, int len) {
        return get(arr, 3, len);
    }
    static vector<Shuangshun *> get(int *arr) {
        vector<Shuangshun *> ret;
        for (int len = 3; len <= 12; len++) {
            auto temp = get(arr, len);
            for (auto x : temp) ret.push_back(x);
        }
        return ret;
    }
    virtual ~Shuangshun() {}
};
class Buchu : public PAI {
public :
    Buchu() : PAI(PAI_TYPE::BUCHU) {}
    bool operator<(PAI &obj) override {
        if (obj.type == PAI_TYPE::BUCHU) return false;
        return true;
    }
    ostream &output() override {
        cout << "pass";
        return cout;
    }
    void take(int *arr) override {
        return ;
    }
    void back(int *arr) override {
        return ;
    }
    static vector<Buchu *> get(int *arr) {
        return vector<Buchu *>(1, new Buchu());
    }
    virtual ~Buchu() {}
};

class Zha : public PAI {
public :
    int x;
    Zha(int x) : x(x), PAI(PAI_TYPE::ZHA) {}
    bool operator<(PAI &_obj) override {
        if (_obj.type == PAI_TYPE::BUCHU) return true;
        if (_obj.type != PAI_TYPE::ZHA) return false;
        Zha &obj = dynamic_cast<Zha &>(_obj);
        return x < obj.x;
    }
    ostream &output() override {
        if (x <= 15) cout << x << " Zha";
        else cout << "Wang Zha";
        return cout;
    }
    void take(int *arr) override {
        if (x <= 15) arr[x] -= 4;
        else arr[16] -= 1, arr[17] -= 1;
        return ;
    }
    void back(int *arr) override {
        if (x <= 15) arr[x] += 4;
        else arr[16] += 1, arr[17] += 1;
        return ;
    }
    static vector<Zha *> get(int *arr) {
        vector<Zha *> ret;
        for (int i = 3; i <= 15; i++) {
            if (arr[i] == 4) ret.push_back(new Zha(i));
        }
        if (arr[16] == 1 && arr[17] == 1) ret.push_back(new Zha(16));
        return ret;
    }
    virtual ~Zha() {}
};

class Dan : public PAI {
public :
    int x;
    Dan(int x) : x(x), PAI(PAI_TYPE::DAN) {}
    bool operator<(PAI &_obj) override {
        if (_obj.type == PAI_TYPE::BUCHU) return true;
        if (_obj.type == PAI_TYPE::ZHA) return true;
        if (_obj.type != PAI_TYPE::DAN) return false;
        Dan &obj = dynamic_cast<Dan &>(_obj);
        return x < obj.x;
    }
    ostream &output() override {
        cout << "Dan " << x;
        return cout;
    }
    void take(int *arr) override {
        arr[x] -= 1;
        return ;
    }
    void back(int *arr) override {
        arr[x] += 1;
        return ;
    }
    virtual ~Dan() {}
    static vector<Dan *> get(int *arr, int x) {
        vector<Dan *> ret;
        for (int i = x; i <= 17; i++) {
            if (arr[i] == 0) continue;
            ret.push_back(new Dan(i));
        }
        return ret;
    }
    static vector<Dan *> get(int *arr) {
        return get(arr, 3);
    }
};

class Duizi : public PAI {
public :
    int x;
    Duizi(int x) : x(x), PAI(PAI_TYPE::DUIZI) {}
    bool operator<(PAI &_obj) override {
        if (_obj.type == PAI_TYPE::BUCHU) return true;
        if (_obj.type == PAI_TYPE::ZHA) return true;
        if (_obj.type != PAI_TYPE::DUIZI) return false;
        Duizi &obj = dynamic_cast<Duizi &>(_obj);
        return x < obj.x;
    }
    ostream &output() override {
        cout << "Duizi " << x;
        return cout;
    }
    void take(int *arr) override {
        arr[x] -= 2;
        return ;
    }
    void back(int *arr) override {
        arr[x] += 2;
        return ;
    }
    virtual ~Duizi() {}
    static vector<Duizi *> get(int *arr, int x) {
        vector<Duizi *> ret;
        for (int i = x; i <= 17; i++) {
            if (arr[i] > 1) {
                ret.push_back(new Duizi(i));
            }
        }
        return ret;
    }
    static vector<Duizi *> get(int *arr) {
        return get(arr, 3);
    }
};

class Shunzi : public PAI {
public :
    int x, len;
    Shunzi(int x, int len) : x(x), len(len), PAI(PAI_TYPE::SHUNZI) {}
    bool operator<(PAI &_obj) override {
        if (_obj.type == PAI_TYPE::BUCHU) return true;
        if (_obj.type == PAI_TYPE::ZHA) return true;
        if (_obj.type != PAI_TYPE::SHUNZI) return false;
        Shunzi &obj = dynamic_cast<Shunzi &>(_obj);
        if (len != obj.len) return false;
        return x < obj.x;
    }
    ostream &output() override {
        cout << "Shunzi ";
        for (int i = x; i < x + len; i++) {
            cout << i << " ";
        }
        return cout;
    }
    void take(int *arr) override {
        for (int i = x; i < x + len; i++) arr[i] -= 1;
        return ;
    }
    void back(int *arr) override {
        for (int i = x; i < x + len; i++) arr[i] += 1;
        return ;
    }
    virtual ~Shunzi() {}
    static vector<Shunzi *> get(int *arr, int x, int len) {
        vector<Shunzi *> ret;
        for (int i = x; i <= 14 - len + 1; i++) {
            int flag = 1;
            for (int j = i; j < i + len && flag; j++) {
                if (arr[j] == 0) flag = 0;
            }
            if (flag) {
                ret.push_back(new Shunzi(i, len));
            }
        }
        return ret;
    }
    static vector<Shunzi *> get(int *arr, int len) {
        return get(arr, 3, len);
    }
    static vector<Shunzi *> get(int *arr) {
        vector<Shunzi *> ret;
        for (int len = 5; len <= 12; len++) {
            auto temp = get(arr, len);
            for (auto x : temp) ret.push_back(x);
        }
        return ret;
    }
};

class Sandai : public PAI {
public :
    int x;
    PAI *dai;
    Sandai(int x, PAI *dai) : x(x), dai(dai), PAI(PAI_TYPE::SANDAI) {}
    bool operator<(PAI &_obj) override {
        if (_obj.type == PAI_TYPE::BUCHU) return true;
        if (_obj.type == PAI_TYPE::ZHA) return true;
        if (_obj.type != PAI_TYPE::SANDAI) return false;
        Sandai &obj = dynamic_cast<Sandai &>(_obj);
        if (dai->type != obj.dai->type) return false;
        return x < obj.x;
    } 
    ostream &output() override {
        cout << "San " << x << " Dai ";
        dai->output();
        return cout;
    }
    void take(int *arr) override {
        arr[x] -= 3;
        dai->take(arr);
        return ;
    }
    void back(int *arr) override {
        arr[x] += 3;
        dai->back(arr);
        return ;
    }
    virtual ~Sandai() {
        delete dai;
    }
    static vector<Sandai *> get(int *arr, int x, Dan *obj) {
        vector<Sandai *> ret;
        for (int i = x; i <= 15; i++) {
            if (arr[i] < 3) continue;
            for (int j = 3; j <= 17; j++) {
                if (i == j) continue;
                if (arr[j] == 0) continue;
                ret.push_back(new Sandai(i, new Dan(j)));
            }
        }
        return ret;
    }
    static vector<Sandai *> get(int *arr, int x, Duizi *obj) {
        vector<Sandai *> ret;
        for (int i = x; i <= 15; i++) {
            if (arr[i] < 3) continue;
            for (int j = 3; j <= 17; j++) {
                if (i == j) continue;
                if (arr[j] < 2) continue;
                ret.push_back(new Sandai(i, new Duizi(j)));
            }
        }
        return ret;
    }
    static vector<Sandai *> get(int *arr, int x, Buchu *obj) {
        vector<Sandai *> ret;
        for (int i = x; i <= 15; i++) {
            if (arr[i] < 3) continue;
            ret.push_back(new Sandai(i, new Buchu()));
        }
        return ret;
    }
    static vector<Sandai *> get(int *arr) {
        vector<Sandai *> ret;
        auto temp1 = get(arr, 3, (Dan *)0);
        auto temp2 = get(arr, 3, (Duizi *)0);
        auto temp3 = get(arr, 3, (Buchu *)0);
        for (auto x : temp1) ret.push_back(x);
        for (auto x : temp2) ret.push_back(x);
        for (auto x : temp3) ret.push_back(x);
        return ret;
    }
};

class TreeNode {
public :
    TreeNode(PAI *p, int d) : win(0), p(p), d(d) {}
    int win, d;
    vector<TreeNode *> next;
    PAI *p;
};

bool checkEmpty(int *a) {
    for (int i = 3; i <= 17; i++) {
        if (a[i]) return 0;
    }
    return 1;
}

int count(int *a) {
    int sum = 0;
    for (int i = 3; i <= 17; i++) {
        sum += a[i];
    }
    return sum;
}

void output(TreeNode *root, TreeNode *new_node, int *a, int *b) {
    printf("[%d] ", root->d);
    root->p->output() << " then, ";
    printf("[%d] ", new_node->d);
    new_node->p->output();
    cout << " a : " << count(a) << ", b : " << count(b) << endl;
    return ;
}

TreeNode *getTree(TreeNode *root, int *a, int *b) {
    if (checkEmpty(b)) {
        root->win = 0;
        return root;
    }
    vector<Shunzi *>     temp1 = Shunzi::get(a);
    vector<Shuangshun *> temp2 = Shuangshun::get(a);
    vector<Sandai *> temp3 = Sandai::get(a);
    vector<Duizi *>  temp4 = Duizi::get(a);
    vector<Dan *>    temp5 = Dan::get(a);
    vector<Zha *>    temp6 = Zha::get(a);
    vector<Buchu *>  temp7 = Buchu::get(a);
    vector<PAI *> arr;
    for (auto x : temp1) arr.push_back(x);
    for (auto x : temp2) arr.push_back(x);
    for (auto x : temp3) arr.push_back(x);
    for (auto x : temp4) arr.push_back(x);
    for (auto x : temp5) arr.push_back(x);
    for (auto x : temp6) arr.push_back(x);
    for (auto x : temp7) arr.push_back(x);
    for (auto x : arr) {
        if (!root->p->operator<(*x)) {
            delete x;
            continue;
        }
        TreeNode *new_node = new TreeNode(x, root->d + 1);
        root->next.push_back(new_node);
        x->take(a);
        //output(root, new_node, a, b);
        getTree(new_node, b, a);
        x->back(a);
        if (new_node->win == 0) {
            root->win = 1;
            return root;
        }
    }
    return root;
}

void output_pai(const char *msg, int *a, const char *tail) {
    printf("%s", msg);
    for (int i = 3; i <= 17; i++) {
        for (int j = 0; j < a[i]; j++) {
            printf(" %d", i);
        }
    }
    printf("%s\n", tail);
    return ;
}

void output_solve(TreeNode *root, int *a, int *b) {
    int step = 0, a_flag = 0;
    do {
        output_pai("me : ", a, a_flag ? "" : " <---");
        output_pai("co : ", b, a_flag ? " <---" : "");
        cout << "----------------" << endl;
        for (int i = 0; i < root->next.size(); i++) {
            printf("%s : [%d] ", root->next[i]->win ? "opp" : "win", i);
            root->next[i]->p->output() << endl;
        }
        cout << 100 << " : quite" << endl; 
        cout << "----------------" << endl;
        cout << "index : ";
        cin >> step;
        if (step == 100) break;
        if (step >= root->next.size()) {
            cout << "please input right index" << endl;
            continue;
        }
        root = root->next[step];
        if (a_flag == 0) root->p->take(a);
        else root->p->take(b);
        root->p->output() << endl;
        a_flag ^= 1;
    } while (1);
    return ;
}

void read(FILE *fin, int *a) {
    int x;
    while (fscanf(fin, "%d", &x)) {
        if (x == 0) break;
        a[x] += 1;
    }
    return ;
}

int main() {
    int a[18] = {0};
    int b[18] = {0}, x;
    while(cin >> x){
        if(x == 0) break;
        a[x]++;
    }
    while(cin >> x){
        if(x == 0) break;
        b[x]++;
    }
    TreeNode *root = new TreeNode(new Buchu(), 0);
    cout << "analysing......" << endl;
    getTree(root, a, b);
    cout << "analysis done." << endl;
    if (root->win) {
        cout << "must win, go!" << endl;
    } else {
        cout << "must loss, opp!" << endl;
    }
    output_solve(root, a, b);
    return 0;
}

