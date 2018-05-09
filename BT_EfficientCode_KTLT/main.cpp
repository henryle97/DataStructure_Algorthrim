/* LE VAN HOANG - MSSV: 20161669 */
/*BT KTLT: Phan tich, thiet ke, cai dat 1 bai toan
Input (Vi du): 101,102,103,104,201,202,205,206,207,208,209,210,212
Output (Vi du): 101-104,201,202,205-210,212
 */

#include <iostream>
#include <sstream>

using namespace std;

/* Ham doc 1 so tu input */
int readOneDigit(string input, int &pst)
{
    stringstream ss;
    string str;
    int X;
    /* Duyet tu vi tri pst den str.size()-3 (bo qua "..." ) */
    for (int i = pst; i != str.size() - 3; i++){
        if (input[i] == '.')
            return 1;
        else if (input[i] != ',')
            str.push_back(input[i]);
        else if (input[i] == ',')
        {
            /* Buoc chuyen string thanh int */
            pst = i + 1;        // Position cho so tiep theo (bo qua ',' )
            ss << str;
            str = "";           // Xoa str
            ss >> X;
            return X;
        }
    }
}

// Ham in ra theo yeu cau ko qua 30 ky tu 1 dong
void printResult(string output2)
{
    int dem = 0;
    // Neu day so vua tren tung dong
    for (int i = 0; i < output2.size(); i++)
    {
        if (dem % 28 == 0)          //Xet 1 string hop le khi ngat dong "101," -> max tren 1 dong co 7 lan "101," = 28 ky tu
            cout << "\n";
        cout << output2[i];
        dem++;
    }
    // Neu den doan hoac 1 so ko cuoi dong ko vua dong thi
}

int main()
{
    string input;
    stringstream output;
    int pst = 0;
    int minX, maxX;                 // 2 bien quan ly tung doan con trong day so
    int currX;                      // So co 3 chu so duoc lay tu input

    /* Nhap xau can chuyen doi */
    getline(cin, input);

    /* Doc so tu xau va dua vao ouput*/
    currX = readOneDigit(input, pst);
    while (currX != 1)
    {
        // Khoi tao gia tri min, max cho doan con
        minX = currX;
        maxX = readOneDigit(input, pst);
        if (maxX == minX+1)
        {
            while (1) {
                /* Doc so tiep theo */
                currX = readOneDigit(input, pst);

                /* Neu so hien tai lon hon so truoc 1 don vi*/
                if (currX == maxX+1)
                    maxX = currX;
                else {
                    /* Neu co lon hon 2 so trong doan [minX; minX] */
                    if (maxX > minX+1)
                        output << minX << "-" << maxX << ",";

                    /* Neu chi co 2 so trong doan [minX; maxX] */
                    else
                        output << minX << "," << maxX <<",";
                    /* Thoat vong lap while(1) */
                    break;
                }
            }
        }   /* Neu 2 so ko lien tiep nhau */
        else
        {
            output << minX << "," << maxX <<",";
            currX = readOneDigit(input, pst);       //Doc so tiep theo
        }
    }
    output << "...";

    /* In day so (moi dong ko qua 30 ky tu) */
    string output2;
    output >> output2;
    printResult(output2);
    return 0;
}
