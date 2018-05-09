#include <iostream>
#include <string>
#include <cmath>

/*Stack using linked list*/

using namespace std;

typedef char dataType;

//Mo ta ngan xep (Trong C++ ko can dung typedef nhu C)
struct StackNode {
    dataType data;
    StackNode *pNext;
};


StackNode* CreatNode(dataType value);
void push(StackNode *&top, dataType value);
void pop(StackNode *&top);
dataType Top(StackNode *top);
int StackEmpty(StackNode *top);
int sizeOfStack(StackNode *top);
void DeleteStack(StackNode *&top);
bool CheckParentheses(StackNode *&top, dataType arr[]);
int CaculatePostFix(StackNode *&top, string postFix);
int doOperand(int a, int b, char op);
string ConvertInfixToPostfix(StackNode *&top, string infix);
int doUuTien(char c);
int CaculateExpression(StackNode *&top, string infix);
void PrintStack(StackNode *top)
{
    while(!StackEmpty(top))
    {
        cout << top->data << " ";
        top = top->pNext;
    }
}


int main()
{
    /*push(top, 10);
    push(top, 20);
    push(top, 15);
    pop(top);
    cout << "Top of stack is "<<Top(top) <<endl;
    DeleteStack(top);
    */
    /* Bai toan Parentheses Matching
    - Input: Mang X gom n ki hieu (dau ngoac, bien, con so or phep toan)
    - Output: true khi cac dau ngoac trong Z co doi
    */

    StackNode *top = NULL;          //CON TRO QUAN LY STACK

    int choose;
    cout << "--------------MENU----------" <<endl;
    cout << "1. Check Parentheses Matching" <<endl;
    cout << "2. Caculate the value of the postfix expression" <<endl;
    cout << "3. Convert infix to postfix" <<endl;
    cout << "4. Caculate the value of EXPRESSION" <<endl;
    cout << "Press choose: ";
    cin >> choose;

    switch (choose)
    {
    /*case 1:     //Chinh dataType -> char
        {
            char X[100];
            cout << "Nhap mang X de kiem tra: ";
            cin >> X;
            //Khoi tao stack rong
            DeleteStack(top);
            bool check = CheckParentheses(top, X);
            if (check == true)
            {
                cout << "true";
            }
            else
                cout << "false";
            break;
        }*/
    case 2:
        {

            string postFix;
            cout << "Nhap bieu thuc hau to: ";
            cin >> postFix;
            cout << "Gia tri cua bieu thuc la: " << CaculatePostFix(top, postFix) <<endl;
            DeleteStack(top);
            break;

        }
    case 3:
        {
            string infix;
            cout << "Nhap bieu thuc trung to: ";
            cin >> infix;
            cout << "Bieu thuc hau to tuong ung la: " << ConvertInfixToPostfix(top, infix) <<endl;
            DeleteStack(top);
            break;
        }
    case 4:
        {
            string infix;
            cout << "Nhap bieu thuc can tinh: ";
            cin >> infix;
            cout << "Ket qua la: " << CaculateExpression(top, infix) <<endl;
            break;
        }
    default:
            cout << "Nhap sai!";
    }

    return 0;
}

//Quan ly stack bang con tro top
StackNode *CreatNode(dataType value)
{
    StackNode *newNode = new StackNode;
    newNode->data = value;
    newNode->pNext = NULL;
    return newNode;
}
//Check stack co rong ko ?
int StackEmpty(StackNode *top)
{
    if (top == NULL)
        return 1;
    else
        return 0;
}
//Ham nhet value vao stack
void push(StackNode* &top, dataType value)
{
    StackNode *newNode = CreatNode(value);
    newNode->pNext = top;
    top = newNode;
}

//Ham loai bo phan tu tren cung  cua stack
void pop(StackNode* &top)
{
    if (StackEmpty(top))
    {
        cout << "Stack Empty, can't pop!"<<endl;
        return;
    }
    else
        top = top->pNext;
}
// Ham tra lai gia tri node tren top (nhung ko lay ra)
dataType Top(StackNode *top)
{
    //Neu Stack rong
    if (StackEmpty(top))
        return NULL;
    else
        return top->data;
}

//Pop khoi ngan xep va tra lai value phan tu vua pop
dataType Pop_Top(StackNode *&top)
{
    dataType result = Top(top);
    pop(top);
    return result;
}

//SIZE OF STACK ( error )
int sizeOfStack(StackNode *top)
{

    if (StackEmpty(top))
        return 0;
    else {
        StackNode *Temp = top;
        int sizeStack = 0;
        while ( !StackEmpty(Temp))      //Trong khi stack chua empty
        {
             sizeStack++;
             Temp = Temp->pNext;        //Chon temp->next lam top
        }
        return sizeStack;
    }


}
//Delete Stack
void DeleteStack(StackNode *&top)
{
    while(!StackEmpty(top))
        top = top->pNext;
}

/* Thuat toan:
- Duyet bieu thuc
    + Neu gap dau ngoac MO thi dua vao stack
    + Neu gap dau ngoac DONG thi kiem tra no voi top of stack return false neu ko giong
    + Cuối cùng kiểm tra Stack is empty ? ( nếu rỗng nghĩa là các dấu ngoặc mở đã bị lấy ra hết)
*/
bool CheckParentheses(StackNode *&top, dataType arr[])
{

    // int sizeOfArr = sizeof(arr) / sizeof(arr[0]) = 4 (sizeof char - pointer) ;  ->> Don't work!!!, dieu nay chi lam viec khi arr thuc su la mang
    // Ở đây chúng ta truyền vào function thực tế là 1 con trỏ (chỉ cho kích thước của nó thôi);

    char temp;
    for (int i = 0; arr[i] != '\0' ; i++)
    {
        if (arr[i] == '(' ||
            arr[i] == '[' ||
            arr[i] == '{')
                push(top, arr[i]);
        else if (arr[i] == ')' ||
                 arr[i] == '}' ||
                 arr[i] == ']' )
        {
            //Kiem tra top stack
            if (StackEmpty(top))
                return false;
            temp = Top(top);
            pop(top);

            if (arr[i] == ')')
            {
                if (temp == '(')        //Dấu ngoặc có đôi
                    continue;
                else
                    return false;
            }
            else if (arr[i] == '}')
            {
                if (temp == '{')
                    continue;
                else
                    return false;
            }
            else if (arr[i] == ']')
            {
                if (temp == '[')
                    continue;
                else
                    return false;
            }
        }
    } //end for

    //Neu stack rong (cac dau ngoac mo da bi lay ra)
    if (StackEmpty(top))
        return true;
    else
        return false;

}

//Caculate Postfix Expression
int doOperand(int a, int b, char op)
{
    switch (op)
    {
    case '+':
        {
            return a + b;
            break;
        }
    case '-':
        {
            return a - b;
        }
    case '*':
        {
            return a * b;
        }
    case '/':
        {
            return a / b;
        }
    case '^':
        return pow(a, b);
    default :
        return 0;
    }
}

int CaculatePostFix(StackNode *&top, string postFix)
{
    int first, second, result;
    int item;
    //Duyet cac ky tu trong posFix
    for (char c : postFix)
    {
        //Kiem tra xem c co phai la phep toan
        if ( c != '+' && c != '-' && c != '*' && c!= '/' && c != '^')
        {
            item = c - '0';         //Chuyen char sang int : '3' -> 3
            push(top, item);        // Dua item vao stack
        }
        else
        {
            second = Top(top);
            pop(top);
            first = Top(top);
            pop(top);
            result = doOperand(first, second, c);           //Chu y toan hang thu 2 - toan hang thu 1 (1 ,2 theo thu tu lay tu ngan xep)
            push(top, result);                              // Dua ket qua tinh toan vao stack
        }
    }
    return Top(top);
}

//Function conver INFIX to POSTFIX
/*
- Thuật toán: Duyệt biểu thức từ trái qua phải
    + Gặp Toán hạng (Operands) : đưa ra ( push in string postfix)
    + Gặp dấu mở ngoặc '(' : nạp nó vào ngăn xếp
    + Gặp dấu đóng ngoặc ')': đẩy kí hiệu ra khỏi ngăn xếp cho đến khi gặp dấu mở ngoặc đầu tiên
    + Gặp phép toán ( Operator): đưa ra khỏi ngăn xếp (push into string) tất cả các phép toán cho đến khi gặp phép toán có
    thứ tự ưu tiên thấp hơn HOẶC gặp phép toán có tính kết hợp phải (vd '^': 2^2^2) có cùng thứ tự ưu tiên, sau đó nạp phép
    toán đang xét vào ngăn xếp.
    + Duyệt hết biểu thức thì đưa all phép toán từ stack -> string
*/
string ConvertInfixToPostfix(StackNode *&top, string infix)
{
    string postfix;
    char temp;
    DeleteStack(top);           //Lam rong stack

    for (char c : infix)    //Duyet tung ky tu trong string (Duyet bieu thuc tu trai qua phai)
    {

        //Neu gap toan hang
        if (c != '+' && c != '-' && c != '*' && c!= '/' && c!= '^' && c != '(' && c != ')')
            postfix.push_back(c);
        else {
            if (c == '(')                           //Gap dau mo ngoac : dua vao stack
                push(top, c);
            else if (c == ')'){                      //Gap dong ngoac thi dua tu stack vao posfix cho den khi gap mo ngoac trong stack
                while (top->data != '(')
                {
                    temp = Pop_Top(top);
                    postfix.push_back(temp);
                }
                pop(top);       //pop '(' rq khoi ngan xep
            }
            else {          //Gap phep toan : dua tu stack -> postfix cho den khi gap phep toan do uu tien thap hon OR c va temp cung bang '^'

                if (top == NULL)    //Neu ngan xep rong
                {
                    push(top, c);
                    continue;       //Nhet c vao stack va xet ky tu tiep theo
                }
                //Kiem tra phep toan o dau ngan xep voi phep toan dang xet
                while (doUuTien(top->data) >= doUuTien(c) && (top->data != '^' && c != '^') )
                {
                    temp = Pop_Top(top);

                    postfix.push_back(temp);
                    if (top == NULL)
                        break;          //thoat khoi vong while

                }
                // Dua toan hang hien tai vao stack
                push(top, c);
            }
        }
    } //END FOR
    //Duyet het BT thi dua all operator tu stack vao postfix

    while (!StackEmpty(top))
    {
        temp = Pop_Top(top);
        postfix.push_back(temp);
    }

    return postfix;

}

int doUuTien(char c)
{
    if (c == '(' || c == ')')
        return 0;       //Trong stack thi ( co do uu tien thap nhat
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    if (c == '^')
        return 3;
}

int CaculateExpression(StackNode *&top, string infix)
{
    DeleteStack(top);
    string postfix;
    postfix = ConvertInfixToPostfix(top, infix);
    return CaculatePostFix(top, postfix);
}

