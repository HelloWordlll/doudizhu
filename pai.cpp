#include<iostream>
#include<vector>
#include<stack>
using namespace std;

#define MAX_N 18

string name[MAX_N + 5] = {
    "", "", "", "3", "4", "5", "6", "7", "8", "9", "10",
    "J", "Q", "K", "Ace", "2", "joker", "JOKER"
};

enum class TYPE{
    DAN_TYPE,
    DUI_TYPE,
    SHUNZHI_TYPE,
    SHANDAI_TYPE,
    ZHADAN_TYPE,
    WANGZHA_TYPE,
    PASS_TYPE
};

class PAI {
public : 
    PAI(TYPE type) : type(type) {}
    static vector<PAI *> getPai(int *);
    virtual bool operator>(PAI &) = 0;
    virtual ostream& outPut() = 0;
    virtual void take(int *) = 0;
    virtual void back(int *) = 0;
    virtual ~PAI() = default;
    TYPE type;
};

class DAN : public PAI {
public :
    DAN(int x) : x(x), PAI(TYPE::DAN_TYPE){}
    static vector<PAI *> get(int *arr){
        vector<PAI *> rec;
        for(int i = 3; i < MAX_N; i++){
            if(arr[i] == 0)continue;
            rec.push_back(new DAN(i));
        }
        return rec;
    }
    ostream& outPut() override {
        cout << "DAN " << name[x] << endl;
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
    bool operator>(PAI &ptr){
        switch(ptr.type){
            case TYPE::PASS_TYPE : {
                return true;
            } break;
            case TYPE::DAN_TYPE : {
                DAN &ptr_ = dynamic_cast<DAN &>(ptr);
                return x > ptr_.x;
            } break;
            default : return false;
        }
        return false;
    }
private :
    int x;
};

class DUI : public PAI {
public :
    DUI(int x) : x(x), PAI(TYPE::DUI_TYPE){}
    static vector<PAI *> get(int *arr){
        vector<PAI *> rec;
        for(int i = 3; i < MAX_N; i++){
            if(arr[i] >= 2){
                rec.push_back(new DUI(i));
            }else continue;
        }
        return rec;
    }
    ostream& outPut() override {
        cout << "DUI " << name[x] << endl;
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
    bool operator>(PAI &ptr){
        switch(ptr.type){
            case TYPE::PASS_TYPE : {
                return true;
            } break;
            case TYPE::DUI_TYPE : {
                DUI &ptr_ = dynamic_cast<DUI &>(ptr);
                return x > ptr_.x;
            } break;
            default : return false;
        }
        return false;
    }
private :
    int x;
};

class SHANDAI : public PAI {
public :
    SHANDAI(int SHAN, PAI *DAI) : SHAN(SHAN), DAI(DAI), PAI(TYPE::SHANDAI_TYPE) {}
    ostream& outPut() override {
        cout << "SHAN " << SHAN << " DAI ";
        DAI->outPut();
        return cout;
    }
    void take(int *arr) override {
        arr[SHAN] -= 3;
        DAI->take(arr);
        return ;
    }
    void back(int *arr) override {
        arr[SHAN] += 3;
        DAI->back(arr);
        return ;
    }
    static vector<PAI *> get(int *arr){
        vector<PAI *> rec;
        for(int i = 3; i < MAX_N; i++){
            if(arr[i] >= 3){
                for(int j = 3; j < MAX_N; j++){
                    if(j == i && arr[i] == 3)continue;
                    if(arr[j] == 1){
                        rec.push_back(new SHANDAI(i, new DAN(j)));
                    }
                    if(arr[j] == 2){
                        rec.push_back(new SHANDAI(i, new DUI(j)));
                    }
                }
            }
        }
        return rec;
    }
    bool operator>(PAI &ptr){
        switch(ptr.type){
            case TYPE::PASS_TYPE : {
                return true;
            } break;
            case TYPE::SHANDAI_TYPE : {
                SHANDAI &ptr_ = dynamic_cast<SHANDAI &>(ptr);
                if(DAI->type == ptr.type){
                    return SHAN > ptr_.SHAN;
                }return false;
            } break;
            default : return false;
        }
        return false;
    }
private :
    int SHAN;
    PAI *DAI;
};

class SHUNZHI : public PAI {
public :
    SHUNZHI(int first, int end, int len) : first(first), end(end), len(len), PAI(TYPE::SHUNZHI_TYPE){}
    ostream& outPut() override {
        cout << "SHUNZHI " << name[first] << "----" << name[end] << " len : " << len << endl;
        return cout;
    }
    void take(int *arr) override {
        for(int i = first; i <= end; i++){
            arr[i] -= 1;
        }
        return ;
    }
    void back(int *arr) override {
        for(int i = first; i <= end; i++){
            arr[i] += 1;
        }
        return ;
    }
    static vector<PAI *> get(int *arr){
        vector<PAI *> rec;
        for(int len = 5; len <= 14; len++){
            for(int i = 3; i <= MAX_N - 2 - len; i++){
                int flag = 1;
                for(int j = i; j < len + i; j++) {
                    if(arr[j] == 0){
                        flag = 0;    
                        break;
                    }
                }
                if(flag == 1){
                    rec.push_back(new SHUNZHI(i, i + len - 1, len));
                }
            }
        }
        return rec;
    }
    bool operator>(PAI &ptr){
        switch(ptr.type){
            case TYPE::PASS_TYPE : {
                return true;
            } break;
            case TYPE::SHUNZHI_TYPE : {
                SHUNZHI &ptr_ = dynamic_cast<SHUNZHI &>(ptr);
                if(len == ptr_.len){
                    return first > ptr_.first;
                }return false;
            } break;
            default : return false;
        }
        return false;
    }
private :
    int first, end, len;
};

class ZHADAN : public PAI {
public :
    ZHADAN(int x) : x(x), PAI(TYPE::ZHADAN_TYPE) {}
    ostream& outPut() override {
        cout << "ZHADAN " << name[x] << endl;
        return cout;
    }
    static vector <PAI *> get(int *arr){
        vector<PAI *> rec;
        for(int i = 3; i <= 15; i++){
            if(arr[i] == 4) {
                rec.push_back(new ZHADAN(i));
            }
        }
        return rec;
    }
    void take(int *arr) override {
        arr[x] -= 4;
        return ;
    }
    void back(int *arr) override {
        arr[x] += 4;
        return ;
    }
    bool operator>(PAI &ptr){
        switch(ptr.type){
            case TYPE::PASS_TYPE : {
                return true;
            } break;
            case TYPE::WANGZHA_TYPE : {
                return false;
            } break;
            case TYPE::ZHADAN_TYPE : {
                ZHADAN &ptr_ = dynamic_cast<ZHADAN &>(ptr);
               return x > ptr_.x;
            } break;
            default : return true;
        }
        return false;
    }
private :
    int x;
};

class WANGZHA : public PAI {
public :
    WANGZHA() : PAI(TYPE::WANGZHA_TYPE) {}
    ostream& outPut() override {
        cout << "WANGZHA" << endl;
        return cout;
    }
    void take(int *arr) override {
        arr[16] -= 1;
        arr[17] -= 1;
        return ;
    }
    void back(int *arr) override {
        arr[16] += 1;
        arr[17] += 1;
        return ;
    }    
    static vector<PAI *> get(int *arr) {
        vector<PAI *> rec;
        if(arr[16] == 1 && arr[17] == 1){
            rec.push_back(new WANGZHA);
        }
        return rec;
    }
    bool operator>(PAI &ptr){
        return true;
    }
};

class PASS : public PAI {
public :
    PASS() : PAI(TYPE::PASS_TYPE) {}
    ostream& outPut() override {
        cout << "PASS" << endl;
        return cout;
    }
    void take(int *arr) override {
        return ;
    }
    void back(int *arr) override {
        return ;
    }  
    static vector<PAI *> get(int *arr){
        vector<PAI *> rec;
        rec.push_back(new PASS);
        return rec;
    }
    bool operator>(PAI &ptr){
        switch(ptr.type){
            case TYPE::PASS_TYPE : {
                return false;
            } break;
            default : {return true;}
        }
    }
};

vector<PAI *> PAI::getPai(int *arr) {
    vector<PAI *> temp1 = DAN::get(arr);
    vector<PAI *> temp2 = DUI::get(arr);
    vector<PAI *> temp3 = SHANDAI::get(arr);
    vector<PAI *> temp4 = SHUNZHI::get(arr);
    vector<PAI *> temp5 = ZHADAN::get(arr);
    vector<PAI *> temp6 = WANGZHA::get(arr);
    vector<PAI *> temp7 = PASS::get(arr);
    vector<PAI *> paiarr;
    for(auto x : temp7){paiarr.push_back(x);}
    for(auto x : temp6){paiarr.push_back(x);}
    for(auto x : temp5){paiarr.push_back(x);}
    for(auto x : temp4){paiarr.push_back(x);}
    for(auto x : temp3){paiarr.push_back(x);}
    for(auto x : temp2){paiarr.push_back(x);}
    for(auto x : temp1){paiarr.push_back(x);}
    return paiarr;
}

class Node{
public :
    Node(PAI *p, int d) : p(p), d(d), win(0) {}
    int win, d;
    vector<Node *> next;
    PAI *p;
};

bool chackempty(int *arr){
    for(int i = 3; i < MAX_N; i++){
        if(arr[i] != 0)return false;
    }
    return true;
}

void outputall(int *arr){
    for(int i = 3; i < MAX_N; i++){
        if(arr[i] > 0){
            cout << name[i] << "*" << arr[i] << " ";
        }
    }
    cout << endl;
    return ;
}

vector<PAI *> repar(int *arr, PAI *ptr){
    vector<PAI *> paiarr = PAI::getPai(arr);
    vector<PAI *> ret;
    for(auto x : paiarr){
        if(x->operator>(*ptr)){
            ret.push_back(x);
        }else{
            delete x;
        }
    }
    return ret;
}

void gettree(Node *root, int *a, int *b){
    if(chackempty(b)){
        root->win = 0;
        return ;
    }
    vector<PAI *> rec = repar(a, root->p);
    for(int i = 0; i  < rec.size(); i++){
        // printf("------------\n");
        // outputall(a);
        // outputall(b);
        // printf("pre: ");
        // root->p->outPut();
        // printf("now: ");
        // x->outPut();
        // printf("------------\n");
        // if(rec[i]->operator>(*root->p)){
            Node *newnode = new Node(rec[i], root->d + 1);
            rec[i]->take(a);
            gettree(newnode, b, a);
            rec[i]->back(a);
            root->next.push_back(newnode);
            if(newnode->win == 0){
                root->win = 1;
                return ;
            }
        }
    return ;
}

void sever(Node *node, int *a, int *b){
    stack<Node *> sta;
    sta.push(node);
    while(!sta.empty()){
        int size = sta.size(), num;
        Node *root = sta.top();
        if(size % 2 == 1){
            root->p->take(b);
            printf("-->");
            outputall(a);
            printf("   ");
            outputall(b);
        }else{
            root->p->take(a);
            printf("   ");
            outputall(a);
            printf("-->");
            outputall(b);
        }
        for(int i = 0; i < sta.top()->next.size(); i++){
            printf("[%d] : [%d] :", i, sta.top()->next[i]->win);
            sta.top()->next[i]->p->outPut();
        }
        cin >> num;
        sta.push(root->next[num]);
    }
}


void useinput(int max = 7){
    if(max >= 1) printf("1-----DAN\n");
    if(max >= 2) printf("2-----DUI\n");
    if(max >= 3) printf("3-----SHUNZHI\n");
    if(max >= 4) printf("4-----SHANDAI\n");
    if(max >= 5) printf("5-----ZHADAN\n");
    if(max >= 6) printf("6-----WANGZHA\n");
    if(max >= 7) printf("7-----PASS\n");
    return ;
}

PAI* getptr(int max = 7){
    useinput(max);
    PAI *ptr;
    int x, n, l;
    cin >> x;
    switch (x){
        case 1 :{
            cin >> n;
            ptr = new DAN(n);
        } break;
        case 2 :{
            cin >> n;
            ptr = new DUI(n);
        } break;
        case 3 :{
            cin >> n;
            PAI *ret = getptr(2);
            ptr = new SHANDAI(n, ret);
        } break;
        case 4 :{
            cin >> n >> l;
            ptr = new SHUNZHI(n, n + l - 1, l);
        } break;
        case 5 :{
            cin >> n;
            ptr = new ZHADAN(n);
        } break;
        case 6 :{
            ptr = new WANGZHA();
        } break;
        case 7 :{
            ptr = new PASS();
        } break;
    }
    return ptr;
}

int main() {
    int a[MAX_N + 5] = {0}, x;
    int b[MAX_N + 5] = {0};
    while(cin >> x){
        if(x == 0) break;
        a[x]++;
    }
    while(cin >> x){
        if(x == 0) break;
        b[x]++;
    }
    Node *node = new Node(new PASS(), 0);
    gettree(node, a, b);
    sever(node, a, b);
    // vector<PAI *> rec = repar(a, new PASS());
    // for(int i = 0; i < rec.size(); i++){
    //     rec[i]->outPut();
    // }
    // Node *root = node->next[3]->next[2];
    // for(int i = 0; i < root->next.size(); i++){
    //     root->next[i]->p->outPut();
    // }
    return 0;
}