/* WordCounts
 *
 * Description
 *
 * Program aska the user to give a file's name and tries to open it. If file
 * can't be opened, program prints an error and ends to a return value
 * EXIT_FAILURE. If file can be opened, program reads every line from the file,
 * splits it from space and adds the split words to a vector words. Program
 * prints how many times the word occurs in the file and also prints the line
 * where the word has occured.
 *
 * Writer of the program
 *
 * Name: EILeh
 */


#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

// Takes a line that user wants to split as a parameter, the separator is the
// char that the line is separated from and variable parts_no_empty has a truth
// value if user wants the empty parts or not.
vector<string> split(string line, char separator, bool parts_no_empty = false)
{

    vector<string> splitted_vector = {};
    string substring = "";

    // Goes through the given string line char by char.
    for ( char c : line )
    {
        // If current char is the separator.
        if ( c == separator )
        {
            // If part_no_empty is false and substring is not empty, substring
            // is added to a variable splitted_vector and the cleared.
            if (!(parts_no_empty && substring.empty()))
            {
                splitted_vector.push_back(substring);
                substring.clear();
            }
        }

        // If c is not separator, current char is added to the substring that it
        // forms a wanted split string.
        else
        {
            substring += c;
        }
    }

    // If variable parts_no_empty is false and substring is not empty, then adds
    // the last split to the vector as well.
    if (!(parts_no_empty && substring.empty()))
    {
        splitted_vector.push_back(substring);
        substring.clear();
    }

    return splitted_vector;

}

using Dictionary = map<string, set<unsigned int>>;

int main()
{
    string file_name = "";

    cout << "Input file: ";
    getline(cin, file_name);

    string line = "";
    unsigned int count_lines = 1;

    ifstream file_object(file_name);

    Dictionary word_count;

    // If file can't opened, prints an error.
    if ( !file_object )
    {
        cout << "Error! The file " << file_name << " cannot be opened.";

        file_object.close();

        return EXIT_FAILURE;
    }

    else

    {
        while ( getline(file_object, line) )
        {
            vector<string> words = split(line, ' ', true);

            // Goes through the vector words a word by word and and adds the
            // counts line as a set to a map word_count.
            for ( string word : words )
            {
                // If words is not already in the map word_count, adds a new
                // key-value -pair to the map.
                if ( word_count.find(word) == word_count.end() )
                {
                    word_count.insert( {word, {}} );
                }

                word_count.at(word).insert(count_lines);

            }

            count_lines++;
        }
    }

    file_object.close();

    // Goes through the map with an iterator.
    for ( Dictionary::iterator iter = word_count.begin();
          iter != word_count.end(); iter++ )
    {
        // Initializes the variable word as a key in the map.
        string word = iter->first;

        // Initializes the set rows_number as a value in the map.
        set<unsigned int> rows_number = iter->second;

        // Prints the word and the size of the varibale that has stored the in-
        // formation of the rows where the word has occured.
        cout << word << " " << rows_number.size() << ": ";

        set<unsigned int>::iterator rows_iterator = rows_number.begin();

        while ( true )
        {
            // Prints the words from the map, *rows_iterator points to the first
            // member in the map.
            cout << *rows_iterator;
            rows_iterator++;

            // If the end of the map is reached, loop is broke so that the comma
            // is not printed after the last member.
            if ( rows_iterator == rows_number.end() )
            {
                break;
            }

            cout << ", ";

        }
        cout << endl;
    }

    return EXIT_SUCCESS;
}
