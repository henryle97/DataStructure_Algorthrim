#include <iostream>
#include <fstream>
#include <unordered_map>
#include <list>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;


/** Solution
 * - Doc file, voi moi tu, check xem da co trong hashtable chua
 * + Neu chua thi tao list chua dong cua tu do va nhet < word, list dong> vao hashtable
 * + Neu da co thi update list cho word do trong hashtable
 *
 * - Tu viet hoa thi chuyen thanh tu thuong.
 * - Các từ giống nhau cùng dòng thì chỉ ghi nhận một lần.
 */

unordered_map<string, list<int>> myMap;         // Hash Table

// Cập nhật vị trí dòng của các từ
void updateLine(string word, int lineNumber)
{
    unordered_map<string, list<int>>::iterator itr;
    list<int> listLine;

    itr = myMap.find(word);

    // Neu word chua co trong myMap
    if(itr == myMap.end())
    {
        listLine.push_back(lineNumber);
        myMap.insert(make_pair(word, listLine));
    }
    else {
        // Neu word da co trong hashtable thi update no
        listLine = itr->second;

        //Nếu từ giống nhau cùng dòng thì bỏ qua
        for (auto it = listLine.begin(); it != listLine.end(); it++)
            if (*it == lineNumber)
                return;

        // Update lineNumber vào listLine
        listLine.push_back(lineNumber);
        myMap[word] = listLine;     //ghi đè cặp (key, value) còn insert thì không (dùng  insert ko thay đổi gì cả).

    }
}
void creatIndexTable()
{
    ifstream myFile;            //ifstream : for read file
    myFile.open("document.txt");

    string lineContent;
    string word;

    // Duyệt các từ trong 1 line
    for (int lineNumber = 1; getline(myFile, lineContent); lineNumber++)
    {
        // Doc tung tu trong dong do
        istringstream iss(lineContent);
        while(iss >> word) {

            //Chuyen word ve chu thuong
            transform(word.begin(), word.end(), word.begin(), ::tolower);

            // Xu ly dau ".", "," , "?", "!"
            if (word.back() == '.' || word.back() == ',' || word.back() == '!' || word.back() == '?')
                word = word.substr(0, word.length()-1);         //substr(begin, so ky tu lay);

            // Update vi tri dong cho word
            updateLine(word, lineNumber);
        }

        cout << lineNumber <<" " <<lineContent << endl;

    }
    myFile.close();

}

int main() {
    string wordFind;
    list<int> listLine;
    unordered_map<string, list<int>>::iterator itr;

    creatIndexTable();

    cout << "Nhap tu can tim : " ;
    cin >> wordFind;
    itr = myMap.find(wordFind);

    if (itr == myMap.end())
        cout << "Khong co tu nay trong van ban \n";

    else
    {
        listLine = itr->second;
        cout << "Tu nay xuat hien tai dong :  ";
        for (auto it = listLine.begin(); it != listLine.end(); it++)
            cout << *it << ", ";
    }

    return 0;
}