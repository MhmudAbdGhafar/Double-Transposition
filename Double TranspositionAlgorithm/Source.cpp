#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main() {

    string plainTxt, firstKey, secondKey;
    cout << "Enter plain text: ";
    getline(cin, plainTxt);
    cout << "Enter first key word: ";
    getline(cin, firstKey);
    cout << "Enter second key word: ";
    getline(cin, secondKey);

    // preprocessing the input to avoid characters like space or special characters!!!
    for (int i = 0; i < plainTxt.size(); i++) {
        if (!isalpha(plainTxt[i])) {
            plainTxt.erase(i, 1);
            i--; //decrease index by 1 to keep track of the character followed removed one
        }
    }
    for (int i = 0; i < firstKey.size(); i++) {
        if (!isalpha(firstKey[i])) { // if the current character is not alphabetic one then I don't need it ^^
            firstKey.erase(i, 1);
            i--; //decrease index by 1 to keep track of the character followed removed one
        }

    }
    for (int i = 0; i < secondKey.size(); i++) {
        if (!isalpha(secondKey[i])) {
            secondKey.erase(i, 1);
            i--; //decrease index by 1 to keep track of the character followed removed one
        }
    }

    int columns = firstKey.size();
    int rows = secondKey.size();

    if (rows * columns < plainTxt.size()) {
        cout << "Sorry, There is no way to store plain text characters into a matrix with number of cells less than these characters";
        return 0;
    }

    // first step of algorithm: creating matrix stores plain text characters
    char** Matrix = new char* [rows]; // building up dynamic matrix using "pointer to pointer"
    for (int i = 0; i < rows; i++) {
        Matrix[i] = new char[columns]; // referencing array for every pointer element in the matrix to points to (2D)
    }

    int index = 0; // index stores next available character position from plain_txt string
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (index == plainTxt.size())
                Matrix[i][j] = 'x'; // unoccupied cell occupies character 'x' by default
            else {
                Matrix[i][j] = plainTxt[index];
                index++;
            }
        }
    }

    //second step of algorithm: doing transposition on columns based on first key word characters
    // creating array of pairs
    // the first value of the pair is a character from first key word string and the second value of the pair is the index of this character
    // pair is built in class in c++ has two values first and second of any type
    pair<char, int>* columnsIndx = new pair<char, int>[columns]; //here first value type is char and the second value is int
    for (int i = 0; i < columns; i++) {
        columnsIndx[i] = { firstKey[i], i };
    }
    sort(columnsIndx, columnsIndx + columns); // sorting first key word string
    // now, we have alphabetically ordered first keyword string which represents columns ordering 

    /*
    * let's explain what did happen ^^
    *
    * if we take plain text as "hello world", first key as "test", and second key  as "key"
    * then first key string before sorting was:
    * 0 1 2 3
    * t e s t
    * and now first key string after sorting is:
    * 1 2 0 3
    * e s t t
    * now, columnIndex array in pair[0] has character "e" as first value and column 1 (based 0) as the second value, ..., and so on so forth !!
    */

    char** columnTempMatrix = new char* [rows];// creating temporary matrix stores first transposition matrix
    for (int i = 0; i < rows; i++) {
        columnTempMatrix[i] = new char[columns];
    }
    // loop over columns and take every column(columns which are sorted and found in the second value of columnsIndex array) and push it in the temporary matrix
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            columnTempMatrix[j][i] = Matrix[j][columnsIndx[i].second];// first when i = 0 I'll take column 1, then 2, then 0, then 3(look above at line 71) 
        }
    }

    // update original matrix with tempMatrix after doing first transposition
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            Matrix[i][j] = columnTempMatrix[i][j];
        }
    }

    // Third step: doning transposition on rows based on second key word
    // creating array of pairs
    // the first value of the pair is a character from second key word string and the second value of the pair is the index of this character
    pair<char, int>* rowsIndx = new pair<char, int>[columns];
    for (int i = 0; i < rows; i++) {
        rowsIndx[i] = { secondKey[i], i };
    }
    sort(rowsIndx, rowsIndx + rows); // Now, I think it's easy to know why I'm sorting ^^

    char** rowTempMatrix = new char* [rows];// creating temporary matrix stores second transposition matrix
    for (int i = 0; i < rows; i++) {
        rowTempMatrix[i] = new char[columns];
    }
    // loop over rows and take every row(rows which are sorted and found in the second value of rowsIndex array) and push it in the temporary matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            rowTempMatrix[i][j] = Matrix[rowsIndx[i].second][j];
        }
    }

    // update original matrix with tempMatrix after doing second transposition
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            Matrix[i][j] = rowTempMatrix[i][j];
        }
    }
    cout << "\nCipher Text is: ";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            char upperCasedCharacter = toupper(Matrix[i][j]);
            cout << upperCasedCharacter;
        }
    }
    return 0;
}